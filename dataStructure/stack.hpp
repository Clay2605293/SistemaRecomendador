#ifndef STACK_HPP
#define STACK_HPP

#include "linked_list.hpp"

template <typename T>
class Stack
{
private:
    LinkedList<T> container_;       
    unsigned long long int size_{0};

public:
    Stack() = default;


    ~Stack() 
    {
        clear();
    }

    
    friend std::ostream& operator<<(std::ostream& os, const Stack& stack)
    {
        os << stack.container_;
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


    T& top()
    {
        return container_.front();
    }


    const T& top() const
    {
        return container_.front();
    }


    void push(const T& value)
    {
        container_.push_front(value);
        ++size_;
    }


    void push(T&& value)
    {
        container_.push_front(std::move(value));
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