#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "anime.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/queue.hpp"
#include "dataStructure/stack.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// Storage for Linked list
void readCSV(const std::string& filename, LinkedList<Anime>& ll)
{
    std::ifstream file(filename); // File to read from with varaible name file
    std::string line; // Variable to store the line read from the file

    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << "anime.csv" << std::endl;
        return;
    }
    
    string name, genre, type;
    int id = 0, episodes = -1, members = -1;
    float rating = -1.0f;
    unsigned long long int lineNumber = 0;
    getline(file, line); // Ignore the first line

    while(getline(file, line))
    {
        ++lineNumber;
        //std::cout << "Reading line " << lineNumber << std::endl; for debugging purposes

        std::stringstream ss(line); // Use stringstream to read the line
        std::string data; // Variable to store the data read from the line

        // Read ID
        getline(ss, data, ','); // Read the first line and save it in data
        id = stoi(data); // Convert string to integer

        // Read name
        getline(ss, data, ',');
        if(data[0] == '"')
        {
            name = data.substr(1);
            while(getline(ss, data, ','))
            {
                name += "," + data;
                if(data.back() == '"')
                {
                    name.pop_back();
                    break;
                }
            }
        }
        else
        {
            name = data;
        }

        // Read genre
        getline(ss, data, ',');
        if (data[0] == '"')
        {
            genre = data.substr(1);
            while (getline(ss, data, ','))
            {
                genre += "," + data;
                if (data.back() == '"')
                {
                    genre.pop_back();
                    break;
                }
            }
        }
        else
        {
            genre = data;
        }

        // Read type
        getline(ss, data, ',');
        type = data;

        // Read episodes
        getline(ss, data, ',');
        episodes = data != "Unknown" ? stoi(data) : -1;

        // Read rating
        getline(ss, data, ',');
        rating = data != "" ? stof(data) : -1.0f;

        // Read members
        getline(ss, data, ',');
        members = stoi(data);
        
        // Create anime object
        Anime anime(id, name, genre, type, episodes, rating, members);

        ll.push_front(anime);
    }

    file.close();
}


// Storage for Doubly linked list
void readCSV(const std::string& filename, DoublyLinkedList<Anime>& dll)
{
    std::ifstream file(filename); // File to read from with varaible name file
    std::string line; // Variable to store the line read from the file

    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << "anime.csv" << std::endl;
        return;
    }
    
    string name, genre, type;
    int id = 0, episodes = -1, members = -1;
    float rating = -1.0f;
    unsigned long long int lineNumber = 0;
    getline(file, line); // Ignore the first line

    while(getline(file, line))
    {
        ++lineNumber;
        //std::cout << "Reading line " << lineNumber << std::endl; for debugging purposes

        std::stringstream ss(line); // Use stringstream to read the line
        std::string data; // Variable to store the data read from the line

        // Read ID
        getline(ss, data, ','); // Read the first line and save it in data
        id = stoi(data); // Convert string to integer

        // Read name
        getline(ss, data, ',');
        if(data[0] == '"')
        {
            name = data.substr(1);
            while(getline(ss, data, ','))
            {
                name += "," + data;
                if(data.back() == '"')
                {
                    name.pop_back();
                    break;
                }
            }
        }
        else
        {
            name = data;
        }

        // Read genre
        getline(ss, data, ',');
        if (data[0] == '"')
        {
            genre = data.substr(1);
            while (getline(ss, data, ','))
            {
                genre += "," + data;
                if (data.back() == '"')
                {
                    genre.pop_back();
                    break;
                }
            }
        }
        else
        {
            genre = data;
        }

        // Read type
        getline(ss, data, ',');
        type = data;

        // Read episodes
        getline(ss, data, ',');
        episodes = data != "Unknown" ? stoi(data) : -1;

        // Read rating
        getline(ss, data, ',');
        rating = data != "" ? stof(data) : -1.0f;

        // Read members
        getline(ss, data, ',');
        members = stoi(data);
        
        // Create anime object
        Anime anime(id, name, genre, type, episodes, rating, members);

        dll.push_front(anime);
    }

    file.close();
}

// Storage for Stack
void readCSV(const std::string& filename, Stack<Anime>& s)
{
    std::ifstream file(filename); // File to read from with varaible name file
    std::string line; // Variable to store the line read from the file

    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << "anime.csv" << std::endl;
        return;
    }
    
    string name, genre, type;
    int id = 0, episodes = -1, members = -1;
    float rating = -1.0f;
    unsigned long long int lineNumber = 0;
    getline(file, line); // Ignore the first line

    while(getline(file, line))
    {
        ++lineNumber;
        //std::cout << "Reading line " << lineNumber << std::endl; for debugging purposes

        std::stringstream ss(line); // Use stringstream to read the line
        std::string data; // Variable to store the data read from the line

        // Read ID
        getline(ss, data, ','); // Read the first line and save it in data
        id = stoi(data); // Convert string to integer

        // Read name
        getline(ss, data, ',');
        if(data[0] == '"')
        {
            name = data.substr(1);
            while(getline(ss, data, ','))
            {
                name += "," + data;
                if(data.back() == '"')
                {
                    name.pop_back();
                    break;
                }
            }
        }
        else
        {
            name = data;
        }

        // Read genre
        getline(ss, data, ',');
        if (data[0] == '"')
        {
            genre = data.substr(1);
            while (getline(ss, data, ','))
            {
                genre += "," + data;
                if (data.back() == '"')
                {
                    genre.pop_back();
                    break;
                }
            }
        }
        else
        {
            genre = data;
        }

        // Read type
        getline(ss, data, ',');
        type = data;

        // Read episodes
        getline(ss, data, ',');
        episodes = data != "Unknown" ? stoi(data) : -1;

        // Read rating
        getline(ss, data, ',');
        rating = data != "" ? stof(data) : -1.0f;

        // Read members
        getline(ss, data, ',');
        members = stoi(data);
        
        // Create anime object
        Anime anime(id, name, genre, type, episodes, rating, members);

        s.push(anime);
    }

    file.close();
}

// Storage for Queue
void readCSV(const std::string& filename, Queue<Anime>& q)
{
    std::ifstream file(filename); // File to read from with varaible name file
    std::string line; // Variable to store the line read from the file

    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << "anime.csv" << std::endl;
        return;
    }
    
    string name, genre, type;
    int id = 0, episodes = -1, members = -1;
    float rating = -1.0f;
    unsigned long long int lineNumber = 0;
    getline(file, line); // Ignore the first line

    while(getline(file, line))
    {
        ++lineNumber;
        //std::cout << "Reading line " << lineNumber << std::endl; for debugging purposes

        std::stringstream ss(line); // Use stringstream to read the line
        std::string data; // Variable to store the data read from the line

        // Read ID
        getline(ss, data, ','); // Read the first line and save it in data
        id = stoi(data); // Convert string to integer

        // Read name
        getline(ss, data, ',');
        if(data[0] == '"')
        {
            name = data.substr(1);
            while(getline(ss, data, ','))
            {
                name += "," + data;
                if(data.back() == '"')
                {
                    name.pop_back();
                    break;
                }
            }
        }
        else
        {
            name = data;
        }

        // Read genre
        getline(ss, data, ',');
        if (data[0] == '"')
        {
            genre = data.substr(1);
            while (getline(ss, data, ','))
            {
                genre += "," + data;
                if (data.back() == '"')
                {
                    genre.pop_back();
                    break;
                }
            }
        }
        else
        {
            genre = data;
        }

        // Read type
        getline(ss, data, ',');
        type = data;

        // Read episodes
        getline(ss, data, ',');
        episodes = data != "Unknown" ? stoi(data) : -1;

        // Read rating
        getline(ss, data, ',');
        rating = data != "" ? stof(data) : -1.0f;

        // Read members
        getline(ss, data, ',');
        members = stoi(data);
        
        // Create anime object
        Anime anime(id, name, genre, type, episodes, rating, members);

        q.push(anime);
    }

    file.close();
}

// Storage for Dynamic array
void readCSV(const std::string& filename, DynamicArray<Anime>& a)
{
    std::ifstream file(filename); // File to read from with varaible name file
    std::string line; // Variable to store the line read from the file

    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << "anime.csv" << std::endl;
        return;
    }
    
    string name, genre, type;
    int id = 0, episodes = -1, members = -1;
    float rating = -1.0f;
    unsigned long long int lineNumber = 0;
    getline(file, line); // Ignore the first line

    while(getline(file, line))
    {
        ++lineNumber;
        //std::cout << "Reading line " << lineNumber << std::endl; for debugging purposes

        std::stringstream ss(line); // Use stringstream to read the line
        std::string data; // Variable to store the data read from the line

        // Read ID
        getline(ss, data, ','); // Read the first line and save it in data
        id = stoi(data); // Convert string to integer

        // Read name
        getline(ss, data, ',');
        if(data[0] == '"')
        {
            name = data.substr(1);
            while(getline(ss, data, ','))
            {
                name += "," + data;
                if(data.back() == '"')
                {
                    name.pop_back();
                    break;
                }
            }
        }
        else
        {
            name = data;
        }

        // Read genre
        getline(ss, data, ',');
        if (data[0] == '"')
        {
            genre = data.substr(1);
            while (getline(ss, data, ','))
            {
                genre += "," + data;
                if (data.back() == '"')
                {
                    genre.pop_back();
                    break;
                }
            }
        }
        else
        {
            genre = data;
        }

        // Read type
        getline(ss, data, ',');
        type = data;

        // Read episodes
        getline(ss, data, ',');
        episodes = data != "Unknown" ? stoi(data) : -1;

        // Read rating
        getline(ss, data, ',');
        rating = data != "" ? stof(data) : -1.0f;

        // Read members
        getline(ss, data, ',');
        members = stoi(data);
        
        // Create anime object
        Anime anime(id, name, genre, type, episodes, rating, members);

        a.push_front(anime);
    }

    file.close();
}

/*
void readCSV(const std::string& filename, LinkedList<Anime>& ll, DoublyLinkedList<Anime>& dll, Queue<Anime>& q, Stack<Anime>& s, DynamicArray<Anime>& da)
{
    std::ifstream file(filename); // File to read from with varaible name file
    std::string line; // Variable to store the line read from the file

    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << "anime.csv" << std::endl;
        return;
    }
    
    string name, genre, type;
    int id = 0, episodes = -1, members = -1;
    float rating = -1.0f;
    unsigned long long int lineNumber = 0;
    getline(file, line); // Ignore the first line

    while(getline(file, line))
    {
        ++lineNumber;
        //std::cout << "Reading line " << lineNumber << std::endl; for debugging purposes

        std::stringstream ss(line); // Use stringstream to read the line
        std::string data; // Variable to store the data read from the line

        // Read ID
        getline(ss, data, ','); // Read the first line and save it in data
        id = stoi(data); // Convert string to integer

        // Read name
        getline(ss, data, ',');
        if(data[0] == '"')
        {
            name = data.substr(1);
            while(getline(ss, data, ','))
            {
                name += "," + data;
                if(data.back() == '"')
                {
                    name.pop_back();
                    break;
                }
            }
        }
        else
        {
            name = data;
        }

        // Read genre
        getline(ss, data, ',');
        if (data[0] == '"')
        {
            genre = data.substr(1);
            while (getline(ss, data, ','))
            {
                genre += "," + data;
                if (data.back() == '"')
                {
                    genre.pop_back();
                    break;
                }
            }
        }
        else
        {
            genre = data;
        }

        // Read type
        getline(ss, data, ',');
        type = data;

        // Read episodes
        getline(ss, data, ',');
        episodes = data != "Unknown" ? stoi(data) : -1;

        // Read rating
        getline(ss, data, ',');
        rating = data != "" ? stof(data) : -1.0f;

        // Read members
        getline(ss, data, ',');
        members = stoi(data);
        
        // Create anime object
        Anime anime(id, name, genre, type, episodes, rating, members);

        ll.push_front(anime);
        dll.push_back(anime);
        q.push(anime);
        s.push(anime);
        da.push_back(anime);
        
    }

    file.close();
}
*/

#endif