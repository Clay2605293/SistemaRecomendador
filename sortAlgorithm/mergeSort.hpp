#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include "../dataStructure/dynamicArray.hpp"
#include "../anime.hpp"

template<typename T>
void merge(DynamicArray<Anime>& data, DynamicArray<T>& aux, unsigned int left, unsigned int middle,  unsigned int right)
{
    unsigned int i = left;
    unsigned int j = middle + 1;
    unsigned int k = left;

    // Merge arrays
    while (i <= middle && j <= right)
    {
        if (data[i] <= data[j])
        {
            aux[k++] = data[i++];
        }
        else
        {
            aux[k++] = data[j++];
        }
    }

    // Copy the rest of elements of the left side
    while (i <= middle)
    {
        aux[k++] = data[i++];
    }

    // Copy the rest of elements of the right side
    while (j <= right)
    {
        aux[k++] = data[j++];
    }

    // Copy the elements to the original array
    for (i = left; i <= right; ++i)
    {
        data[i] = aux[i];
    }
    
}


template<typename T>
void mergeSort(DynamicArray<Anime>& data, DynamicArray<Anime>& aux, unsigned int left, unsigned int right)
{
    if (left < right)
    {
        unsigned int middle = left + (right - left) / 2;

        // Sort the first subarray
        mergeSort(data, aux, left, middle);

        // Sort the second subarray
        mergeSort(data, aux, middle + 1, right);

        // Merge the sorted subarrays
        merge(data, aux, left, middle, right);
    }   
}

void mergeSort(DynamicArray<Anime>& data)
{
    DynamicArray<Anime> aux(data.size());
    //mergeSort(data, aux, 0, data.size() - 1);
}

#endif