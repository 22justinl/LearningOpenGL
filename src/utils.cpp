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

void fps_counter(unsigned int& frames, std::chrono::time_point<std::chrono::steady_clock>& startTime, std::vector<double>& fps_acc) {
    if (std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime) >= std::chrono::duration<double>(0.25)) {
        double d = std::chrono::duration<double>(frames) / std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime);
        // std::cout << d << std::endl;
        fps_acc.push_back(d);
        startTime = std::chrono::steady_clock::now();
        frames = 0;
    } else {
        frames++;
    }
}
