#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#define GRAVITY -9.81

class Object {
public:
    Object(std::vector<GLfloat> vertexPositions, 
           std::vector<GLfloat> vertexColors, 
           std::vector<GLuint> vertexIndices);

    glm::mat4* const model();
    // Remove later (replace with specific transformation functions?)
    void leftMultMatrix(glm::mat4 transformation);
    void draw();

    GLuint vao() const;
    GLuint vbo() const;

    // Object Properties
    glm::vec3 position() const;
    void setPosition(glm::vec3 pos);
    glm::vec3 velocity() const;
    void setVelocity(glm::vec3 vel);
    glm::vec3 acceleration() const;
    void setAcceleration(glm::vec3 acc);

    glm::vec3 scale() const;
    void setScale(glm::vec3 scale);


    bool isGravityOn() const;
    void setGravity(bool b);

private:
    void recalculateBufferData();

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;

    unsigned int m_vertexCount;
    unsigned int m_indexCount;
    unsigned int m_attributesPerVertex;

    glm::mat4 m_model;
    std::vector<GLfloat> m_vertexPositions;
    std::vector<GLfloat> m_vertexColors;
    std::vector<GLuint> m_vertexIndices;

    std::vector<GLfloat> m_bufferData;

    // When vertex data is changed set to true
    // Recalculate m_bufferData before draw
    // Removes unneccessary bufferData calculations
    bool m_vertexDataChanged = false;
    bool m_modelChanged = false;

    // Physics Properties
    glm::vec3 m_position = {0,0,0};
    glm::vec3 m_velocity = {0,0,0};
    glm::vec3 m_acceleration = {0,0,0};
    glm::vec3 m_scale = {1,1,1};

    bool m_gravity = false;
};
