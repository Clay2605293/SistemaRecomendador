#ifndef SEQUENTIAL_SEARCH_TITLE_HPP
#define SEQUENTIAL_SEARCH_TITLE_HPP

#include "../dataStructure/dynamicArray.hpp" // Incluye DynamicArray en lugar de OrderedList
#include "../anime.hpp"
#include "toLower.hpp"
#include <string>

int sequentialSearchTitle(const DynamicArray<Anime>& array, const std::string& target) {
    std::string lowerTarget = toLower(target); // Convertir el título objetivo a minúsculas

    for (int i = 0; i < array.size(); ++i) {
        std::string animeTitle = toLower(array[i].name); // Acceso directo al título usando array[i]
        if (animeTitle == lowerTarget) { // Comparación insensible a mayúsculas
            return i;
        }
    }
    return -1; // Si no se encuentra el título
}

#endif
