#pragma once

#include "glm/glm.hpp"

class Camera {
public:
    Camera();

    glm::mat4 ViewMatrix() const;

    void MouseTurn(float relX, float relY);

    void MoveForward();
    void MoveBackward();

    void MoveRight();
    void MoveLeft();

    void MoveUp();
    void MoveDown();
private:
    glm::vec3 eye;              // position
    glm::vec3 up;               // direction of up
    glm::vec3 viewDirection;    // eye + viewDirection = center

    float sensitivity = 0.1;
    float speed = 0.1;
};
