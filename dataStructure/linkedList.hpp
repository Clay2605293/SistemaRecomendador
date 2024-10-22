#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <stdexcept>    // For std::out_of_range

template <typename T>
class Node {

public:

    T data;
    Node* next;

    Node(const T& value) 
    {
        data = value;
        next = nullptr;
    }
    
    Node(T&& value) 
    {
        data = std::move(value);
        next = nullptr;
    }
};

template <typename T>
class LinkedList {

private:

    Node<T>* head_{ nullptr };   
    unsigned long int size_{0};

public:

    LinkedList() = default;


    ~LinkedList() 
    {
        clear();
    }


    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list)
    {
        os << "{ ";
        if (list.empty())
        {
            os << "}";
        }
        else
        {
            Node<T>* current = list.head_;
            while (current != nullptr)
            {
                os << current->data;
                current = current->next;
                if (current != nullptr) {
                    os << ", ";
                }
            }
            os << " }";
        }
        
        return os;
    }

    unsigned long long int size()
    {
        return size_;
    }


    T& at(unsigned long long int index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        
        Node<T>* current = head_;
        unsigned long long int i = 0;     
        while (i != index)
        {
            Node<T>* next = current->next;
            current = next;
            ++i;
        }
        
        return current->data;
    }


    const T& at(unsigned long long int index) const
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        
        Node<T>* current = head_;
        unsigned long long int i = 0;
        while (i != index)
        {
            Node<T>* next = current->next;
            current = next;
            ++i;
        }
        
        return current->data;
    }


    bool empty() const
    {
        return head_ == nullptr;
    }

    void clear()
    {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        size_ = 0;
    }


    void push_front(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head_;
        head_ = newNode;
        ++size_;
    }

    /*
    void push_front(T&& value)
    {
        Node<T>* newNode = new Node<T>(std::move(value));
        newNode->next = head_;
        head_ = newNode;
        ++size_;
    }
    */

    void pop_front()
    {
        if (!empty()) {
            Node<T>* oldHead = head_;
            head_ = head_->next;
            delete oldHead;
            --size_;
        }
    }


    void push_back(const T& value)
    {
        Node<T>* current = head_;
        for (unsigned long long int i = 0; i < size_; ++i)
        {
            Node<T>* next = current->next;
            if (i != size_ - 1)
            {
                current = next;
            }
            else
            {
                insert_after(current, value);
                break;
            }
        }
    }


    void pop_back()
    {
        if (!empty())
        {
            Node<T>* current = head_;
            for (unsigned long long int i = 0; i < size_; ++i)
            {
                Node<T>* next = current->next;
                if (i != size_ - 2)
                {
                    current = next;
                }
                else
                {
                    erase_after(current);
                }
            }
        }

    }

    T& front()
    {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head_->data;
    }


    const T& front() const
    {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head_->data;
    }


    T& back()
    {
        if (empty())
        {
            throw std::out_of_range("List is empty");
        }
        return at(size_ - 1);
    }


    void insert_after(Node<T>* node, const T& value)
    {
        if (node != nullptr) {
            Node<T>* newNode = new Node<T>(value);
            newNode->next = node->next;
            node->next = newNode;
            ++size_;
        }
    }


    void erase_after(Node<T>* node)
    {
        if (node != nullptr && node->next != nullptr) {
            Node<T>* toDelete = node->next;
            node->next = toDelete->next;
            delete toDelete;
            --size_;
        }
    }


    Node<T>* find(const T& value)
    {
        Node<T>* current = head_;

        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }

        return nullptr;
    }
};

#endif