#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "anime.hpp"
#include "dataStructure/doublyLinkedList.hpp"
#include "dataStructure/linkedList.hpp"
#include "dataStructure/queue.hpp"
#include "dataStructure/stack.hpp"
#include "dataStructure/OrderedList.hpp"
#include "dataStructure/PriorityQueue.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>

using namespace std::chrono;

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

        a.push_back(anime);
    }

    file.close();
}

// Storage for OrderedList
void readCSV(const std::string& filename, OrderedList<Anime>& orderedList)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    std::string name, genre, type;
    int id = 0, episodes = -1, members = -1;
    float rating = -1.0f;
    unsigned long long int lineNumber = 0;
    getline(file, line); // Ignore the first line

    while (getline(file, line))
    {
        ++lineNumber;
        std::stringstream ss(line);
        std::string data;

        // Read ID
        getline(ss, data, ',');
        id = stoi(data);

        // Read name
        getline(ss, data, ',');
        if (data[0] == '"')
        {
            name = data.substr(1);
            while (getline(ss, data, ','))
            {
                name += "," + data;
                if (data.back() == '"')
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

        // Insert anime into OrderedList
        orderedList.insert(anime);
    }

    file.close();
}

// Storage for PriorityQueue
void readCSV(const std::string& filename, PriorityQueue<Anime>& priorityQueue)
{
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    std::string name, genre, type;
    int id = 0, episodes = -1, members = -1;
    float rating = -1.0f;
    unsigned long long int lineNumber = 0;
    getline(file, line); // Ignore the first line

    while (getline(file, line))
    {
        ++lineNumber;
        std::stringstream ss(line);
        std::string data;

        // Read ID
        getline(ss, data, ',');
        id = stoi(data);

        // Read name
        getline(ss, data, ',');
        if (data[0] == '"')
        {
            name = data.substr(1);
            while (getline(ss, data, ','))
            {
                name += "," + data;
                if (data.back() == '"')
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

        // Insert anime into PriorityQueue with rating as priority
        priorityQueue.push(anime, rating);  // Using rating as the priority
    }

    file.close();
}


void testStoragePerformance(LinkedList<Anime>& linkedList, DoublyLinkedList<Anime>& doublyLinkedList, Queue<Anime>& queue, Stack<Anime>& stack, DynamicArray<Anime>& dynamicArray, OrderedList<Anime>& orderedList, PriorityQueue<Anime>& priorityQueue) {
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

    // Queue
    std::cout << "Queue" << std::endl;
    auto start2 = high_resolution_clock::now();
    readCSV(filename, queue);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);
    std::cout << "Milliseconds: " << duration2.count() << std::endl;
    std::cout << "############################################" << std::endl;

    // Stack
    std::cout << "Stack" << std::endl;
    auto start3 = high_resolution_clock::now();
    readCSV(filename, stack);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(stop3 - start3);
    std::cout << "Milliseconds: " << duration3.count() << std::endl;
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
    std::cout << "Milliseconds: " << duration_cast<milliseconds>(stop - start).count() << std::endl;
    std::cout << "############################################" << std::endl;

    // Priority Queue
    std::cout << "Priority Queue" << std::endl;
    start = high_resolution_clock::now();
    readCSV(filename, priorityQueue);
    stop = high_resolution_clock::now();
    std::cout << "Milliseconds: " << duration_cast<milliseconds>(stop - start).count() << std::endl;
    std::cout << "############################################" << std::endl;
}


#endif