#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>

class Cube {
public:
    Cube();

    glm::mat4 model();
    void leftMultMatrix(glm::mat4 transformation);
    
    void draw();
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
    std::vector<GLint> m_vertexIndices;

    std::vector<GLfloat> m_bufferData;

    // When vertex data is changed set to true
    // Recalculate m_bufferData before draw
    // Removes unneccessary bufferData calculations
    bool m_vertexDataChanged;
};
