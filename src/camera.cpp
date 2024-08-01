#include "camera.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

Camera::Camera(): m_eye(0, 0, 0), m_viewDirection(0, 0, -1), m_up(0, 1, 0) {

}

glm::mat4 Camera::viewMatrix() const {
    return glm::lookAt(m_eye, m_eye + m_viewDirection, m_up);
}

void Camera::mouseTurn(float relX, float relY) {
    m_viewDirection = glm::rotate(m_viewDirection, glm::radians(-relY * m_sensitivity), glm::cross(m_viewDirection, m_up));
    m_viewDirection = glm::rotate(m_viewDirection, glm::radians(-relX * m_sensitivity), m_up);
}

void Camera::moveForward() {
    m_eye += m_viewDirection * m_speed;
}

void Camera::moveBackward() {
    m_eye -= m_viewDirection * m_speed;
}

void Camera::moveRight() {
    m_eye += glm::normalize(glm::cross(m_viewDirection, m_up)) * m_speed;
}

void Camera::moveLeft() {
    m_eye -= glm::normalize(glm::cross(m_viewDirection, m_up)) * m_speed;
}

void Camera::moveUp() {
    m_eye += m_up * m_speed;
}

void Camera::moveDown() {
    m_eye -= m_up * m_speed;
}
