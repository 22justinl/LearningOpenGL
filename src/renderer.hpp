#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "objectmanager.hpp"

#include <string>

class Renderer {
public:
    Renderer(ObjectManager* om);

    void setClearColor(float r, float g, float b, float a);
    void setViewPort(GLint x, GLint y, GLsizei height, GLsizei width);

    void setProgram(GLuint program);
    void compileShaders(std::string vsspath, std::string fsspath);

    void getUniformLocations();

    void setCameraViewUniform(glm::mat4* cameraViewMatrix);
    void setModelUniform(glm::mat4* modelMatrix);

    void draw();
    int m_cameraViewMatrixLoc;
    int m_modelLoc;
private:
    ObjectManager* m_objectManager;
    GLuint m_program;

};
