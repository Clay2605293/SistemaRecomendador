#ifndef SEQUENTIAL_SEARCH_TITLE_HPP
#define SEQUENTIAL_SEARCH_TITLE_HPP

#include "../dataStructure/OrderedList.hpp"
#include "../anime.hpp"
#include "toLower.hpp"
#include <string>

int sequentialSearchTitle(const OrderedList<Anime>& list, const std::string& target) {
    std::string lowerTarget = toLower(target); // Convertir el título objetivo a minúsculas

    for (int i = 0; i < list.size(); ++i) {
        std::string animeTitle = toLower(list.get(i).name); // Convertir el título actual a minúsculas
        if (animeTitle == lowerTarget) { // Comparación insensible a mayúsculas
            return i;
        }
    }
    return -1; // Si no se encuentra el título
}

#endif
