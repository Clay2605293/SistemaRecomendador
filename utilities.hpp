#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "anime.hpp"
#include "dataStructure/stack.hpp"
#include "dataStructure/stack.hpp"
#include "dataStructure/dynamicArray.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/PriorityQueue.hpp"
#include "searchAlgorithm/binarySearchTitle.hpp"
#include "searchAlgorithm/ternarySearchTitle.hpp"
#include "searchAlgorithm/sequentialSearchTitle.hpp"
#include "searchAlgorithm/toLower.hpp"
#include "sortAlgorithm/quickSort.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <type_traits>

using namespace std::chrono;

template <typename T>
void readCSV(const std::string filename, T &dataStructure) 
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) 
    {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }
    
    unsigned lineNumber = 1; // Just for debuging
    std::getline(file, line);

    while (std::getline(file, line)) 
    {
        // Atributes variables
        std::string name, genre, type;
        int id = 0, episodes = -1, members = -1;
        float rating = -1.0f;
       
        // Control variables
        std::stringstream ss(line); // Use to read line
        std::string data; // Variable to store the information of CSV

        ++lineNumber; // Counts line in case of especial error in CSV
        //std::cout << "Line: " << lineNumber << std::endl;
       
        // Save ID
        std::getline(ss, data, ','); // Read the first line and saves it in data
        id = stoi(data);

        // Leer el campo "name" (manejar nombres con y sin comillas)
        std::getline(ss, name, ',');
        if (name[0] == '"') 
        {
            while (name.back() != '"') 
            {
                std::string temp;
                std::getline(ss, temp, ',');
                name += "," + temp;
            }
            name = name.substr(1, name.size() - 2); // Quitar comillas
        }

        // Leer el campo "genre" (manejar géneros con y sin comillas)
        std::getline(ss, genre, ',');
        if (genre[0] == '"') 
        {
            while (genre.back() != '"') 
            {
                std::string temp;
                std::getline(ss, temp, ',');
                genre += "," + temp;
            }
            genre = genre.substr(1, genre.size() - 2); // Quitar comillas
        }
        
        if (genre == "")
            continue;

        // Save type
        getline(ss, data, ',');
        type = data;
        if (type == "")
            continue;

        // Save episodes
        getline(ss, data, ',');
        episodes = data != "Unknown" ? stoi(data) : -1;
        if (episodes < 0) {
            continue;
        
        }
        // Save rating
        getline(ss, data, ',');
        rating = data != "" ? stof(data) : -1.0f;
        if (rating < 0)
            continue;

        // Save members
        getline(ss, data, ',');
        members = stoi(data);
        
        // Create anime object
        Anime anime(id, name, genre, type, episodes, rating, members);

        while (true) 
        {
            if constexpr (std::is_same<T, DynamicArray<Anime>>::value) 
            {
                dataStructure.push_back(anime); // Is dynamic array
                break;
            } 
            else if constexpr (std::is_same<T, LinkedList<Anime>>::value) 
            {
                dataStructure.push_front(anime);
                break;
            }
            else if constexpr (std::is_same<T, DoublyLinkedList<Anime>>::value)
            {
                dataStructure.push_front(anime);
                break;
            }
            else if constexpr (std::is_same<T, PriorityQueue<Anime>>::value) 
            {
                dataStructure.push(anime, rating);
                break;
            }
        }
    }
    file.close();
}


void testStoragePerformance(LinkedList<Anime> &linkedList,
                            DoublyLinkedList<Anime> &doublyLinkedList,
                            DynamicArray<Anime> &dynamicArray,
                            PriorityQueue<Anime> &priorityQueue) 
{
  std::string filename = "anime.csv";

  std::cout << "TESTING PERFORMANCE OF DATA STRUCTURES" << std::endl;
  std::cout << "############################################" << std::endl;

  // Linked List
  std::cout << "Linked List: " << std::endl;
  auto start = high_resolution_clock::now();
  readCSV(filename, linkedList);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  std::cout << "Milliseconds: " << duration.count() << std::endl;
  std::cout << "############################################" << std::endl;

  // Doubly Linked List
  std::cout << "Doubly Linked List" << std::endl;
  auto start1 = high_resolution_clock::now();
  readCSV(filename, doublyLinkedList);
  auto stop1 = high_resolution_clock::now();
  auto duration1 = duration_cast<milliseconds>(stop1 - start1);
  std::cout << "Milliseconds: " << duration1.count() << std::endl;
  std::cout << "############################################" << std::endl;

  // Dynamic Array
  std::cout << "Dynamic Array" << std::endl;
  auto start4 = high_resolution_clock::now();
  readCSV(filename, dynamicArray);
  auto stop4 = high_resolution_clock::now();
  auto duration4 = duration_cast<milliseconds>(stop4 - start4);
  std::cout << "Milliseconds: " << duration4.count() << std::endl;
  std::cout << "############################################" << std::endl;


  // Priority Queue
  std::cout << "Priority Queue" << std::endl;
  start = high_resolution_clock::now();
  readCSV(filename, priorityQueue);
  stop = high_resolution_clock::now();
  std::cout << "Milliseconds: "
            << duration_cast<milliseconds>(stop - start).count() << std::endl;
  std::cout << "############################################" << std::endl;
}

void extractUniqueTypes(const std::string& filename, DynamicArray<std::string>&
typesArray)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }


    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string data, name, genres, types;


        std::getline(ss, data, ',');
        // Leer el campo "name" (manejar nombres con y sin comillas)
        std::getline(ss, name, ',');
        if (name[0] == '"') {
            while (name.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                name += "," + temp;
            }
            name = name.substr(1, name.size() - 2);  // Quitar comillas
        }
        
        // Leer el campo "genre" (manejar géneros con y sin comillas)
        std::getline(ss, genres, ',');
        if (genres[0] == '"') {
            while (genres.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                genres += "," + temp;
            }
            genres = genres.substr(1, genres.size() - 2);  // Quitar comillas
        }

        // Leer el campo "type" (manejar tipos con y sin comillas)
        std::getline(ss, types, ',');
        if (types[0] == '"') {
            while (types.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                types += "," + temp;
            }
            types = types.substr(1, types.size() - 2);  // Quitar comillas
        }

        // Separar los géneros en subcategorías y limpiarlos
        std::stringstream typeStream(types);
        std::string type;
        while (std::getline(typeStream, type, ',')) {
            // Eliminar espacios al inicio y al final de cada género
            type.erase(0, type.find_first_not_of(" "));
            type.erase(type.find_last_not_of(" ") + 1);

            // Verificar si el género ya está en typesArray
            bool exists = false;
            for (int i = 0; i < typesArray.size(); ++i) {
                if (typesArray[i] == type) {
                    exists = true;
                    break;
                }
            }

            // Agregar género si no existe en typesArray
            if (!exists) {
                typesArray.push_back(type);
            }
        }
    }

    file.close();
}

void extractUniqueGenres(const std::string& filename, DynamicArray<std::string>& genresArray)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }


    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string data, name, genres;


        std::getline(ss, data, ',');

        // Leer el campo "name" (manejar nombres con y sin comillas)
        std::getline(ss, name, ',');
        if (name[0] == '"') {
            while (name.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                name += "," + temp;
            }
            name = name.substr(1, name.size() - 2);  // Quitar comillas
        }

        // Leer el campo "genre" (manejar géneros con y sin comillas)
        std::getline(ss, genres, ',');
        if (genres[0] == '"') {
            while (genres.back() != '"') {
                std::string temp;
                std::getline(ss, temp, ',');
                genres += "," + temp;
            }
            genres = genres.substr(1, genres.size() - 2);  // Quitar comillas
        }

        // Separar los géneros en subcategorías y limpiarlos
        std::stringstream genreStream(genres);
        std::string genre;
        while (std::getline(genreStream, genre, ',')) {
            // Eliminar espacios al inicio y al final de cada género
            genre.erase(0, genre.find_first_not_of(" "));
            genre.erase(genre.find_last_not_of(" ") + 1);

            // Verificar si el género ya está en genresArray
            bool exists = false;
            for (int i = 0; i < genresArray.size(); ++i) {
                if (genresArray[i] == genre) {
                    exists = true;
                    break;
                }
            }

            // Agregar género si no existe en genresArray
            if (!exists) {
                genresArray.push_back(genre);
            }
        }
    }

    file.close();
}


void buscarAnimePorTitulo(const DynamicArray<Anime>& dynamicArray, const std::string& titulo, int searchType) {
    std::string lowerTitulo = toLower(titulo);
    int index = -1;
    
    std::cout << "\n############################################################################";
    switch (searchType) {
        case 1: {
            auto start = high_resolution_clock::now();
            index = sequentialSearchTitle(dynamicArray, lowerTitulo);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            std::cout << "\nTiempo de busqueda secuencial en microsegundo: " << duration.count() << std::endl;
            break;
            }
        case 2: {
            auto start2 = high_resolution_clock::now();
            index = binarySearchTitle(dynamicArray, lowerTitulo);
            auto stop2 = high_resolution_clock::now();
            auto duration2 = duration_cast<microseconds>(stop2 - start2);
            std::cout << "\nTiempo de busqueda binaria en microsegundo: " << duration2.count() << std::endl; 
            break;
            }
        case 3: {
            auto start3 = high_resolution_clock::now();  
            index = ternarySearchTitle(dynamicArray, lowerTitulo);
            auto stop3 = high_resolution_clock::now();
            auto duration3 = duration_cast<microseconds>(stop3 - start3);
            std::cout << "\nTiempo de busqueda ternaria en microsegundo: " << duration3.count() << std::endl;
            break;
            }
        default: {
            std::cout << "Tipo de búsqueda inválido. Seleccione 1, 2 o 3.\n";
            return;
            }
    }
    std::cout << "############################################################################" << std::endl;
    
    if (index != -1) {
        Anime foundAnime = dynamicArray[index];
        std::cout << "\nAnime encontrado:\n";
        std::cout << "ID: " << foundAnime.anime_id << "\n";
        std::cout << "Título: " << foundAnime.name << "\n";
        std::cout << "Género: " << foundAnime.genre << "\n";
        std::cout << "Tipo: " << foundAnime.type << "\n";
        std::cout << "Episodios: " << foundAnime.episodes << "\n";
        std::cout << "Calificación: " << foundAnime.rating << "\n";
        std::cout << "Miembros: " << foundAnime.members << "\n";
    } else {
        std::cout << "\nAnime no encontrado.\n";
    }
}

int regresarindexRecom(const DynamicArray<Anime>& dynamicArray, const std::string& titulo) {
    std::string lowerTitulo = toLower(titulo);
    int index = -1;

    index = binarySearchTitle(dynamicArray, lowerTitulo);


    if (index != -1) {
        Anime foundAnime = dynamicArray[index];
        std::cout << "\nAnime encontrado:\n";
        std::cout << "ID: " << foundAnime.anime_id << "\n";
        std::cout << "Título: " << foundAnime.name << "\n";
        std::cout << "Género: " << foundAnime.genre << "\n";
        std::cout << "Tipo: " << foundAnime.type << "\n";
        std::cout << "Episodios: " << foundAnime.episodes << "\n";
        std::cout << "Calificación: " << foundAnime.rating << "\n";
        std::cout << "Miembros: " << foundAnime.members << "\n";
        std::cout << "\n";
    } else {
        std::cout << "\nAnime no encontrado.\n";
    }

    return index;
}

DynamicArray<PriorityQueue<Anime>> initializeGenrePriorityQueues(const DynamicArray<std::string>& uniqueGenres) {
    DynamicArray<PriorityQueue<Anime>> genreQueues(uniqueGenres.size());
    return genreQueues;
}

LinkedList<PriorityQueue<Anime>> initializeGenrePriorityQueuesLinkedList(const DynamicArray<std::string>& uniqueGenres) {
    LinkedList<PriorityQueue<Anime>> genreQueue;
    for (int i = 0; i < uniqueGenres.size(); ++i) {
        PriorityQueue<Anime> newPriorityQueue;
        genreQueue.push_front(newPriorityQueue);
    }
    return genreQueue;
}

DoublyLinkedList<PriorityQueue<Anime>> initializeGenrePriorityQueuesDoblyList(const DynamicArray<std::string>& uniqueGenres) {
    DoublyLinkedList<PriorityQueue<Anime>> genreQueue;
    for (int i = 0; i < uniqueGenres.size(); ++i) {
        PriorityQueue<Anime> newPriorityQueue;
        genreQueue.push_front(newPriorityQueue);
    }
    return genreQueue;
}

Stack<PriorityQueue<Anime>> initializeGenrePriorityQueuesStack(const DynamicArray<std::string>& uniqueGenres) {
    Stack<PriorityQueue<Anime>> genreQueue;
    for (int i = 0; i < uniqueGenres.size(); ++i) {
        PriorityQueue<Anime> newPriorityQueue;
        genreQueue.push(newPriorityQueue);
    }
    return genreQueue;
}

void assignAnimesToGenreQueues(const DynamicArray<Anime>& animes, const DynamicArray<std::string>& uniqueGenres, Stack<PriorityQueue<Anime>> genreQueues) {
    for (int i = 0; i < animes.size(); ++i) {
        const Anime& anime = animes[i];
        
        for (int j = 0; j < uniqueGenres.size(); ++j) {
            const std::string& genre = uniqueGenres[j];
            
            if (anime.genre.find(genre) != std::string::npos) {
                genreQueues.at(j).push(anime, anime.rating);

            }
        }
    }
}

void assignAnimesToGenreQueues(const DynamicArray<Anime>& animes, const DynamicArray<std::string>& uniqueGenres, DoublyLinkedList<PriorityQueue<Anime>>& genreQueues) {
    for (int i = 0; i < animes.size(); ++i) {
        const Anime& anime = animes[i];
        
        for (int j = 0; j < uniqueGenres.size(); ++j) {
            const std::string& genre = uniqueGenres[j];
            
            
            if (anime.genre.find(genre) != std::string::npos) {
                genreQueues.at(j).push(anime, anime.rating);
            }
        }
    }
}

void assignAnimesToGenreQueues(const DynamicArray<Anime>& animes, const DynamicArray<std::string>& uniqueGenres, LinkedList<PriorityQueue<Anime>>& genreQueues) {
    for (int i = 0; i < animes.size(); ++i) {
        const Anime& anime = animes[i];
        
        for (int j = 0; j < uniqueGenres.size(); ++j) {
            const std::string& genre = uniqueGenres[j];
            
            
            if (anime.genre.find(genre) != std::string::npos) {
                genreQueues.at(j).push(anime, anime.rating);
            }
        }
    }
}

void assignAnimesToGenreQueues(const DynamicArray<Anime>& animes, const DynamicArray<std::string>& uniqueGenres, DynamicArray<PriorityQueue<Anime>>& genreQueues) {
    for (int i = 0; i < animes.size(); ++i) {
        const Anime& anime = animes[i];
        
        for (int j = 0; j < uniqueGenres.size(); ++j) {
            const std::string& genre = uniqueGenres[j];
            
            
            if (anime.genre.find(genre) != std::string::npos) {
                genreQueues[j].push(anime, anime.rating);
            }
        }
    }
}


void assignAnimesToTypesQueue(const DynamicArray<Anime>& animes, const DynamicArray<std::string>& uniqueTypes, DynamicArray<PriorityQueue<Anime>>& typeQueues) {
    for (int i = 0; i < animes.size(); ++i) {
        const Anime& anime = animes[i];
        
        for (int j = 0; j < uniqueTypes.size(); ++j) {
            const std::string& genre = uniqueTypes[j];
            
            
            if (anime.type.find(genre) != std::string::npos) {
                typeQueues[j].push(anime, anime.rating);
            }
        }
    }
}

// Función para eliminar espacios al inicio y al final de una cadena
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return ""; // La cadena está vacía o solo tiene espacios

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}


// Estructura para almacenar una categoría y su frecuencia
struct CategoriaFrecuencia {
    std::string categoria;
    int frecuencia;

    CategoriaFrecuencia() : categoria(""), frecuencia(0) {} // Constructor predeterminado
    CategoriaFrecuencia(const std::string& cat, int freq) : categoria(cat), frecuencia(freq) {}
};


// Función para recolectar la frecuencia de las categorías de los animes favoritos
DynamicArray<CategoriaFrecuencia> recolectarCategorias(const DynamicArray<Anime>& animesFavoritos) {
    DynamicArray<CategoriaFrecuencia> categoriaFrecuencia;

    for (int i = 0; i < animesFavoritos.size(); ++i) {
        const Anime& anime = animesFavoritos[i];
        std::istringstream ss(anime.genre);
        std::string categoria;

        // Procesar cada categoría en la cadena de géneros
        while (std::getline(ss, categoria, ',')) {
            categoria = trim(categoria); // Eliminar espacios al inicio y al final
            bool encontrado = false;

            // Verificar si la categoría ya está en `categoriaFrecuencia`
            for (int j = 0; j < categoriaFrecuencia.size(); ++j) {
                if (categoriaFrecuencia[j].categoria == categoria) {
                    categoriaFrecuencia[j].frecuencia++;
                    encontrado = true;
                    break;
                }
            }

            // Si no se encuentra, agregar la categoría con frecuencia 1
            if (!encontrado) {
                categoriaFrecuencia.push_back(CategoriaFrecuencia(categoria, 1));
            }
        }
    }
    
    return categoriaFrecuencia;
}


template <typename T, typename Compare>
int partition(DynamicArray<T>& array, int low, int high, Compare comp) {
    T pivot = array[high]; // Elegir el último elemento como pivote
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (comp(array[j], pivot)) { // Usar la función de comparación para ordenar
            i++;
            swap(array, i, j);
        }
    }
    swap(array, i + 1, high);
    return i + 1;
}


// Implementación de quickSort para ordenar por frecuencia
void quickSortCategorias(DynamicArray<CategoriaFrecuencia>& array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high, [](const CategoriaFrecuencia& a, const CategoriaFrecuencia& b) {
            return a.frecuencia > b.frecuencia; // Ordenar de mayor a menor frecuencia
        });
        quickSortCategorias(array, low, pi - 1);
        quickSortCategorias(array, pi + 1, high);
    }
}


void quickSortCategorias(DynamicArray<CategoriaFrecuencia>& array) {
    quickSortCategorias(array, 0, array.size() - 1);
}


// Función para encontrar el índice de una categoría en un DynamicArray de cadenas
int encontrarIndiceCategoria(const std::string& categoria, const DynamicArray<std::string>& categories) {
    for (int i = 0; i < categories.size(); ++i) {
        if (categories[i] == categoria) {
            return i;
        }
    }
    return -1;
}


// Implementación de `generarRecomendaciones`
DynamicArray<Anime> generarRecomendaciones(const DynamicArray<CategoriaFrecuencia>& categoriaFrecuencia, 
                                           const DynamicArray<PriorityQueue<Anime>>& genreQueues, 
                                           const DynamicArray<std::string>& uniqueGenres,
                                           const DynamicArray<Anime>& animesUsuario) {
    DynamicArray<Anime> recomendaciones;
    DynamicArray<std::string> titulosUsuario;

    // Almacenar nombres de animes dados por el usuario en `titulosUsuario`
    for (int i = 0; i < animesUsuario.size(); ++i) {
        titulosUsuario.push_back(animesUsuario[i].name);
    }

    // Debug: Mostrar los títulos que el usuario ya ha visto
    std::cout << "Animes vistos por el usuario:\n";
    for (int i = 0; i < titulosUsuario.size(); ++i) {
        std::cout << "- " << titulosUsuario[i] << "\n";
    }

    // Definir las cantidades de recomendaciones por categoría
    int totalRecomendaciones = 5;
    int maxPorCategoria[] = {3, 2}; // Hasta 3 de la primera categoría, 2 de la segunda
    int categoriasConsideradas = sizeof(maxPorCategoria) / sizeof(maxPorCategoria[0]);

    int recomendacionesActuales = 0;

    // Procesar categorías por orden de frecuencia (de mayor a menor)
    for (int i = 0; i < categoriaFrecuencia.size() && recomendacionesActuales < totalRecomendaciones; ++i) {
        const auto& categoria = categoriaFrecuencia[i].categoria;
        int maxRecomendacionesEnCategoria = 1; // Valor por defecto si no está en el arreglo

        // Determinar el número máximo de recomendaciones para esta categoría
        if (i < categoriasConsideradas) {
            maxRecomendacionesEnCategoria = maxPorCategoria[i];
        }

        std::cout << "\nProcesando categoría: " << categoria << " (frecuencia: " << categoriaFrecuencia[i].frecuencia << ")\n";

        // Busca el índice de la categoría en `genreQueues`
        int indiceCategoria = encontrarIndiceCategoria(categoria, uniqueGenres);
        if (indiceCategoria == -1) {
            std::cout << "Categoría no encontrada en uniqueGenres.\n";
            continue;
        }

        // Copiar la `PriorityQueue` para no modificar la original
        PriorityQueue<Anime> queue = genreQueues[indiceCategoria];
        int count = 0;

        // Recorre la cola y evita los títulos que ya están en `titulosUsuario`
        while (!queue.empty() && count < maxRecomendacionesEnCategoria && recomendacionesActuales < totalRecomendaciones) {
            Anime topAnime = queue.top();
            queue.pop();

            // Mostrar información del anime actual
            std::cout << "Considerando anime: " << topAnime.name << " (rating: " << topAnime.rating << ")\n";

            // Verificar si el anime ya está en la lista del usuario
            bool encontrado = false;
            for (int j = 0; j < titulosUsuario.size(); ++j) {
                if (titulosUsuario[j] == topAnime.name) {
                    encontrado = true;
                    std::cout << "-> Ya visto por el usuario. Se omite.\n";
                    break;
                }
            }

            // Solo agrega el anime si no está en la lista del usuario
            if (!encontrado) {
                recomendaciones.push_back(topAnime);
                ++count;
                ++recomendacionesActuales;
                std::cout << "-> Agregado a las recomendaciones.\n";
            }
        }

        // Verificar si ya alcanzamos el total de recomendaciones
        if (recomendacionesActuales >= totalRecomendaciones) {
            std::cout << "Se han alcanzado las recomendaciones necesarias.\n";
            break;
        }
    }

    // Mostrar las recomendaciones finales
    std::cout << "\nRecomendaciones generadas:\n";
    for (int i = 0; i < recomendaciones.size(); ++i) {
        std::cout << "- " << recomendaciones[i].name << " (rating: " << recomendaciones[i].rating << ")\n";
    }

    return recomendaciones;
}


// Implementación de `generarPeoresRecomendaciones`
DynamicArray<Anime> generarPeoresRecomendaciones(const DynamicArray<CategoriaFrecuencia>& categoriaFrecuencia, 
                                                 const DynamicArray<PriorityQueue<Anime>>& genreQueues, 
                                                 const DynamicArray<std::string>& uniqueGenres,
                                                 const DynamicArray<Anime>& animesUsuario) {
    DynamicArray<Anime> peoresRecomendaciones;
    DynamicArray<std::string> titulosUsuario;

    // Almacenar nombres de animes dados por el usuario en `titulosUsuario`
    for (int i = 0; i < animesUsuario.size(); ++i) {
        titulosUsuario.push_back(animesUsuario[i].name);
    }

    // Identificar las categorías seleccionadas en `categoriaFrecuencia`
    DynamicArray<std::string> categoriasSeleccionadas;
    for (int i = 0; i < categoriaFrecuencia.size(); ++i) {
        categoriasSeleccionadas.push_back(categoriaFrecuencia[i].categoria);
    }

    // Encontrar las categorías no seleccionadas
    DynamicArray<std::string> categoriasNoSeleccionadas;
    for (int i = 0; i < uniqueGenres.size(); ++i) {
        if (encontrarIndiceCategoria(uniqueGenres[i], categoriasSeleccionadas) == -1) {
            categoriasNoSeleccionadas.push_back(uniqueGenres[i]);
        }
    }

    int totalPeoresRecomendaciones = 5;
    int peoresRecomendacionesActuales = 0;

    // Extraer animes con menor rating de las categorías no seleccionadas
    for (int i = 0; i < categoriasNoSeleccionadas.size() && peoresRecomendacionesActuales < totalPeoresRecomendaciones; ++i) {
        const auto& categoria = categoriasNoSeleccionadas[i];
        std::cout << "\nProcesando categoría no seleccionada: " << categoria << "\n";

        int indiceCategoria = encontrarIndiceCategoria(categoria, uniqueGenres);
        if (indiceCategoria == -1) {
            std::cout << "Categoría no encontrada en uniqueGenres.\n";
            continue;
        }

        // Crear una cola temporal para almacenar los animes y obtener los de menor rating
        PriorityQueue<Anime> tempQueue = genreQueues[indiceCategoria];
        DynamicArray<Anime> animesConMenorRating;

        // Extraer todos los animes de la cola y almacenarlos temporalmente
        while (!tempQueue.empty()) {
            animesConMenorRating.push_back(tempQueue.top());
            tempQueue.pop();
        }

        // Ordenar los animes temporalmente por rating ascendente
        quickSort(animesConMenorRating, std::function<bool(const Anime&, const Anime&)>([](const Anime& a, const Anime& b) {
            return a.rating < b.rating;
        }));


        int count = 0;

        // Tomar los animes con menor rating y que el usuario no haya visto
        for (int j = 0; j < animesConMenorRating.size() && count < 2 && peoresRecomendacionesActuales < totalPeoresRecomendaciones; ++j) {
            const Anime& bottomAnime = animesConMenorRating[j];

            bool encontrado = false;
            for (int k = 0; k < titulosUsuario.size(); ++k) {
                if (titulosUsuario[k] == bottomAnime.name) {
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado) {
                peoresRecomendaciones.push_back(bottomAnime);
                ++count;
                ++peoresRecomendacionesActuales;
            }
        }

        if (peoresRecomendacionesActuales >= totalPeoresRecomendaciones) {
            break;
        }
    }

    std::cout << "\nPeores recomendaciones generadas:\n";
    for (int i = 0; i < peoresRecomendaciones.size(); ++i) {
        std::cout << "- " << peoresRecomendaciones[i].name << " (rating: " << peoresRecomendaciones[i].rating << ")\n";
    }

    return peoresRecomendaciones;
}




void imprimirCategoriasFrecuencia(const DynamicArray<CategoriaFrecuencia>& categoriaFrecuencia) {
    std::cout << "Categorías y sus frecuencias:\n";
    for (int i = 0; i < categoriaFrecuencia.size(); ++i) {
        std::cout << "- " << categoriaFrecuencia[i].categoria
                  << ": " << categoriaFrecuencia[i].frecuencia << "\n";
    }
}



#endif
