#pragma once

#include <glad/glad.h>

class Renderer {
public:
    Renderer();

    void setClearColor(float r, float g, float b, float a);
    void setProgram(GLuint program);
    void setViewPort(GLint x, GLint y, GLsizei height, GLsizei width);

    void draw();
private:

};
