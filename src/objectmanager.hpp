#pragma once

#include "object.hpp"
#include "cube.hpp"

#include <vector>

class ObjectManager {
public:
    ObjectManager();
    std::vector<Object*>& objects();

    Object* createObject(std::vector<GLfloat> vertexPositions, 
                         std::vector<GLfloat> vertexColors, 
                         std::vector<GLuint> vertexIndices);
    Cube* createCube();
private:
    std::vector<Object*> m_objects;
};
