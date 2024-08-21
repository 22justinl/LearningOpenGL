#include "physics.hpp"

Physics::Physics(ObjectManager* objectManager): m_objectManager(objectManager) {

}

void Physics::incrementTimeStep(std::chrono::duration<double> timeDuration) {
    double time = timeDuration.count();
    glm::vec3 timeVec = glm::vec3(time);
    for (Object* obj : m_objectManager->objects()) {
        if (!obj->isGravityOn()) {
            continue;
        }
        glm::vec3 vel = obj->velocity() + (timeVec * obj->acceleration());
        glm::vec3 pos = obj->position() + (timeVec * obj->velocity());

        if (pos.y < 0) {
            vel.y = 10;
        }

        obj->setPosition(pos);
        obj->setVelocity(vel);
    }
}
