#ifndef _MEMORY_SPY_
#define _MEMORY_SPY_

#include <vector>
#include <list>
#include <string>
#include <cstddef>
#include <stdio.h>
#include <algorithm>

class CMemorySpy
{
public:
    void NotifyAlloc(size_t size, size_t count, void *address)
    {
        printf("*** Allocate block %d : %ld elem of %ld bytes\n", s_curId, count, size);
        m_blocks.push_back({size, count, address, s_curId++});
    }

    void NotifyDealloc(void *address, size_t count)
    {
        for (size_t i = 0; i < m_blocks.size(); ++i)
        {
            if (m_blocks[i].address == address)
            {
                if (m_blocks[i].count == count)
                {
                    printf("*** Deallocate block %d : %ld elem of %ld bytes\n",
                           m_blocks[i].id, m_blocks[i].count, m_blocks[i].size);
                }
                else
                {
                    printf("*** Trying to deallocate block %d of %ld elem while %ld where allocated !\n",
                           m_blocks[i].id, count, m_blocks[i].count);
                }
                if (i + 1 < m_blocks.size())
                {
                    m_blocks[i] = m_blocks[m_blocks.size() - 1];
                }
                m_blocks.resize(m_blocks.size() - 1);
                return;
            }
        }
        printf("*** Deallocate failed !\n");
    }
    void CheckLeaks()
    {
        if (m_blocks.empty())
        {
            printf("*** No memory leak\n");
        }
        else
        {
            printf("*** %ld memory leaks detected !\n", m_blocks.size());
            for (const MemBlock &block : m_blocks)
            {
                printf("- Leak of block %d : %ld elem of size %ld \n", block.id, block.count, block.size);
            }
        }
    }
    static int s_curId;

private:
    struct MemBlock
    {
        size_t size;
        size_t count;
        void *address;
        int id;
    };
    std::vector<MemBlock> m_blocks;
};

int CMemorySpy::s_curId = 0;
static CMemorySpy memorySpy;

template <class T>
struct SpyAllocator : std::allocator<T>
{
    typedef T value_type;
    SpyAllocator(/*vector args*/) = default;
    template <class U>
    SpyAllocator(const SpyAllocator<U> &other) {}
    template <class U>
    struct rebind
    {
        using other = SpyAllocator<U>;
    };
    T *allocate(std::size_t n)
    {
        T *p = (T *)new char[sizeof(T) * n];
        memorySpy.NotifyAlloc(sizeof(T), n, p);
        return p;
    };
    void deallocate(T *p, std::size_t n)
    {
        memorySpy.NotifyDealloc(p, n);
        delete (char *)p;
    }
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
};
template <class T, class U>
bool operator==(const SpyAllocator<T> &, const SpyAllocator<U> &) { return false; }
template <class T, class U>
bool operator!=(const SpyAllocator<T> &, const SpyAllocator<U> &) { return false; }

class Foo
{
public:
    Foo()
    {
        m_id = count++;
        printf("Create Foo_%d\n", m_id);
    }
    Foo(const Foo &foo)
    {
        m_id = count++;
        printf("Create Foo_%d copy of Foo_%d\n", m_id, foo.m_id);
    }
    Foo &operator=(const Foo &foo)
    {
        printf("Copying Foo_%d into Foo_%d\n", foo.m_id, m_id);
        return *this;
    }
#if USE_MOVE
    Foo &operator=(Foo &&foo)
    {
        printf("Moving Foo_%d into Foo_%d\n", foo.m_id, m_id);
        return *this;
    }
    Foo(Foo &&foo)
    {
        m_id = count++;
        printf("Create Foo_%d move copy of Foo_%d\n", m_id, foo.m_id);
    }
#endif
    virtual ~Foo()
    {
        printf("Destroy Foo_%d\n", m_id);
    }
    static void ResetCount()
    {
        count = 0;
    }

private:
    int m_id;
    static int count;
};
int Foo::count;


#endif