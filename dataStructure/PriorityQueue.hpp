#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class PriorityQueue {
private:
    std::vector<std::pair<T, float>> queue;  // Par de (valor, prioridad)

public:
    // Constructor que inicializa la fila vacía
    PriorityQueue() {}

    // Constructor que inicializa la fila con un vector de pares (valor, prioridad)
    PriorityQueue(const std::vector<std::pair<T, float>>& elements) {
        queue = elements;
        // Ordenar los elementos según su prioridad
        std::sort(queue.begin(), queue.end(), [](const std::pair<T, float>& a, const std::pair<T, float>& b) {
            return a.second > b.second;  // Orden descendente por prioridad
        });
    }

    // Constructor de copia
    PriorityQueue(const PriorityQueue& other) {
        queue = other.queue;
    }

    // Constructor de movimiento
    PriorityQueue(PriorityQueue&& other) noexcept {
        queue = std::move(other.queue);
    }

    // Método que devuelve el tamaño de la fila
    int size() const {
        return queue.size();
    }

    // Método que verifica si la fila está vacía
    bool empty() const {
        return queue.empty();
    }

    // Método que limpia la fila
    void clear() {
        queue.clear();
    }

    // Método que devuelve el elemento con la mayor prioridad (top)
    T top() const {
        if (!empty()) {
            return queue.front().first;  // Retorna el valor con mayor prioridad
        } else {
            throw std::runtime_error("Queue is empty");
        }
    }

    // Método para insertar un valor con una prioridad específica
    void push(const T& value, float priority) {
        queue.push_back(std::make_pair(value, priority));
        // Reordena el vector de acuerdo con la prioridad (mayor prioridad al frente)
        std::sort(queue.begin(), queue.end(), [](const std::pair<T, float>& a, const std::pair<T, float>& b) {
            return a.second > b.second;  // Orden descendente por prioridad
        });
    }

    // Método para eliminar el elemento con la mayor prioridad
    void pop() {
        if (!empty()) {
            queue.erase(queue.begin());  // Elimina el primer elemento (el de mayor prioridad)
        } else {
            throw std::runtime_error("Queue is empty");
        }
    }
};

#endif // PRIORITYQUEUE_HPP
