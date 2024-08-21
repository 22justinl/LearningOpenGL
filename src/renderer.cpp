#include "renderer.hpp"
#include "utils.hpp"

#include <iostream>

Renderer::Renderer(ObjectManager* om): m_objectManager(om) {
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    compileShaders("shaders/vertexshader.glsl", "shaders/fragshader.glsl");
    getUniformLocations();
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::setViewPort(GLint x, GLint y, GLsizei height, GLsizei width) {
    glViewport(x, y, height, width);
}

void Renderer::setProgram(GLuint program) {
    glUseProgram(program);
}

void Renderer::compileShaders(std::string vsspath, std::string fsspath) {
    m_program = glCreateProgram();
    std::string vertexshadersource = LoadShaderFromFile(vsspath);
    std::string fragmentshadersource = LoadShaderFromFile(fsspath);

    const char* vertexshadersrc = vertexshadersource.c_str();
    const char* fragmentshadersrc = fragmentshadersource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexshadersrc, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentshadersrc, nullptr);
    glCompileShader(fragmentShader);

    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    glValidateProgram(m_program);
    glUseProgram(m_program);
}

void Renderer::getUniformLocations() {
    m_cameraViewMatrixLoc = glGetUniformLocation(m_program, "u_cameraViewMatrix");
    if (m_cameraViewMatrixLoc < 0) {
        std::cout << "u_cameraViewMatrix location not found" << std::endl;
    }
    
    m_modelLoc = glGetUniformLocation(m_program, "u_model");
    if (m_modelLoc < 0) {
        std::cout << "u_model location not found" << std::endl;
    }
}

void Renderer::setCameraViewUniform(glm::mat4* cameraViewMatrix) {
    glUniformMatrix4fv(m_cameraViewMatrixLoc, 1, GL_FALSE, &(*cameraViewMatrix)[0][0]);
}

void Renderer::setModelUniform(glm::mat4* modelMatrix) {
    glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, &(*modelMatrix)[0][0]);
}

void Renderer::draw() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    for (auto* obj : m_objectManager->objects()) {
        if (obj->visible()) {
            continue;
        }

        setModelUniform(obj->model());
        obj->draw();
    }
}
