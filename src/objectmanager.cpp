#include "objectmanager.hpp"

ObjectManager::ObjectManager() {

}

std::vector<Cube*>& ObjectManager::objects() {
    return m_objects;
}

Cube* ObjectManager::createCube() {
    Cube* cube = new Cube();
    objects().push_back(cube);
    return cube;
}
