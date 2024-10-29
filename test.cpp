#include "ut.hpp"
#include "dataStructure/dynamicArray.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/OrderedList.hpp"
#include "dataStructure/PriorityQueue.hpp"
#include "anime.hpp"
#include <cstdio>
#include <iostream>

int main()
{
    DynamicArray<Anime> array;
    LinkedList<Anime> list;
    OrderedList<Anime> order;
    PriorityQueue<Anime> prior;
    extractDataFromCSV("anime.csv", array);
    array[1].display();
}
