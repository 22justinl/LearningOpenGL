#define GL_SILENCE_DEPRECATION

// -------------- INCLUDES ------------
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string>
#include <fstream>

#include <iostream>

#include "app.hpp"
#include "camera.hpp"
#include "utils.hpp"

void CreateGraphicsPipeline(GLuint& program, std::string vsspath, std::string fsspath) {
    program = glCreateProgram();
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

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glValidateProgram(program);
}

// NOTE: RIGHT HANDED COORDS (+x right, +y up, -z into screen)
int main() {
    App app;

    // setup cube
    std::vector<GLfloat> cubeVertexPos =     {-0.5f   , -0.5f , -1.0f,
                                                0.5f    , -0.5f , -1.0f,
                                                0.5f    , 0.5f  , -1.0f,
                                                -0.5f   , 0.5f  , -1.0f,
                                                -0.5f   , -0.5f , -2.0f,
                                                0.5f    , -0.5f , -2.0f,
                                                0.5f    , 0.5f  , -2.0f,
                                                -0.5f   , 0.5f  , -2.0f};

    std::vector<GLfloat> cubeVertexCol =     {1.0f    , 0.0f  , 0.0f,
                                                0.0f    , 1.0f  , 0.0f,
                                                0.0f    , 0.0f  , 1.0f,
                                                0.0f    , 0.0f  , 1.0f,
                                                1.0f    , 0.0f  , 0.0f,
                                                0.0f    , 1.0f  , 0.0f,
                                                0.0f    , 0.0f  , 1.0f,
                                                0.0f    , 0.0f  , 1.0f};

    std::vector<GLfloat> cubeVertexPosCol =  {-0.5f   , -0.5f , -1.0f,
                                                1.0f    , 0.0f  , 0.0f,

                                                0.5f    , -0.5f , -1.0f,
                                                0.0f    , 1.0f  , 0.0f,

                                                0.5f    , 0.5f  , -1.0f,
                                                0.0f    , 0.0f  , 1.0f,

                                                -0.5f   , 0.5f  , -1.0f,
                                                0.0f    , 0.0f  , 1.0f,

                                                -0.5f   , -0.5f , -2.0f,
                                                1.0f    , 0.0f  , 0.0f,

                                                0.5f    , -0.5f , -2.0f,
                                                0.0f    , 1.0f  , 0.0f,

                                                0.5f    , 0.5f  , -2.0f,
                                                0.0f    , 0.0f  , 1.0f,

                                                -0.5f   , 0.5f  , -2.0f,
                                                0.0f    , 0.0f  , 1.0f};

    std::vector<GLuint> cubeVertexIndices =  {0, 1, 3,
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
    
    GLuint cubeVertexCount = cubeVertexIndices.size();

    GLuint vao;
    GLuint vbo;
    GLuint ibo;

    // Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex Buffer Object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cubeVertexPosCol.size() * sizeof(GLfloat), cubeVertexPosCol.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeVertexIndices.size() * sizeof(GLuint), cubeVertexIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // TODO: New class?
    GLuint program;
    CreateGraphicsPipeline(program, "shaders/vertexshader.glsl", "shaders/fragshader.glsl");

    // Uniforms
    glm::mat4 u_cameraViewMatrix;
    GLuint u_cameraViewMatrixLoc = glGetUniformLocation(program, "u_cameraViewMatrix");
    if (u_cameraViewMatrixLoc < 0) {
        std::cout << "u_cameraViewMatrix location not found" << std::endl;
    }

    // Setup
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, app.screenWidth(), app.screenHeight());
    glUseProgram(program);

    // Main loop
    bool quit = false;
    while (!quit) {
        quit = app.inputManager()->handleEvents();

        u_cameraViewMatrix = app.camera()->projectionMatrix() * app.camera()->viewMatrix();
        glUniformMatrix4fv(u_cameraViewMatrixLoc, 1, GL_FALSE, &u_cameraViewMatrix[0][0]);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, cubeVertexCount, GL_UNSIGNED_INT, 0);
        SDL_GL_SwapWindow(app.window());
    }

    return 0;
}
