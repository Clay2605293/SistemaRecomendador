#include "anime.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/queue.hpp"
#include "dataStructure/stack.hpp"
#include "utils.hpp"

using namespace std;

int main() {
    // Crear instancias de las estructuras de datos
    LinkedList<Anime> linkedList;
    DoublyLinkedList<Anime> doublyLinkedList;
    Queue<Anime> queue;
    Stack<Anime> stack;

    // Leer el archivo CSV y almacenar los objetos Anime en las estructuras
    string filename = "anime.csv";
    readCSV(filename, linkedList, doublyLinkedList, queue, stack);
    

    return 0;
}
