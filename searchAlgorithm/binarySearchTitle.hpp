#ifndef BINARY_SEARCH_TITLE_HPP
#define BINARY_SEARCH_TITLE_HPP

#include "../dataStructure/OrderedList.hpp"
#include "../anime.hpp"
#include <string>

int binarySearchTitle(const OrderedList<Anime>& list, const std::string& target, int high, int low) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (list.get(mid).name == target) { // Compara el título del anime usando get
            return mid; // Retorna el índice del elemento encontrado
        } 
        else if (list.get(mid).name > target) { // Orden lexicográfico
            return binarySearchTitle(list, target, mid - 1, low);
        } 
        else {
            return binarySearchTitle(list, target, high, mid + 1);
        }
    }

    return -1; // Si no se encuentra el título
}

int binarySearchTitle(const OrderedList<Anime>& list, const std::string& target) {
    return binarySearchTitle(list, target, list.size() - 1, 0);
}

#endif
