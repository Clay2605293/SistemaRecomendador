#include "anime.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/queue.hpp"
#include "dataStructure/stack.hpp"
#include "dataStructure/dynamicArray.hpp"
#include "dataStructure/OrderedList.hpp"
#include "dataStructure/PriorityQueue.hpp"
#include "searchAlgorithm/binarySearchTitle.hpp"
#include "sortAlgorithm/quickSort.hpp"
#include "utilities.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

void mostrarMenuPrincipal() {
    std::cout << "\n--- Sistema Recomendador de Anime ---\n";
    std::cout << "1. Buscar anime por título\n";
    std::cout << "2. Ver animes mejor calificados en general\n";
    std::cout << "3. Ver animes mejor calificados por categoría\n";
    std::cout << "4. Ver animes mejor calificados por tipos\n";
    std::cout << "5. Generar recomendaciones personalizadas\n";
    std::cout << "6. Salir\n";
    std::cout << "Seleccione una opción: ";
}

void mostrarSubmenuMejorCalificado() {
    std::cout << "\n--- Ver Animes Mejor Calificados ---\n";
    std::cout << "1. Usar Priority List\n";
    std::cout << "2. Usar Ordered List\n";
    std::cout << "3. Regresar al menú principal\n";
    std::cout << "Seleccione una opción: ";
}



int main() {
    LinkedList<Anime> linkedList;
    DoublyLinkedList<Anime> doublyLinkedList;
    Queue<Anime> queue;
    Stack<Anime> stack;
    DynamicArray<Anime> dynamicArray;
    PriorityQueue<Anime> priorityQueue;

    // Cargar la base de datos en las estructuras
    testStoragePerformance(linkedList, doublyLinkedList, dynamicArray, priorityQueue); 

    sortDynamicArrayByName(dynamicArray);

    DynamicArray<Anime> copiedArray = dynamicArray;

    dynamicArray.verificarOrden();

    copiedArray.verificarOrden();

    DynamicArray<std::string> uniqueGenres;
    extractUniqueGenres("anime.csv", uniqueGenres);

    std::cout << "Categorías únicas en el archivo:\n";
    for (int i = 0; i < uniqueGenres.size(); ++i) {
        std::cout << uniqueGenres[i] << std::endl;
    }
    
    DynamicArray<std::string> uniqueTypes;
    extractUniqueTypes("anime.csv", uniqueTypes);

    for (int i = 0; i < uniqueTypes.size(); ++i) {
        std::cout << uniqueTypes[i] << std::endl;
    }

    // Generar lista unicas y hacer las categorias
    DynamicArray<PriorityQueue<Anime>> genreQueues = initializeGenrePriorityQueues(uniqueGenres);
    assignAnimesToGenreQueues(dynamicArray, uniqueGenres, genreQueues);
    
    DynamicArray<PriorityQueue<Anime>> typeQueues = initializeGenrePriorityQueues(uniqueTypes);
    assignAnimesToTypesQueue(dynamicArray, uniqueTypes, typeQueues);
    
    LinkedList<PriorityQueue<Anime>> genreQueuesL = initializeGenrePriorityQueuesLinkedList(uniqueGenres);
    assignAnimesToGenreQueues(dynamicArray, uniqueGenres, genreQueuesL);
    
    DoublyLinkedList<PriorityQueue<Anime>> genreQueuesD = initializeGenrePriorityQueuesDoblyList(uniqueGenres);
    assignAnimesToGenreQueues(dynamicArray, uniqueGenres, genreQueuesD);
    
    //Stack<PriorityQueue<Anime>> genreQueuesS = initializeGenrePriorityQueuesStack(uniqueGenres);
    //assignAnimesToGenreQueues(dynamicArray, uniqueGenres, genreQueuesS);

    // Solo para debugear
    std::cout << std::endl;
    std::cout << "Pruebas de estructuras" << std::endl;
    measureDynamicPriorityQueue(genreQueues);
    measureLinkedListPriorityQueue(genreQueuesL);
    measureDoublyLinkedListPriorityQueue(genreQueuesD);
    //genreQueuesS.top().top().display();


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
                        case 1: {
                            auto start = std::chrono::high_resolution_clock::now();
                            std::cout << "Mostrando los 5 animes mejor calificados de todos...\n";
                            PriorityQueue<Anime> tempQueueGeneral = priorityQueue;

                            int count = 0;
                            while (!tempQueueGeneral.empty() && count < 5) {
                                Anime topAnime = tempQueueGeneral.top();  
                                tempQueueGeneral.pop(); 

                                topAnime.display(); 
                                std::cout << "------------------------------------\n";
                                ++count;
                            }

                            if (count == 0) {
                                std::cout << "No se encontraron animes.\n";
                            }
                            auto end = std::chrono::high_resolution_clock::now();
                            std::cout << "Time for PriorityQueue: " 
                                    << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() 
                                    << " ns\n";
                            break;
                        }
                        case 2: {
                            auto start = std::chrono::high_resolution_clock::now();
                            OrderedList<Anime> orderedListGeneral;
                            
                            // Llenar la OrderedList desde el DynamicArray ordenado por rating
                            for (int i = 0; i < dynamicArray.size(); ++i) {
                                orderedListGeneral.insert(dynamicArray[i]);
                            }

                            std::cout << "Mostrando los 5 mejores animes:\n";
                            for (std::size_t i = 0; i < orderedListGeneral.size() && i < 5; ++i) {
                                try {
                                    const Anime& topAnime = orderedListGeneral.get(i);
                                    topAnime.display();
                                    std::cout << "------------------------------------\n";
                                } catch (const std::out_of_range&) {
                                    std::cout << "Error: Índice fuera de rango al intentar acceder a la OrderedList.\n";
                                }
                            }
                                                        auto end = std::chrono::high_resolution_clock::now();
                            std::cout << "Time for OrderedList: " 
                                    << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() 
                                    << " ns\n";
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
                    std::cout << std::setw(3) << i + 1 << ". " << std::setw(20) << std::left << uniqueGenres[i];
                    if ((i + 1) % 4 == 0) {
                        std::cout << "\n";
                    }
                }
                if (uniqueGenres.size() % 4 != 0) {
                    std::cout << "\n";
                }

                int categoriaIndex;
                std::cout << "\nIngrese el número de la categoría: ";
                std::cin >> categoriaIndex;

                if (categoriaIndex < 1 || categoriaIndex > uniqueGenres.size()) {
                    std::cout << "Número inválido. Intente de nuevo.\n";
                    break;
                }

                // Copiar PriorityQueue para no modificar la original
                PriorityQueue<Anime> tempQueue = genreQueues[categoriaIndex - 1];
                std::string selectedCategory = uniqueGenres[categoriaIndex - 1];

                std::cout << "Mostrando los 5 mejores animes en la categoría: " << selectedCategory << "\n";
                int count = 0;

                // Mostrar los 5 mejores animes
                while (!tempQueue.empty() && count < 5) {
                    Anime topAnime = tempQueue.top();
                    tempQueue.pop();  // Elimina de la copia temporal

                    topAnime.display();  // Llamar a la función display para mostrar detalles
                    std::cout << "------------------------------------\n";
                    ++count;
                }
                
                if (count == 0) {
                    std::cout << "No se encontraron animes en la categoría seleccionada.\n";
                }
                break;
            }


            case 4: {
                std::cout << "Seleccione un tipo (teclea el número):\n\n";
                
                // Mostrar los tipos en una tabla de 4 columnas
                for (int i = 0; i < uniqueTypes.size(); ++i) {
                    std::cout << std::setw(3) << i + 1 << ". " << std::setw(20) << std::left << uniqueTypes[i];
                    
                    // Insertar salto de línea cada 4 tipos para formar una nueva fila
                    if ((i + 1) % 4 == 0) {
                        std::cout << "\n";
                    }
                }

                if (uniqueTypes.size() % 4 != 0) {
                    std::cout << "\n";
                }

                int tipoIndex;
                std::cout << "\nIngrese el número del tipo: ";
                std::cin >> tipoIndex;

                // Validar la entrada del usuario
                if (tipoIndex < 1 || tipoIndex > uniqueTypes.size()) {
                    std::cout << "Número inválido. Intente de nuevo.\n";
                    break;
                }

                // Copiar PriorityQueue para no modificar la original
                PriorityQueue<Anime> tempQueue = typeQueues[tipoIndex - 1];
                std::string selectedType = uniqueTypes[tipoIndex - 1];

                std::cout << "Mostrando los 5 mejores animes en el tipo: " << selectedType << "\n";
                int count = 0;

                // Mostrar los 5 mejores animes sin modificar la cola original
                while (!tempQueue.empty() && count < 5) {
                    Anime topAnime = tempQueue.top();  // Obtener el anime con mayor prioridad
                    tempQueue.pop();  // Removerlo de la cola temporal

                    topAnime.display();  // Mostrar detalles
                    std::cout << "------------------------------------\n";
                    ++count;
                }

                if (count == 0) {
                    std::cout << "No se encontraron animes con el tipo seleccionado.\n";
                }
                break;
            }

            case 5: {
                std::cout << "Generar recomendaciones personalizadas\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // Pedir al usuario los nombres de 5 animes que le gusten
                DynamicArray<Anime> animesFavoritos;
                std::cout << "Ingresa el nombre de 5 animes que te gusten:\n";
                int index = -1;
                
                for (int i = 0; i < 5; ++i) {
                    std::cin.clear();
                    std::string animeNombre;
                    std::cout << "Anime " << i + 1 << ": ";
                    std::getline(std::cin, animeNombre);

                    index = regresarindexRecom(copiedArray, animeNombre);

                    if (index != -1) {
                        animesFavoritos.push_back(copiedArray[index]);
                        index = -1;
                    } else {
                        std::cout << "Anime no encontrado en la base de datos.\n";
                    }
                }


                // Verificar que tenemos animes válidos para recomendar
                if (animesFavoritos.size() == 0) {
                    std::cout << "No se encontraron los animes proporcionados. No se pueden generar recomendaciones.\n";
                    break;
                }

               // Después de recolectar las categorías
                DynamicArray<CategoriaFrecuencia> categoriaFrecuencia = recolectarCategorias(animesFavoritos);

                // Imprimir las categorías y sus frecuencias antes de ordenar
                imprimirCategoriasFrecuencia(categoriaFrecuencia);

                // Ordenar las categorías por frecuencia (de mayor a menor)
                quickSortCategorias(categoriaFrecuencia);

                // Imprimir las categorías y sus frecuencias después de ordenar
                std::cout << "\nCategorías ordenadas por frecuencia:\n";
                imprimirCategoriasFrecuencia(categoriaFrecuencia);

                // Generar las recomendaciones
                DynamicArray<Anime> mejoresRecomendaciones = generarRecomendaciones(categoriaFrecuencia, genreQueues, uniqueGenres, animesFavoritos);
                DynamicArray<Anime> peoresRecomendaciones = generarPeoresRecomendaciones(categoriaFrecuencia, genreQueues, uniqueGenres, animesFavoritos);



                // Mostrar los mejores 5 animes recomendados
                std::cout << "\n--- Mejores recomendaciones ---\n";
                for (int i = 0; i < mejoresRecomendaciones.size() && i < 5; ++i) {
                    mejoresRecomendaciones[i].display();
                    std::cout << "------------------------------------\n";
                }

                // Mostrar los mejores 5 animes recomendados
                std::cout << "\n--- Peores recomendaciones ---\n";
                for (int i = 0; i < peoresRecomendaciones.size() && i < 5; ++i) {
                    peoresRecomendaciones[i].display();
                    std::cout << "------------------------------------\n";
                }


                break;
            }



            case 6:
                std::cout << "Saliendo...\n";
                break;

            default:
                std::cout << "Opción inválida. Por favor, intente nuevamente.\n";
        }
    } while (opcionPrincipal != 6);

    return 0;
}
