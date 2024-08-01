#pragma once

#include "glm/glm.hpp"

class Camera {
public:
    Camera(unsigned int w, unsigned int h);
    
    struct ProjectionMode {
        bool perspective;
    
        // Perspective projection only
        float fovy;
        float aspect;
    
        // Orthogonal projection only
        float left;
        float right;
        float bottom;
        float top;
    
        // Both
        float zNear;
        float zFar;
    };

    glm::mat4 viewMatrix() const;
    glm::mat4 projectionMatrix() const;
    void setProjectionMode(ProjectionMode p);

    void setPerspectiveMode();
    void setOrthogonalMode();

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

    ProjectionMode m_projectionMode;
    glm::mat4 m_projectionMatrix;

    unsigned int m_screenWidth;
    unsigned int m_screenHeight;

    float m_sensitivity = 0.1;
    float m_speed = 0.1;
};
