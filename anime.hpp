#ifndef ANIME_HPP
#define ANIME_HPP

#include <string>
#include <iostream>

using namespace std;

class Anime {
public:
    int anime_id;
    string name;
    string genre;
    string type;
    int episodes;
    float rating;
    int members;

    // Constructor por defecto
    Anime() : anime_id(0), name(""), genre(""), type(""), episodes(0), rating(0.0), members(0) {}

    // Constructor con parámetros
    Anime(int id, const string& n, const string& g, const string& t, int ep, float r, int m)
        : anime_id(id), name(n), genre(g), type(t), episodes(ep), rating(r), members(m) {}

    // Métodos que podrías agregar para manipular o mostrar información
    void display() const {
        cout << "ID: " << anime_id
             << ", Name: " << name
             << ", Genre: " << genre
             << ", Type: " << type
             << ", Episodes: " << episodes
             << ", Rating: " << rating
             << ", Members: " << members << endl;
    }
};


#endif // ANIME_HPP
