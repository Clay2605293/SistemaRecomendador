#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "anime.hpp"
#include "dataStructure/dynamicArray.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/OrderedList.hpp"
#include "dataStructure/PriorityQueue.hpp"
#include "searchAlgorithm/binarySearchTitle.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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
            else if constexpr (std::is_same<T, OrderedList<Anime>>::value)
            {
                dataStructure.insert(anime);
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
                            OrderedList<Anime> &orderedList,
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

  // Ordered List
  std::cout << "Ordered List" << std::endl;
  start = high_resolution_clock::now();
  readCSV(filename, orderedList);
  stop = high_resolution_clock::now();
  std::cout << "Milliseconds: "
            << duration_cast<milliseconds>(stop - start).count() << std::endl;
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

void extractUniqueGenres(const std::string& filename, DynamicArray<std::string>&
genresArray)
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

void buscarAnimePorTitulo(const OrderedList<Anime> &orderedList,
                          const std::string &titulo) {
  int index = binarySearchTitle(orderedList, titulo);

  if (index != -1) {
    // Usando `get` para obtener el anime en el índice encontrado
    Anime foundAnime = orderedList.get(index);
    std::cout << "\n";
    std::cout << "Anime encontrado:\n";
    std::cout << "ID: " << foundAnime.anime_id << "\n";
    std::cout << "Título: " << foundAnime.name << "\n";
    std::cout << "Género: " << foundAnime.genre << "\n";
    std::cout << "Tipo: " << foundAnime.type << "\n";
    std::cout << "Episodios: " << foundAnime.episodes << "\n";
    std::cout << "Calificación: " << foundAnime.rating << "\n";
    std::cout << "Miembros: " << foundAnime.members << "\n";
  } else {
    std::cout << "\n";
    std::cout << "Anime no encontrado.\n";
  }
}

#endif
