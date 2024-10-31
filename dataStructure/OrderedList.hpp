#ifndef ORDERED_LIST_HPP
#define ORDERED_LIST_HPP

#include <iostream>        // Para std::cout
#include <initializer_list> // Para std::initializer_list
#include <cstddef>          // Para std::size_t
#include <string>
#include "../searchAlgorithm/toLower.hpp"      // Asegúrate de tener la función toLower

template <typename T>
class OrderedList {
public:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head;
    std::size_t list_size;

    // Constructor por defecto
    OrderedList() : head(nullptr), list_size(0) {}

    // Destructor
    ~OrderedList() {
        clear();
    }

    // Constructor de copia
    OrderedList(const OrderedList& other) : head(nullptr), list_size(0) {
        copy_from(other);
    }

    // Operador de asignación
    OrderedList& operator=(const OrderedList& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    // Constructor con lista de inicialización
    OrderedList(std::initializer_list<T> values) : head(nullptr), list_size(0) {
        for (const T& value : values) {
            insert(value);
        }
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
        list_size = 0;
    }

    // Inserta un valor de forma ordenada
    void insert(const T& value) {
        Node* new_node = new Node(value);

        // Comparar por el campo `name` del objeto Anime, en minúsculas
        if (!head || toLower(head->data.name) >= toLower(value.name)) {
            new_node->next = head;
            head = new_node;
        } else {
            Node* current = head;
            while (current->next && toLower(current->next->data.name) < toLower(value.name)) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
        list_size++;
    }


    // Método para obtener un nodo en una posición específica
    const T& get(std::size_t index) const {
        Node* current = head;
        for (std::size_t i = 0; i < index && current != nullptr; ++i) {
            current = current->next;
        }
        if (current == nullptr) {
            throw std::out_of_range("Índice fuera de rango");
        }
        return current->data;
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

    // Método para verificar si la lista está ordenada
    void verificarOrden() const {
        Node* current = head;
        bool ordenado = true;
        while (current && current->next) {
            if (toLower(current->data.name) > toLower(current->next->data.name)) {
                std::cout << "Desorden detectado entre: " << current->data.name 
                          << " y " << current->next->data.name << std::endl;
                ordenado = false;
            }
            current = current->next;
        }
        if (ordenado) {
            std::cout << "La lista está ordenada correctamente.\n";
        } else {
            std::cout << "La lista tiene elementos fuera de orden.\n";
        }
    }

private:
    // Función auxiliar para copiar otra lista
    void copy_from(const OrderedList& other) {
        Node* current = other.head;
        while (current) {
            insert(current->data);
            current = current->next;
        }
    }
};

#endif
