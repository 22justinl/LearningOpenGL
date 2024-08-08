#include "renderer.hpp"

Renderer::Renderer() {
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::setProgram(GLuint program) {
    glUseProgram(program);
}

void Renderer::setViewPort(GLint x, GLint y, GLsizei height, GLsizei width) {
    glViewport(x, y, height, width);
}

void Renderer::draw() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
