#ifndef PRIORITY_QUEUE_TYPE_HPP
#define PRIORITY_QUEUE_TYPE_HPP

#include "../utilities.hpp"
#include "PriorityQueue.hpp"
#include "../anime.hpp"
#include <iostream>
#include <string>

template <typename T>
class PriorityQueueType {
private:
    DynamicArray<std::string> typesArray;  // Almacena los tipos únicos de anime
    PriorityQueue<Anime> tvQueue;
    PriorityQueue<Anime> movieQueue;
    PriorityQueue<Anime> ovaQueue;
    PriorityQueue<Anime> onaQueue;
    PriorityQueue<Anime> specialQueue;
    PriorityQueue<Anime> musicQueue;

public:
    // Constructor que acepta el arreglo dinámico con los tipos únicos
    PriorityQueueType(const DynamicArray<std::string>& uniqueTypes)
        : typesArray(uniqueTypes) {
    }

    // Método para añadir un anime a su PriorityQueue correspondiente
    void addAnimeToQueue(const Anime &anime) {
        std::string type = anime.type;

        if (type == "TV") {
            tvQueue.push(anime, anime.rating);
        } else if (type == "Movie") {
            movieQueue.push(anime, anime.rating);
        } else if (type == "OVA") {
            ovaQueue.push(anime, anime.rating);
        } else if (type == "ONA") {
            onaQueue.push(anime, anime.rating);
        } else if (type == "Special") {
            specialQueue.push(anime, anime.rating);
        } else if (type == "Music") {
            musicQueue.push(anime, anime.rating);
        }
    }

    // Método para mostrar los animes mejor calificados de cada tipo
    void showBestRated() {
        if (!tvQueue.empty()) {
            std::cout << "TV: " << std::endl; 
            tvQueue.top().display();
        }
        if (!movieQueue.empty()) {
            std::cout << "Movie: " << std::endl; 
            movieQueue.top().display(); 
        }
        if (!ovaQueue.empty()) {
            std::cout << "OVA: " << std::endl;
            ovaQueue.top().display();
        }
        if (!onaQueue.empty()) {
            std::cout << "ONA: " << std::endl;
             onaQueue.top().display();
        }
        if (!specialQueue.empty()) {
            std::cout << "Special: " << std::endl;
            specialQueue.top().display();
        }
        if (!musicQueue.empty()) {
            std::cout << "Music: " << std::endl;
            musicQueue.top().display();
        }
    }
};

#endif // PRIORITY_QUEUE_TYPE_HPP
