#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "anime.hpp"
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

        // Save type
        getline(ss, data, ',');
        type = data;

        // Save episodes
        getline(ss, data, ',');
        episodes = data != "Unknown" ? stoi(data) : -1;

        // Save rating
        getline(ss, data, ',');
        rating = data != "" ? stof(data) : -1.0f;

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

    switch (searchType) {
        case 1:
            index = sequentialSearchTitle(dynamicArray, lowerTitulo);
            break;
        case 2:
            index = binarySearchTitle(dynamicArray, lowerTitulo);
            break;
        case 3:
            index = ternarySearchTitle(dynamicArray, lowerTitulo);
            break;
        default:
            std::cout << "Tipo de búsqueda inválido. Seleccione 1, 2 o 3.\n";
            return;
    }

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

DynamicArray<PriorityQueue<Anime>> initializeGenrePriorityQueues(const DynamicArray<std::string>& uniqueGenres) {
    DynamicArray<PriorityQueue<Anime>> genreQueues(uniqueGenres.size());
    return genreQueues;
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

#endif
