#pragma once
#include <memory_resource>
#include <iterator>
#include <cstddef>


template <class T>
class PmrDList
{
private:
    struct Node
    {
        Node* prev{nullptr};
        Node* next{nullptr};
        T data;
        Node(const T& val) : data(val) {}
        Node(T&& val) : data(std::move(val)) {}
    };

    using Alloc = std::pmr::polymorphic_allocator<Node>;
    using AllocTraits = std::allocator_traits<Alloc>;

public:
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator(Node* p) : m_cur(p) {}
        reference operator*()  const { return m_cur->data; }
        pointer   operator->() const { return &(m_cur->data); }
        iterator& operator++()
        {
            if (m_cur) m_cur = m_cur->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        bool operator==(const iterator& rhs) const { return m_cur == rhs.m_cur; }
        bool operator!=(const iterator& rhs) const { return !(*this == rhs); }
    private:
        Node* m_cur{nullptr};
    };

    PmrDList(std::pmr::memory_resource* mr = std::pmr::get_default_resource())
            : m_alloc(mr), m_head(nullptr), m_tail(nullptr)
    {}


    ~PmrDList() { clear(); }


    PmrDList(const PmrDList&) = delete;
    PmrDList& operator=(const PmrDList&) = delete;


    PmrDList(PmrDList&&) = delete;
    PmrDList& operator=(PmrDList&&) = delete;

    void push_back(const T& val)
    {
        Node* n = AllocTraits::allocate(m_alloc,1);
        AllocTraits::construct(m_alloc, n, val);
        linkBack(n);
    }
    void push_back(T&& val)
    {
        Node* n = AllocTraits::allocate(m_alloc,1);
        AllocTraits::construct(m_alloc, n, std::move(val));
        linkBack(n);
    }

    void clear()
    {
        Node* cur = m_head;
        while(cur)
        {
            Node* nxt = cur->next;
            AllocTraits::destroy(m_alloc, cur);
            AllocTraits::deallocate(m_alloc, cur, 1);
            cur = nxt;
        }
        m_head = m_tail = nullptr;
    }

    iterator begin() { return iterator(m_head); }
    iterator end()   { return iterator(nullptr); }

private:
    void linkBack(Node* n)
    {
        n->prev = m_tail;
        n->next = nullptr;
        if (!m_head)
        {
            m_head = n;
        }
        if (m_tail)
        {
            m_tail->next = n;
        }
        m_tail = n;
    }

private:
    Alloc m_alloc;
    Node* m_head{nullptr};
    Node* m_tail{nullptr};
};
