#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "anime.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/queue.hpp"
#include "dataStructure/stack.hpp"

using namespace std;

// Función para eliminar espacios en blanco iniciales y finales
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";  // Si no hay caracteres no vacíos
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Función para verificar si una cadena es numérica
bool isNumeric(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), [](char c){ return isdigit(c) || c == '.'; });
}

// Función para leer el archivo CSV y crear objetos Anime
void readCSV(const string& filename, LinkedList<Anime>& ll, DoublyLinkedList<Anime>& dll, Queue<Anime>& q, Stack<Anime>& s) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return;
    }

    string line;
    int lineNumber = 0;  // Para llevar la cuenta de la línea actual
    getline(file, line); // Ignorar la primera línea (cabecera)
    
    while (getline(file, line)) {
        lineNumber++;  // Contar las líneas a partir de la segunda (datos)

        stringstream ss(line);
        string anime_id_str, episodes_str, rating_str, members_str;
        int anime_id = 0, episodes = -1, members = -1;  // Inicializamos con valores por defecto
        float rating = -1.0f;  // Valor especial para rating si está vacío
        string name, genre, type;

        try {
            // Leer y convertir el anime_id
            getline(ss, anime_id_str, ',');
            anime_id_str = trim(anime_id_str);  // Eliminar espacios en blanco
            if (isNumeric(anime_id_str)) anime_id = stoi(anime_id_str);  // Convertir solo si es numérico

            // Leer nombre
            getline(ss, name, ',');

            // Leer el género (dentro de comillas dobles)
            getline(ss, genre, '"'); // Saltar comilla inicial
            getline(ss, genre, '"'); // Leer dentro de las comillas
            genre = trim(genre);  // Eliminar espacios en blanco
            ss.ignore();  // Ignorar la coma después de las comillas

            // Leer tipo (TV, Movie, etc.)
            getline(ss, type, ',');
            type = trim(type);  // Eliminar espacios en blanco

            // Leer y convertir episodes
            getline(ss, episodes_str, ',');
            episodes_str = trim(episodes_str);  // Eliminar espacios en blanco
            if (isNumeric(episodes_str) && episodes_str != "Unknown") {
                episodes = stoi(episodes_str);  // Convertir solo si es numérico y no es "Unknown"
            }

            // Leer y convertir rating
            getline(ss, rating_str, ',');
            rating_str = trim(rating_str);  // Eliminar espacios en blanco
            if (isNumeric(rating_str)) {
                rating = stof(rating_str);  // Convertir solo si es numérico
            }

            // Leer y convertir members
            getline(ss, members_str, ',');
            members_str = trim(members_str);  // Eliminar espacios en blanco
            if (isNumeric(members_str)) {
                members = stoi(members_str);  // Convertir solo si es numérico
            }

        } catch (const invalid_argument& e) {
            cerr << "Error al convertir un valor en la línea " << lineNumber << ": " << e.what() << endl;
            cerr << "Línea completa: " << line << endl;
            continue;  // Saltar esta línea y continuar con la siguiente
        }

        // Crear objeto Anime
        Anime anime(anime_id, name, genre, type, episodes, rating, members);

        // Insertar el objeto en las diferentes estructuras
        ll.push_back(anime);  // Lista enlazada simple
        dll.push_back(anime); // Lista doblemente enlazada
        q.push(anime);        // Cola
        s.push(anime);        // Pila
    }

    file.close();
}

#endif // UTILS_HPP
