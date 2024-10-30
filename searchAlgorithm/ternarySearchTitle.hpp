#ifndef TERNARY_SEARCH_TITLE_HPP
#define TERNARY_SEARCH_TITLE_HPP

#include "../dataStructure/OrderedList.hpp"
#include "../anime.hpp"
#include "toLower.hpp" // Asegúrate de tener el archivo de conversión a minúsculas
#include <string>
#include <iostream>

// Función para realizar búsqueda ternaria
int ternarySearchTitle(const OrderedList<Anime>& list, const std::string& target, int left, int right) {
    std::string lowerTarget = toLower(target); // Convertir el objetivo a minúsculas

    if (right >= left) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        std::string animeTitle1 = toLower(list.get(mid1).name); // Convertir a minúsculas para comparación
        std::string animeTitle2 = toLower(list.get(mid2).name); // Convertir a minúsculas para comparación


        // Verificación directa en los dos puntos medios
        if (animeTitle1 == lowerTarget) return mid1;
        if (animeTitle2 == lowerTarget) return mid2;

        // Ajuste: Si el target podría estar entre mid1 y mid2, recorrer ese rango en secuencia para precisión
        if (lowerTarget > animeTitle1 && lowerTarget < animeTitle2) {
            for (int i = mid1 + 1; i < mid2; ++i) {
                if (toLower(list.get(i).name) == lowerTarget) {
                    return i;
                }
            }
            return -1;
        }

        // Divisiones en el primer y tercer tercios
        if (lowerTarget < animeTitle1) {
            return ternarySearchTitle(list, target, left, mid1 - 1);
        }
        if (lowerTarget > animeTitle2) {
            return ternarySearchTitle(list, target, mid2 + 1, right);
        }
    }

    return -1; // Si no se encuentra el título
}

// Función de búsqueda pública
int ternarySearchTitle(const OrderedList<Anime>& list, const std::string& target) {
    return ternarySearchTitle(list, target, 0, list.size() - 1);
}

#endif
