#ifndef ORDERED_LIST_HPP
#define ORDERED_LIST_HPP

#include <iostream>        // Para std::cout
#include <initializer_list> // Para std::initializer_list
#include <cstddef>          // Para std::size_t

template <typename T>
class OrderedList {
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t list_size;

    // Función auxiliar para copiar otra lista
    void copy_from(const OrderedList& other) {
        clear();
        Node* current = other.head;
        while (current) {
            insert(current->data);
            current = current->next;
        }
    }

public:
    // Constructor por defecto
    OrderedList() : head(nullptr), tail(nullptr), list_size(0) {}

    // Destructor
    ~OrderedList() {
        clear();
    }

    // Constructor de copia
    OrderedList(const OrderedList& other) : head(nullptr), tail(nullptr), list_size(0) {
        copy_from(other);
    }

    // Operador de asignación
    OrderedList& operator=(const OrderedList& other) {
        if (this != &other) {
            copy_from(other);
        }
        return *this;
    }

    // Constructor con lista de inicialización
    OrderedList(std::initializer_list<T> values) : head(nullptr), tail(nullptr), list_size(0) {
        for (const T& value : values) {
            insert(value);
        }
    }

    // Método para obtener un nodo en una posición específica
    Node* get_node_at(std::size_t index) const {
        if (index >= list_size) {
            return nullptr;
        }

        Node* current = head;
        for (std::size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    // Binary search
    Node* binary_search(const T& value) const {
        if (list_size == 0) {
            return nullptr;
        }

        std::size_t left = 0;
        std::size_t right = list_size - 1;

        while (left <= right) {
            std::size_t mid = left + (right - left) / 2;
            Node* mid_node = get_node_at(mid);

            if (mid_node->data == value) {
                return mid_node;
            }
            else if (mid_node->data < value) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return nullptr;  // El valor no está en la lista
    }

    // Método para limpiar la lista
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* to_delete = current;
            current = current->next;
            delete to_delete;
        }
        head = nullptr;
        tail = nullptr;
        list_size = 0;
    }

    // Inserta un valor de forma ordenada
    void insert(const T& value) {
        Node* new_node = new Node(value);

        if (list_size == 0) {
            head = tail = new_node;
        } else {
            Node* current = head;
            while (current != nullptr && current->data < value) {
                current = current->next;
            }

            if (current == head) {
                // Insertar al inicio
                new_node->next = head;
                head->prev = new_node;
                head = new_node;
            } else if (current == nullptr) {
                // Insertar al final
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            } else {
                // Insertar en medio
                new_node->next = current;
                new_node->prev = current->prev;
                current->prev->next = new_node;
                current->prev = new_node;
            }
        }
        list_size++;
    }

    // Elimina un valor
    void erase(const T& value) {
        Node* current = head;
        while (current != nullptr && current->data != value) {
            current = current->next;
        }
        if (current == nullptr) {
            std::cout << "Value not found in the list." << std::endl;
            return;
        }
        if (current == head) {
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
        } else if (current == tail) {
            tail = tail->prev;
            if (tail != nullptr) tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        delete current;
        list_size--;
    }

    // Encuentra un nodo por su valor
    Node* find(const T& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Imprime los valores de la lista
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Retorna true si la lista está vacía
    bool empty() const {
        return list_size == 0;
    }

    // Retorna el tamaño de la lista
    std::size_t size() const {
        return list_size;
    }
};

#endif
