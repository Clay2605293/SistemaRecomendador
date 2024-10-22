#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "doubly_linked_list.hpp"

template <typename T>
class Queue
{
private:
    DoublyLinkedList<T> container_;
    unsigned long long int size_{0};        

public:
    Queue() = default;


    ~Queue()
    {
        clear();
    }


    friend std::ostream& operator<<(std::ostream& os, const Queue& queue)
    {
        os << queue.container_;
        return os;
    }


    unsigned long long int size()
    {
        return size_;
    }


    bool empty()
    {
        if (size_ != 0)
            return false;
        return true;
    }


    T& front()
    {
        return container_.front();
    }


    const T& front() const
    {
        return container_.front();
    }


    void push(const T& value)
    {
        container_.push_back(value);
        ++size_;
    }

    
    void push(T&& value)
    {
        container_.push_back(std::move(value));
        ++size_;
    }


    void pop()
    {
        container_.pop_front();
        --size_;
    }   


    void clear()
    {
        container_.clear();
        size_ = 0;
    }       
};


#endif