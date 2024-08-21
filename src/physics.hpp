#pragma once

#include <chrono>

#include "objectmanager.hpp"

class Physics {
public: 
    Physics(ObjectManager* objectManager);

    void incrementTimeStep(std::chrono::duration<double> timeDuration);
private:
    ObjectManager* m_objectManager;
};
