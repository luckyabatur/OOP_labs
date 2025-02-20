#include "../include/fixed_block_resource.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <new>

FixedBlockResource::FixedBlockResource(std::size_t totalSize)
        : m_totalSize(totalSize)
{
    m_buffer = ::operator new(m_totalSize);
    // вся память свободна:
    std::uintptr_t base = reinterpret_cast<std::uintptr_t>(m_buffer);
    m_map[ base ] = { m_totalSize, true };
}

FixedBlockResource::~FixedBlockResource()
{
    ::operator delete(m_buffer);
}

void* FixedBlockResource::do_allocate(std::size_t bytes, std::size_t alignment)
{
    void* result = findFreeBlock(bytes, alignment);
    if (!result) {
        throw std::bad_alloc();
    }
    return result;
}

void FixedBlockResource::do_deallocate(void* p, std::size_t /*bytes*/, std::size_t /*alignment*/)
{
    std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(p);
    auto it = m_map.find(addr);
    if (it != m_map.end()) {
        it->second.second = true; // помечаем free
    }
    // Не сливаем блоки, упрощённый вариант
}

bool FixedBlockResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept
{
    return (this == &other);
}

void* FixedBlockResource::findFreeBlock(std::size_t bytes, std::size_t alignment)
{
    for (auto it = m_map.begin(); it != m_map.end(); ++it) {
        auto addr     = it->first;
        auto blockSz  = it->second.first;
        auto isFree   = it->second.second;
        if (!isFree) continue;
        std::uintptr_t aligned = alignAddr(addr, alignment);
        if (aligned + bytes <= addr + blockSz) {
            // помещаем
            it->second.second = false; // занято
            // разделение блока:
            std::size_t usedOffset = aligned - addr;
            if (usedOffset > 0) {
                m_map[addr] = { usedOffset, true };
                m_map[aligned] = { bytes, false };
            } else {
                it->second.first = bytes;
            }
            std::uintptr_t tail = aligned + bytes;
            std::size_t leftover = (addr + blockSz) - tail;
            if (leftover > 0) {
                m_map[tail] = { leftover, true };
            }
            return reinterpret_cast<void*>(aligned);
        }
    }
    return nullptr;
}

std::uintptr_t FixedBlockResource::alignAddr(std::uintptr_t addr, std::size_t alignment)
{
    std::uintptr_t over = addr % alignment;
    if (over == 0) return addr;
    return addr + (alignment - over);
}
