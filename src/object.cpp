#include "object.hpp"

Object::Object(std::vector<GLfloat> vertexPositions, 
               std::vector<GLfloat> vertexColors, 
               std::vector<GLuint> vertexIndices) {
    m_vertexPositions = {-0.5f   , -0.5f , -1.0f,
                         0.5f    , -0.5f , -1.0f,
                         0.5f    , 0.5f  , -1.0f,
                         -0.5f   , 0.5f  , -1.0f,
                         -0.5f   , -0.5f , -2.0f,
                         0.5f    , -0.5f , -2.0f,
                         0.5f    , 0.5f  , -2.0f,
                         -0.5f   , 0.5f  , -2.0f};
    m_vertexColors =    {1.0f    , 0.0f  , 0.0f,
                         0.0f    , 1.0f  , 0.0f,
                         0.0f    , 0.0f  , 1.0f,
                         0.0f    , 0.0f  , 1.0f,
                         1.0f    , 0.0f  , 0.0f,
                         0.0f    , 1.0f  , 0.0f,
                         0.0f    , 0.0f  , 1.0f,
                         0.0f    , 0.0f  , 1.0f};
    m_vertexIndices =   {0, 1, 3,
                         1, 2, 3,
                         1, 2, 5,
                         5, 6, 2,
                         3, 2, 7,
                         2, 6, 7,
                         2, 6, 7,
                         0, 1, 4,
                         1, 5, 4,
                         5, 4, 6,
                         4, 6, 7,
                         4, 0, 7,
                         0, 7, 3};
    m_attributesPerVertex = 6;
    m_vertexCount = m_vertexPositions.size()/3;
    m_indexCount = m_vertexIndices.size();
    m_model = glm::mat4(1.0f);
    m_bufferData = std::vector<GLfloat>(m_vertexPositions.size()*2);

    for (int i = 0; i < m_vertexCount; ++i) {
        m_bufferData[i*m_attributesPerVertex + 0] = m_vertexPositions[i*3 + 0];
        m_bufferData[i*m_attributesPerVertex + 1] = m_vertexPositions[i*3 + 1];
        m_bufferData[i*m_attributesPerVertex + 2] = m_vertexPositions[i*3 + 2];

        m_bufferData[i*m_attributesPerVertex + 3] = m_vertexColors[i*3 + 0];
        m_bufferData[i*m_attributesPerVertex + 4] = m_vertexColors[i*3 + 1];
        m_bufferData[i*m_attributesPerVertex + 5] = m_vertexColors[i*3 + 2];
    }

    GLuint vertexCount = m_vertexIndices.size();
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_bufferData.size() * sizeof(GLfloat), m_bufferData.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexIndices.size() * sizeof(GLuint), m_vertexIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

glm::mat4* Object::model() {
    return &m_model;
}

void Object::leftMultMatrix(glm::mat4 transformation) {
    m_model = transformation * m_model;
}

void Object::draw() {
    if (m_vertexDataChanged) {
        recalculateBufferData();
        m_vertexDataChanged = false;
    }
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}

GLuint Object::vao() {
    return m_vao;
}

GLuint Object::vbo() {
    return m_vbo;
}

void Object::recalculateBufferData() {
    m_bufferData = std::vector<GLfloat>(m_vertexPositions.size()*2);

    for (int i = 0; i < m_vertexCount; ++i) {
        m_bufferData[i*m_attributesPerVertex + 0] = m_vertexPositions[i*3 + 0];
        m_bufferData[i*m_attributesPerVertex + 1] = m_vertexPositions[i*3 + 1];
        m_bufferData[i*m_attributesPerVertex + 2] = m_vertexPositions[i*3 + 2];

        m_bufferData[i*m_attributesPerVertex + 3] = m_vertexColors[i*3 + 0];
        m_bufferData[i*m_attributesPerVertex + 4] = m_vertexColors[i*3 + 1];
        m_bufferData[i*m_attributesPerVertex + 5] = m_vertexColors[i*3 + 2];
    }

    glNamedBufferSubData(m_vbo, 0, m_bufferData.size() * sizeof(GLfloat), m_bufferData.data());
}

