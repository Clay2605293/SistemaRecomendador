#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "../dataStructure/dynamicArray.hpp"
#include "../anime.hpp"
#include "../searchAlgorithm/toLower.hpp"

// Función para intercambiar dos elementos en DynamicArray<Anime>
void swap(DynamicArray<Anime>& array, int i, int j) {
    Anime temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

// Función para la partición en QuickSort, insensible a mayúsculas
int partition(DynamicArray<Anime>& array, int low, int high) {
    std::string pivotName = toLower(array[high].name); // Convertir el pivote a minúsculas
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (toLower(array[j].name) < pivotName) { // Comparar el nombre en minúsculas
            i++;
            swap(array, i, j);
        }
    }
    swap(array, i + 1, high);
    return i + 1;
}

// QuickSort recursivo para DynamicArray<Anime>
void quickSort(DynamicArray<Anime>& array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

// Función para ordenar el DynamicArray<Anime> por nombre usando QuickSort
void sortDynamicArrayByName(DynamicArray<Anime>& array) {
    if (array.size() > 1) {
        quickSort(array, 0, array.size() - 1);
    }
}

// --- Funciones para ordenar otros tipos con campo 'nombre' ---

// Función para intercambiar dos elementos en DynamicArray<T>
template <typename T>
void swap(DynamicArray<T>& array, int i, int j) {
    T temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

// Función de partición para DynamicArray<T>
template <typename T>
int partition(DynamicArray<T>& array, int low, int high) {
    std::string pivot = toLower(array[high].nombre);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (toLower(array[j].nombre) < pivot) {
            i++;
            swap(array, i, j);
        }
    }
    swap(array, i + 1, high);
    return i + 1;
}

// QuickSort recursivo para DynamicArray<T>
template <typename T>
void quickSortCategorias(DynamicArray<T>& array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSortCategorias(array, low, pi - 1);
        quickSortCategorias(array, pi + 1, high);
    }
}

// Función para ordenar cualquier DynamicArray<T> por el campo 'nombre' usando QuickSort
template <typename T>
void quickSortCategorias(DynamicArray<T>& array) {
    if (array.size() > 1) {
        quickSortCategorias(array, 0, array.size() - 1);
    }
}

#endif // QUICKSORT_HPP
