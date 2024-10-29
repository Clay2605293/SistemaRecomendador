#include "anime.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/queue.hpp"
#include "dataStructure/stack.hpp"
#include "dataStructure/dynamicArray.hpp"
#include "dataStructure/OrderedList.hpp"
#include "dataStructure/PriorityQueue.hpp"
#include "utilities.hpp"
#include <iostream>
#include "searchAlgorithm/binarySearchTitle.hpp"



void mostrarMenuPrincipal() {
    std::cout << "\n--- Sistema Recomendador de Anime ---\n";
    std::cout << "1. Buscar anime por título\n";
    std::cout << "2. Ver animes mejor calificados\n";
    std::cout << "3. Ver animes por categoría\n";
    std::cout << "4. Generar recomendaciones personalizadas\n";
    std::cout << "5. Salir\n";
    std::cout << "Seleccione una opción: ";
}

void mostrarSubmenuMejorCalificado() {
    std::cout << "\n--- Ver Animes Mejor Calificados ---\n";
    std::cout << "1. Ver el mejor calificado de todos\n";
    std::cout << "2. Ver mejor calificado por categoría\n";
    std::cout << "3. Regresar al menú principal\n";
    std::cout << "Seleccione una opción: ";
}

int main() {
    LinkedList<Anime> linkedList;
    DoublyLinkedList<Anime> doublyLinkedList;
    Queue<Anime> queue;
    Stack<Anime> stack;
    DynamicArray<Anime> dynamicArray;
    OrderedList<Anime> orderedList;
    PriorityQueue<Anime> priorityQueue;

    // Cargar la base de datos en las estructuras
    testStoragePerformance(linkedList, doublyLinkedList, queue, stack, dynamicArray, orderedList, priorityQueue); 

    DynamicArray<std::string> uniqueGenres;
    extractUniqueGenres("anime.csv", uniqueGenres);

    std::cout << "Categorías únicas en el archivo:\n";
    for (int i = 0; i < uniqueGenres.size(); ++i) {
        std::cout << uniqueGenres[i] << std::endl;
    }

    std::cout << "Total de categorías únicas: " << uniqueGenres.size() << std::endl;


    int opcionPrincipal;
    do {
        
        mostrarMenuPrincipal();
        std::cin >> opcionPrincipal;
        // Validación de entrada
        if (std::cin.fail()) {
            std::cin.clear(); // Restablece el estado de cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el buffer
            std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
            continue; // Repite el ciclo sin ejecutar el switch
        }

        switch (opcionPrincipal) {
            case 1: {
                std::cout << "Buscar anime por título\n";
                std::string titulo;
                std::cout << "Ingrese el título del anime: ";
                std::cin.ignore();
                std::getline(std::cin, titulo);
                
                // Llamar a la función para buscar por título usando OrderedList
                buscarAnimePorTitulo(orderedList, titulo);
                break;
            }
            case 2: {
                int opcionSubmenu;
                do {
                    mostrarSubmenuMejorCalificado();
                    std::cin >> opcionSubmenu;
                    switch (opcionSubmenu) {
                        case 1:
                            std::cout << "Mostrando el anime mejor calificado de todos...\n";
                            // Llamar a la función para obtener el mejor calificado de todos
                            // Ejemplo: mostrarMejorCalificadoDeTodos(linkedList);
                            break;
                        case 2: {
                            std::cout << "Ingrese la categoría: ";
                            std::string categoria;
                            std::cin.ignore();
                            std::getline(std::cin, categoria);
                            std::cout << "Mostrando el mejor calificado en la categoría: " << categoria << "\n";
                            // Llamar a la función para mostrar el mejor calificado por categoría
                            // Ejemplo: mostrarMejorCalificadoPorCategoria(linkedList, categoria);
                            break;
                        }
                        case 3:
                            std::cout << "Regresando al menú principal...\n";
                            break;
                        default:
                            std::cout << "Opción inválida. Por favor, intente nuevamente.\n";
                    }
                } while (opcionSubmenu != 3);
                break;
            }
            case 3: {
                std::cout << "Ver animes por categoría\n";
                std::string categoria;
                std::cout << "Ingrese la categoría: ";
                std::cin.ignore();
                std::getline(std::cin, categoria);
                // Llamar a la función para mostrar animes por categoría
                // Ejemplo: mostrarAnimesPorCategoria(linkedList, categoria);
                break;
            }
            case 4:
                std::cout << "Generando recomendaciones personalizadas...\n";
                // Llamar a la función para recomendaciones basadas en el interés del usuario
                // Ejemplo: generarRecomendaciones(linkedList, preferenciasUsuario);
                break;

            case 5:
                std::cout << "Saliendo...\n";
                break;

            default:
                std::cout << "Opción inválida. Por favor, intente nuevamente.\n";
        }
    } while (opcionPrincipal != 5);

    return 0;
}
