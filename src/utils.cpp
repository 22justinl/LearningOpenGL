#include "utils.hpp"
#include <fstream>

std::string LoadShaderFromFile(const std::string& path) {
    std::string result;
    std::string line;
    std::ifstream file(path.c_str());
    if (file.is_open()) {
        while (file.good()) {
            std::getline(file, line);
            result += line + "\n";
        }
        file.close();
    }
    return result;
}

