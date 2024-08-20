#include "objectmanager.hpp"

ObjectManager::ObjectManager() {

}

std::vector<Object*>& ObjectManager::objects() {
    return m_objects;
}

Object* ObjectManager::createObject(std::vector<GLfloat> vertexPositions, 
                                    std::vector<GLfloat> vertexColors, 
                                    std::vector<GLuint> vertexIndices) {
    Object* obj = new Object(vertexPositions, vertexColors, vertexIndices);
    objects().push_back(obj);
    return obj;
}

Cube* ObjectManager::createCube() {
    Cube* cube = new Cube();
    objects().push_back(cube);
    return cube;
}
