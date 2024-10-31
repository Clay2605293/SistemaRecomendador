#ifndef BINARY_SEARCH_TITLE_HPP
#define BINARY_SEARCH_TITLE_HPP

#include "../dataStructure/dynamicArray.hpp" // Incluye DynamicArray en lugar de OrderedList
#include "../anime.hpp"
#include "toLower.hpp"
#include <string>
#include <algorithm>

int binarySearchTitle(const DynamicArray<Anime>& array, const std::string& target, int high, int low) {
    std::string lowerTarget = toLower(target);

    if (high >= low) {
        int mid = low + (high - low) / 2;
        std::string animeTitle = toLower(array[mid].name); // Acceso directo usando `[]` y convertir a minúsculas

        if (animeTitle == lowerTarget) { // Compara el título en minúsculas
            return mid; // Retorna el índice del elemento encontrado
        } 
        else if (animeTitle > lowerTarget) { // Orden lexicográfico en minúsculas
            return binarySearchTitle(array, target, mid - 1, low); // Llamada recursiva ajustada para `array`
        } 
        else {
            return binarySearchTitle(array, target, high, mid + 1); // Llamada recursiva ajustada para `array`
        }
    }

    return -1; // Si no se encuentra el título
}

// Función sobrecargada para iniciar la búsqueda binaria
int binarySearchTitle(const DynamicArray<Anime>& array, const std::string& target) {
    return binarySearchTitle(array, target, array.size() - 1, 0);
}

#endif
