void readCSV(const std::string& filename, OrderedList<Anime>& ol)
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

    // Ignorar la primera línea si contiene encabezados
    getline(file, line);

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string data;

        // Diagnóstico: imprime la línea actual para verificar el contenido
        std::cout << "Processing line: " << line << std::endl;

        try {
            // Leer ID y verificar si es numérico
            getline(ss, data, ',');
            id = !data.empty() ? stoi(data) : 0;

            // Leer nombre y verificar si está vacío
            getline(ss, data, ',');
            name = !data.empty() ? data : "Unknown";  // Asignar "Unknown" si no hay nombre

            // Leer género
            getline(ss, data, ',');
            genre = !data.empty() ? data : "Unknown";

            // Leer tipo
            getline(ss, data, ',');
            type = !data.empty() ? data : "Unknown";

            // Leer episodios y verificar si es numérico
            getline(ss, data, ',');
            episodes = (!data.empty() && data != "Unknown") ? stoi(data) : -1;

            // Leer rating y verificar si es numérico
            getline(ss, data, ',');
            rating = !data.empty() ? stof(data) : -1.0f;

            // Leer miembros y verificar si es numérico
            getline(ss, data, ',');
            members = !data.empty() ? stoi(data) : 0;

            // Crear el objeto Anime
            Anime anime(id, name, genre, type, episodes, rating, members);
            ol.insert(anime);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: dato inválido en la línea: " << line << std::endl;
            continue;  // Omitir la línea con el error y continuar con la siguiente
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: dato fuera de rango en la línea: " << line << std::endl;
            continue;  // Omitir la línea con el error y continuar con la siguiente
        }
    }

    file.close();
}