#include "anime.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/queue.hpp"
#include "dataStructure/stack.hpp"
#include "dataStructure/dynamicArray.hpp"
#include "searchAlgorithm/binarySearch.hpp"
#include "utilities.hpp"
#include <chrono>

using namespace std::chrono;

void testStoragePerformence(LinkedList<Anime>& linkedList, DoublyLinkedList<Anime>& doublyLinkedList, Queue<Anime>& queue, Stack<Anime>& stack, DynamicArray<Anime>& dynamicArray)
{
    // Leer el archivo CSV y almacenar los objetos Anime en las estructuras
    
    string filename = "anime.csv";
    
    // Linked List
    std::cout << "Linked List: " << endl;
    auto start = high_resolution_clock::now();
    readCSV(filename, linkedList);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "Miliseconds: " << duration.count() << endl;
    std::cout << "############################################" << endl;

    // Doubly Linked List
    std::cout << "Doubly Linked List" << endl;
    auto start1 = high_resolution_clock::now();
    readCSV(filename, doublyLinkedList);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);
    std::cout << "Miliseconds: " << duration1.count() << endl;
    std::cout << "############################################" << endl;

    // Queue
    std::cout << "Queue" << endl;
    auto start2 = high_resolution_clock::now();
    readCSV(filename, queue);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);
    std::cout << "Miliseconds: " << duration2.count() << endl;
    std::cout << "############################################" << endl;
    
    // Stack
    std::cout << "Stack" << endl;
    auto start3 = high_resolution_clock::now();
    readCSV(filename, stack);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(stop3 - start3);
    std::cout << "Miliseconds: " << duration3.count() << endl;
    std::cout << "############################################" << endl;

    // Dynamic Array
    std::cout << "Dynamic Array" << endl;
    auto start4 = high_resolution_clock::now();
    readCSV(filename, dynamicArray);
    auto stop4 = high_resolution_clock::now();
    auto duration4 = duration_cast<seconds>(stop4 - start4);
    std::cout << "Seconds: " << duration4.count() << endl;
    std::cout << "############################################" << endl;
    
    return;
}

int main() {
    // Crear instancias de las estructuras de datos
    LinkedList<Anime> linkedList;
    DoublyLinkedList<Anime> doublyLinkedList;
    Queue<Anime> queue;
    Stack<Anime> stack;
    DynamicArray<Anime> dynamicArray;

    // Test the performance of the storage structures
    testStoragePerformence(linkedList, doublyLinkedList, queue, stack, dynamicArray);
    

    // Mostrar el contenido de las estructuras
    linkedList.front().display();
    doublyLinkedList.front().display();
    stack.top().display();
    queue.front().display();
    dynamicArray[5].display();
    return 0;
}
