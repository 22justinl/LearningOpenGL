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
#include <chrono>

#include <iostream>

#include "app.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "cube.hpp"
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

    std::vector<Cube> objects;
    for (int i = 0; i < 1000; ++i) {
        objects.emplace_back();
        objects[i].leftMultMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(i, i, i)));
    }

    // TODO: New class?
    GLuint program;
    CreateGraphicsPipeline(program, "shaders/vertexshader.glsl", "shaders/fragshader.glsl");

    // Uniforms
    glm::mat4 u_cameraViewMatrix;
    GLuint u_cameraViewMatrixLoc = glGetUniformLocation(program, "u_cameraViewMatrix");
    if (u_cameraViewMatrixLoc < 0) {
        std::cout << "u_cameraViewMatrix location not found" << std::endl;
    }

    glm::mat4 u_model = glm::mat4(1.0f);
    GLuint u_modelLoc = glGetUniformLocation(program, "u_model");
    if (u_modelLoc < 0) {
        std::cout << "u_model location not found" << std::endl;
    }

    // Setup
    app.renderer()->setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    app.renderer()->setViewPort(0, 0, app.screenWidth(), app.screenHeight());
    app.renderer()->setProgram(program);

    // FPS Counter Init
    unsigned int frames = 0;
    std::vector<double> fps_acc;
    auto startTime = std::chrono::steady_clock::now();

    // Main loop
    bool quit = false;
    while (!quit) {
        fps_counter(frames, startTime, fps_acc);

        u_cameraViewMatrix = app.camera()->projectionMatrix() * app.camera()->viewMatrix();
        glUniformMatrix4fv(u_cameraViewMatrixLoc, 1, GL_FALSE, &u_cameraViewMatrix[0][0]);

        app.renderer()->draw();

        for (auto& obj : objects) {
            u_model = obj.model();
            glUniformMatrix4fv(u_modelLoc, 1, GL_FALSE, &u_model[0][0]);
            obj.draw();
        }
        SDL_GL_SwapWindow(app.window());

        quit = app.inputManager()->handleEvents();
    }

    double fps_avg = 0;
    for (double fps : fps_acc) {
        fps_avg += (double)fps/(double)fps_acc.size();
    }
    std::cout << "Average fps: " << fps_avg << std::endl;

    return 0;
}
