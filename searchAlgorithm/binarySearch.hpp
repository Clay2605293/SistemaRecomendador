#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include "../dataStructure/dynamicArray.hpp"
#include "../anime.hpp"

template<typename T>
int binarySearch(const DynamicArray<Anime>& array, const T& target, int high, int low)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;

        if (target == array[mid].anime_id)
        {
            return mid;
        }
        else if (target < array[mid].anime_id)   
        {
            return binarySearch(array, target, mid - 1, low);
        }
        else if (target > array[mid].anime_id)
        {
             return binarySearch(array, target, high, mid + 1);
        }
    }

    return -1;
}

template<typename T>
int binarySearch(const DynamicArray<Anime>& array, const T& target)
{
    return binarySearch(array, target, array.size() - 1, 0);
}


#endif