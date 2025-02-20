#pragma once
#include <memory_resource>
#include <map>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

/*
 * Фиксированный блок памяти.
 * Вся логика внутри .cpp
 */

class FixedBlockResource : public std::pmr::memory_resource
{
public:
    explicit FixedBlockResource(std::size_t totalSize);
    ~FixedBlockResource();

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void  do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool  do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    void* m_buffer{nullptr};
    std::size_t m_totalSize{0};

    // map<адрес, (размер, free?)>
    std::map<std::uintptr_t, std::pair<std::size_t,bool>> m_map;

    void* findFreeBlock(std::size_t bytes, std::size_t alignment);
    static std::uintptr_t alignAddr(std::uintptr_t addr, std::size_t alignment);
};
