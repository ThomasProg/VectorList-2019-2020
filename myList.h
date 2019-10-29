#ifndef _MY_LIST_H_
#define _MY_LIST_H_

#include <iostream>
#include <cassert>

#define DO(inst)             \
    printf("\n" #inst "\n"); \
    inst

template <typename T, class Allocator>
class MyList
{
private:
    class Node 
    {
    private:

    public:
        T* elem = nullptr;
        Node* next = nullptr, *prev = nullptr;

        Node(const T& newElem)
        {
            elem = new T(newElem); 
        }

        ~Node()
        {
            //delete elem;
        }
    };

public:
    class iterator : public std::iterator<
                        std::forward_iterator_tag, // iterator_category
                        long,                      // value_type
                        long,                      // difference_type
                        const long*,               // pointer
                        const long&                // reference
                                      >
    {
    public:
        Node* node;

        iterator() {}

        ~iterator()
        {
            //delete elem;
        }

        iterator(Node* node)
        {
            this->node = node;
        }

        iterator(const iterator& it)
        {
            node = it.node;
        }

        iterator& operator++()
        {
            //ptr++;
            node = this->node->next;
            return *this;
        }

        bool operator==(const iterator& it)
        {
            return this->node->elem == it.elem;
        }

        bool operator!=(const iterator& it)
        {
            return (it.node != node);
        }

        T& operator*()
        {
            return *node->elem;
        }
    };

    iterator begin() const
    {
        return iterator(head);
    }

    iterator end() const
    {
        //iterator x(head);
        // while (x.node->next != nullptr)
        //     x = x.node->next;
        return iterator(nullptr);
    }

public:
    
    MyList()
    {

    }

    MyList(const MyList& copied)
    {
        for (iterator it = copied.begin(); it != copied.end(); ++it)
        {
            this->push_back(*it.node->elem);
        }
    }

    ~MyList()
    {
        Node* it = head, *toDelete = nullptr;
        while (it != nullptr)
        {
            toDelete = it;
            it = it->next;
            spy.deallocate(toDelete, 1);
        }
    }

    size_t size() const
    {
        return m_size;
    } 

    void push_back(const T& newElem)
    {
        if (head == nullptr)
        {
            Node* newNode = spy.allocate(1);
            new (&(*newNode)) Node(newElem);
            head = newNode;
            tail = newNode;
        }
        else 
        {
            Node** prevNewNode = &head;
            while ((*prevNewNode)->next != nullptr)
            {
                prevNewNode = &(*prevNewNode)->next;
            }
            
            Node* newNode = spy.allocate(1);
            new (&(*newNode)) Node(newElem);
            newNode->prev = *prevNewNode;
            (*prevNewNode)->next = newNode;
            tail = newNode;
        }

        m_size++;
    }

    void insert(const iterator& it, T data)
    {
        
        Node* newNode = spy.allocate(1);
        new (newNode) Node(data);

        it.node->prev->next = newNode;
        //std::cout << it.node->prev << " -> " << newNode << " -> " << it.node << std::endl;
        newNode->prev = it.node->prev;
        newNode->next = it.node;
        it.node->prev = newNode;
        m_size++;
    }

    void remove(T item)
    {
        if (head == nullptr)
            return;

        Node** prevNewNode = &head;
        while (*(*prevNewNode)->next->elem != item)
        {
            if ((*prevNewNode)->next == nullptr)
                return;
            prevNewNode = &(*prevNewNode)->next;
        }
        
        Node* toDeleteNode = (*prevNewNode)->next;
        (*prevNewNode)->next = toDeleteNode->next;
        toDeleteNode->next->prev = (*prevNewNode);

        delete toDeleteNode->elem;
        spy.deallocate(toDeleteNode, 1);

        m_size--;
    }

public:


private:
    //T m_elements;
    size_t m_size = 0;
    Node* head = nullptr;
    Node* tail = nullptr;
    SpyAllocator<Node> spy;
};

#endif