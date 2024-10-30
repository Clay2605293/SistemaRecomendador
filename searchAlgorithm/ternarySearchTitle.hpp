#ifndef TERNARY_SEARCH_TITLE_HPP
#define TERNARY_SEARCH_TITLE_HPP

#include "../dataStructure/OrderedList.hpp"
#include "../anime.hpp"
#include "toLower.hpp"
#include <string>

int ternarySearchTitle(const OrderedList<Anime>& list, const std::string& target, int left, int right) {
    std::string lowerTarget = toLower(target); // Convertir el título objetivo a minúsculas

    if (right >= left) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        // Convertir los títulos en los índices mid1 y mid2 a minúsculas para la comparación
        std::string titleMid1 = toLower(list.get(mid1).name);
        std::string titleMid2 = toLower(list.get(mid2).name);

        if (titleMid1 == lowerTarget) { // Comparación con el primer tercio
            return mid1;
        }
        if (titleMid2 == lowerTarget) { // Comparación con el segundo tercio
            return mid2;
        }

        if (lowerTarget < titleMid1) {
            return ternarySearchTitle(list, target, left, mid1 - 1);
        }
        else if (lowerTarget > titleMid2) {
            return ternarySearchTitle(list, target, mid2 + 1, right);
        }
        else {
            return ternarySearchTitle(list, target, mid1 + 1, mid2 - 1);
        }
    }

    return -1; // Si no se encuentra el título
}

int ternarySearchTitle(const OrderedList<Anime>& list, const std::string& target) {
    return ternarySearchTitle(list, target, 0, list.size() - 1);
}

#endif
