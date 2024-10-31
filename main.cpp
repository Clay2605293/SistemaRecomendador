#include "anime.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/queue.hpp"
#include "dataStructure/stack.hpp"
#include "dataStructure/dynamicArray.hpp"
#include "dataStructure/OrderedList.hpp"
#include "dataStructure/PriorityQueue.hpp"
#include "sortAlgorithm/quickSort.hpp"
#include "utilities.hpp"
#include <iostream>
#include <iomanip>

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
    testStoragePerformance(linkedList, doublyLinkedList, dynamicArray, priorityQueue); 

    sortDynamicArrayByName(dynamicArray);

    dynamicArray.verificarOrden();

    DynamicArray<std::string> uniqueGenres;
    extractUniqueGenres("anime.csv", uniqueGenres);

    std::cout << "Categorías únicas en el archivo:\n";
    for (int i = 0; i < uniqueGenres.size(); ++i) {
        std::cout << uniqueGenres[i] << std::endl;
    }

    DynamicArray<PriorityQueue<Anime>> genreQueues = initializeGenrePriorityQueues(uniqueGenres);
    assignAnimesToGenreQueues(dynamicArray, uniqueGenres, genreQueues);

    //Imprimir la cantidad de animes por género para verificar
    for (int i = 0; i < uniqueGenres.size(); ++i) {
        std::cout << "Género: " << uniqueGenres[i] << ", Animes en la cola: " << genreQueues[i].size() << std::endl;
    }

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
                
                int searchType;
                std::cout << "Seleccione el tipo de búsqueda (1: Secuencial, 2: Binaria, 3: Ternaria): ";
                std::cin >> searchType;

                buscarAnimePorTitulo(dynamicArray, titulo, searchType);
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
                std::cout << "Seleccione una categoría (teclea el número):\n\n";
                
                // Mostrar las categorías en una tabla de 4 columnas
                for (int i = 0; i < uniqueGenres.size(); ++i) {
                    std::cout << std::setw(3) << i + 1 << ". " << std::setw(20) << std::left << uniqueGenres[i];  // Ajusta el ancho para alinear columnas
                    
                    // Insertar salto de línea cada 4 categorías para formar una nueva fila
                    if ((i + 1) % 4 == 0) {
                        std::cout << "\n";
                    }
                }

                // Asegurarse de que no quede una línea incompleta sin salto
                if (uniqueGenres.size() % 4 != 0) {
                    std::cout << "\n";
                }

                int categoriaIndex;
                std::cout << "\nIngrese el número de la categoría: ";
                std::cin >> categoriaIndex;

                // Validar la entrada del usuario
                if (categoriaIndex < 1 || categoriaIndex > uniqueGenres.size()) {
                    std::cout << "Número inválido. Intente de nuevo.\n";
                    break;
                }

                // Obtener la PriorityQueue correspondiente a la categoría elegida
                PriorityQueue<Anime>& selectedQueue = genreQueues[categoriaIndex - 1];
                std::string selectedCategory = uniqueGenres[categoriaIndex - 1];

                std::cout << "Mostrando los 5 mejores animes en la categoría: " << selectedCategory << "\n";
                int count = 0;

                // Mostrar los 5 mejores animes
                while (!selectedQueue.empty() && count < 5) {
                    Anime topAnime = selectedQueue.top();  // Obtener el anime con mayor prioridad
                    selectedQueue.pop();  // Eliminar el anime mostrado para avanzar al siguiente

                    topAnime.display();  // Llamar a la función display para mostrar detalles
                    std::cout << "------------------------------------\n";
                    ++count;
                }
                
                if (count == 0) {
                    std::cout << "No se encontraron animes en la categoría seleccionada.\n";
                }
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
