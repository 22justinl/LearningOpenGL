#pragma once

#include "glm/glm.hpp"

class Camera {
public:
    Camera();

    glm::mat4 viewMatrix() const;

    void mouseTurn(float relX, float relY);

    void moveForward();
    void moveBackward();

    void moveRight();
    void moveLeft();

    void moveUp();
    void moveDown();
private:
    glm::vec3 m_eye;              // position
    glm::vec3 m_up;               // direction of up
    glm::vec3 m_viewDirection;    // eye + viewDirection = center

    float m_sensitivity = 0.1;
    float m_speed = 0.1;
};
