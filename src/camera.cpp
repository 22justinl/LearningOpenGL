#include "camera.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

Camera::Camera(): eye(0, 0, 0), viewDirection(0, 0, -1), up(0, 1, 0) {}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(eye, eye + viewDirection, up);
}

void Camera::MouseTurn(float relX, float relY) {
    viewDirection = glm::rotate(viewDirection, glm::radians(-relY * sensitivity), glm::cross(viewDirection, up));
    viewDirection = glm::rotate(viewDirection, glm::radians(-relX * sensitivity), up);
}

void Camera::MoveForward() {
    eye += viewDirection * speed;
}

void Camera::MoveBackward() {
    eye -= viewDirection * speed;
}

void Camera::MoveRight() {
    eye += glm::normalize(glm::cross(viewDirection, up)) * speed;
}

void Camera::MoveLeft() {
    eye -= glm::normalize(glm::cross(viewDirection, up)) * speed;
}

void Camera::MoveUp() {
    eye += up * speed;
}

void Camera::MoveDown() {
    eye -= up * speed;
}
