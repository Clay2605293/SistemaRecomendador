#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class PriorityQueue {
private:
    std::vector<std::pair<T, int>> queue;  // Par de (valor, prioridad)

public:
    PriorityQueue() {}

    PriorityQueue(const std::vector<std::pair<T, int>>& elements) {
        queue = elements;
        std::make_heap(queue.begin(), queue.end(), [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
            return a.second < b.second; // Menor prioridad en la raíz
        });
    }

    int size() const {
        return queue.size();
    }

    bool empty() const {
        return queue.empty();
    }

    void clear() {
        queue.clear();
    }

    T top() const {
        if (!empty()) {
            return queue.front().first;  // Retorna el valor con mayor prioridad
        } else {
            throw std::runtime_error("Queue is empty");
        }
    }

    void push(const T& value, int priority) {
        queue.push_back(std::make_pair(value, priority));
        std::push_heap(queue.begin(), queue.end(), [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
            return a.second < b.second; // Mantiene el heap con mayor prioridad al frente
        });
    }

    void pop() {
        if (!empty()) {
            std::pop_heap(queue.begin(), queue.end(), [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
                return a.second < b.second;
            });
            queue.pop_back();  // Remueve el elemento con mayor prioridad
        } else {
            throw std::runtime_error("Queue is empty");
        }
    }
};

#endif // PRIORITYQUEUE_HPP
