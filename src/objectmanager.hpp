#pragma once

#include "cube.hpp"

#include <vector>

class ObjectManager {
public:
    ObjectManager();
    std::vector<Cube*>& objects();

    Cube* createCube();
private:
    std::vector<Cube*> m_objects;
};
