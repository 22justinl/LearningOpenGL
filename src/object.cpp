#include "object.hpp"

Object::Object(std::vector<GLfloat> vertexPositions, 
               std::vector<GLfloat> vertexColors, 
               std::vector<GLuint> vertexIndices): m_vertexPositions(vertexPositions),
                                                   m_vertexColors(vertexColors), 
                                                   m_vertexIndices(vertexIndices) {

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

glm::mat4* const Object::model() {
    if (m_modelChanged) {
        m_model = glm::translate(glm::mat4(1), position()) * glm::scale(glm::mat4(1), scale());
        // m_model = glm::rotate... * glm::scale... * glm::translate(glm::mat4(1), position());
        m_modelChanged = false;
    }
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

GLuint Object::vao() const {
    return m_vao;
}

GLuint Object::vbo() const {
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

glm::vec3 Object::position() const {
    return m_position;
}

void Object::setPosition(glm::vec3 pos) {
    if (pos == m_position) {
        return;
    }
    m_modelChanged = true;
    m_position = pos;
}

glm::vec3 Object::velocity() const {
    return m_velocity;
}

void Object::setVelocity(glm::vec3 vel) {
    m_velocity = vel;
}

glm::vec3 Object::acceleration() const {
    return m_acceleration;
}

void Object::setAcceleration(glm::vec3 acc) {
    m_acceleration = acc;
}

glm::vec3 Object::scale() const {
    return m_scale;
}

void Object::setScale(glm::vec3 scale) {
    if (scale == m_scale) {
        return;
    }
    m_modelChanged = true;
    m_scale = scale;
}


bool Object::isGravityOn() const {
    return m_gravity;
}

void Object::setGravity(bool b) {
    m_gravity = b;
    glm::vec3 acc = acceleration() + glm::vec3(0.0f, GRAVITY, 0.0f);
    setAcceleration(acc);
}
