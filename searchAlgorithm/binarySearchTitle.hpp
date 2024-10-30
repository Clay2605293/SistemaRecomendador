#ifndef BINARY_SEARCH_TITLE_HPP
#define BINARY_SEARCH_TITLE_HPP

#include "../dataStructure/OrderedList.hpp"
#include "../anime.hpp"
#include "toLower.hpp"
#include <string>
#include <algorithm>

int binarySearchTitle(const OrderedList<Anime>& list, const std::string& target, int high, int low) {
    std::string lowerTarget = toLower(target);

    if (high >= low) {
        int mid = low + (high - low) / 2;
        std::string animeTitle = toLower(list.get(mid).name); // Convertimos a minúsculas

        if (animeTitle == lowerTarget) { // Compara el título en minúsculas
            return mid; // Retorna el índice del elemento encontrado
        } 
        else if (animeTitle > lowerTarget) { // Orden lexicográfico en minúsculas
            return binarySearchTitle(list, target, mid - 1, low); // Usamos `target` en la recursión
        } 
        else {
            return binarySearchTitle(list, target, high, mid + 1); // Usamos `target` en la recursión
        }
    }

    return -1; // Si no se encuentra el título
}

int binarySearchTitle(const OrderedList<Anime>& list, const std::string& target) {
    return binarySearchTitle(list, target, list.size() - 1, 0);
}

#endif
