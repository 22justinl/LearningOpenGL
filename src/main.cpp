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
#include "renderer.hpp"
#include "utils.hpp"


// NOTE: RIGHT HANDED COORDS (+x right, +y up, -z into screen)
int main() {
    App app;

    for (int i = 0; i < 1000; ++i) {
        Cube* object = app.objectManager()->createCube();
        object->leftMultMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(i, i, i)));
    }

    // Renderer
    Renderer renderer(app.objectManager());
    renderer.setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    renderer.setViewPort(0, 0, app.screenWidth(), app.screenHeight());

    // Uniform copy
    glm::mat4 viewMatrix;

    // FPS Counter Init
    unsigned int frames = 0;
    std::vector<double> fps_acc;
    auto startTime = std::chrono::steady_clock::now();

    // Main loop
    bool quit = false;
    while (!quit) {
        fps_counter(frames, startTime, fps_acc);

        // Camera uniform
        viewMatrix = app.camera()->projectionMatrix() * app.camera()->viewMatrix();
        renderer.setCameraViewUniform(&viewMatrix);

        renderer.draw();

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
