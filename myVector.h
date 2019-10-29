#ifndef _MY_VECTOR_H_
#define _MY_VECTOR_H_

#include <iostream>

#define DO(inst)             \
    printf("\n" #inst "\n"); \
    inst

template <typename T, class Allocator>
class MyVector
{
public:
    MyVector()
    {

    }

    MyVector(const MyVector& copied)
    {
        m_capacity = copied.capacity();
        m_size     = copied.size();

        m_elements = Allocator().allocate(m_capacity);

        for (size_t i = 0; i < copied.m_size; i++)
            new (&m_elements[i]) T((copied[i]));
    }

    ~MyVector()
    {
        for (size_t i = 0; i < m_size; ++i)
            m_elements[i].~T(); // destroy each element

        if (m_capacity != 0)
            Allocator().deallocate(m_elements, m_capacity);
    }

    size_t capacity() const
    {
        return m_capacity;
    } 

    size_t size() const
    {
        return m_size;
    } 

    void push_back(const T& elem)
    {
        if (m_size == m_capacity)
        {
            //increase capacity
            if (m_capacity == 0)
                m_capacity = 1;
            else 
                m_capacity *= 2;

            //allocate data
            T* newAllowedData = Allocator().allocate(m_capacity); 

            new (&newAllowedData[m_size]) T(elem);

            //copy data
            for (size_t i = 0; i < m_size; i++)
                new (&newAllowedData[i]) T((m_elements[i]));

            if (m_size != 0)
            {
                for (size_t i = 0; i < m_size; i++)
                    m_elements[i].~T();

                Allocator().deallocate(m_elements, m_size);
            }

            m_elements = newAllowedData;
        }
        else 
            new (&m_elements[m_size]) T(elem);

        m_size++;
    }

    T& operator[](size_t i) const
    {
        return m_elements[i];
    }

    MyVector& operator=(const MyVector& copied)
    {
        clear();

        m_capacity = copied.capacity();
        m_size     = copied.size();

        m_elements = Allocator().allocate(m_capacity);

        for (size_t i = 0; i < copied.m_size; i++)
            new (&m_elements[i]) T((copied[i]));
        
        return *this;
    }

    void resize(size_t newSize)
    {
        //allocate data
        T* newAllowedData = Allocator().allocate(newSize); 
        //copy data
        for (size_t i = 0; i < m_size; i++)
            new (&newAllowedData[i]) T(m_elements[i]);
        
        for (size_t i = m_size; i < newSize; i++)
            new (&newAllowedData[i]) T();

        if (m_size != 0)
        {
            for (size_t i = 0; i < m_size; i++)
                m_elements[i].~T();

            Allocator().deallocate(m_elements, m_size);
        }

        m_elements = newAllowedData;
        m_capacity = newSize;
        m_size     = newSize;
    }

    void reserve(size_t reserved)
    {
        m_elements = Allocator().allocate(reserved);
        m_capacity = reserved;
    }

    void clear()
    {
        if (m_size != 0)
        {
            for (size_t i = 0; i < m_size; i++)
                m_elements[i].~T();
        }
        m_size = 0;
    }

private:
    T* m_elements;
    size_t m_capacity = 0;
    size_t m_size     = 0;
};

#endif