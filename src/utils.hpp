#pragma once

#include <string>

#include <iostream>

std::string LoadShaderFromFile(const std::string& path);

void fps_counter(unsigned int& frames, std::chrono::time_point<std::chrono::steady_clock>& startTime, std::vector<double>& fps_acc);
