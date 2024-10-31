#ifndef TO_LOWER_HPP
#define TO_LOWER_HPP

#include <algorithm>
#include <string>

// Función para convertir una cadena a minúsculas
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

#endif // TO_LOWER_HPP
