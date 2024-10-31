#ifndef TERNARY_SEARCH_TITLE_HPP
#define TERNARY_SEARCH_TITLE_HPP

#include "../dataStructure/dynamicArray.hpp"
#include "../anime.hpp"
#include "toLower.hpp" 
#include <string>
#include <iostream>

// Función para realizar búsqueda ternaria con ajustes en las divisiones
int ternarySearchTitle(const DynamicArray<Anime>& array, const std::string& target, int left, int right) {
    std::string lowerTarget = toLower(target);

    if (right >= left) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        std::string animeTitle1 = toLower(array[mid1].name);
        std::string animeTitle2 = toLower(array[mid2].name);

        // Comparación directa en los puntos medios
        if (animeTitle1 == lowerTarget) return mid1;
        if (animeTitle2 == lowerTarget) return mid2;

        // Ajuste de rango para una cobertura completa entre mid1 y mid2
        if (lowerTarget < animeTitle1) {
            return ternarySearchTitle(array, target, left, mid1 - 1);
        } else if (lowerTarget > animeTitle2) {
            return ternarySearchTitle(array, target, mid2 + 1, right);
        } else {
            // Búsqueda lineal en el rango estrecho entre mid1 y mid2
            for (int i = mid1 + 1; i < mid2; ++i) {
                if (toLower(array[i].name) == lowerTarget) {
                    return i;
                }
            }
            return -1;  // Retorna -1 si no se encuentra en el rango medio
        }
    }

    return -1;
}

// Función pública de búsqueda
int ternarySearchTitle(const DynamicArray<Anime>& array, const std::string& target) {
    return ternarySearchTitle(array, target, 0, array.size() - 1);
}

#endif
