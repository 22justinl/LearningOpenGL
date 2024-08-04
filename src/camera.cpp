#include "camera.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include <iostream>

Camera::Camera(unsigned int w, unsigned int h): m_eye(0, 0, 0), m_viewDirection(0, 0, -1), m_up(0, 1, 0), m_screenWidth(w), m_screenHeight(h) {
    // Default
    ProjectionMode p = {true, glm::radians(45.f), (float)w/(float)h, 0, 0, 0, 0, 0.1f, 10.f};
    setProjectionMode(p);
}

glm::mat4 Camera::viewMatrix() const {
    return glm::lookAt(m_eye, m_eye + m_viewDirection, m_up);
}

glm::mat4 Camera::projectionMatrix() const {
    return m_projectionMatrix;
}

void Camera::setProjectionMode(ProjectionMode p) {
    m_projectionMode = p;
    if (p.perspective) {
        m_projectionMatrix = glm::perspective(p.fovy, p.aspect, p.zNear, p.zFar);
    } else {
        m_projectionMatrix = glm::ortho(p.left, p.right, p.bottom, p.top, p.zNear, p.zFar);
    }
}

void Camera::setPerspectiveMode() {
    Camera::ProjectionMode persp = {true, glm::radians(45.f), (float)m_screenWidth/(float)m_screenHeight, 0, 0, 0, 0, 0.1f, 10.f};
    setProjectionMode(persp);
}

void Camera::setOrthogonalMode() {
    Camera::ProjectionMode ortho = {false, 0, 0, -4, 4, -4, 4, 0.1f, 10.f};
    setProjectionMode(ortho);
}

void Camera::mouseTurn(float relX, float relY) {
    if (    (m_viewDirection[1] > 0.98 && relY < 0) || 
            (m_viewDirection[1] < -0.98 && relY > 0)) {
        relY = 0;
    }
    m_viewDirection = glm::rotate(m_viewDirection, glm::radians(-relX * m_sensitivity), m_up);
    m_viewDirection = glm::rotate(m_viewDirection, glm::radians(-relY * m_sensitivity), glm::cross(m_viewDirection, m_up));
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
