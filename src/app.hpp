#pragma once

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "camera.hpp"
#include "inputmanager.hpp"
#include "renderer.hpp"

class App {
public:
    App(unsigned int w = 1280, unsigned int h = 720);

    SDL_Window* window() const;
    SDL_GLContext glcontext() const;

    InputManager* inputManager() const;

    Renderer* renderer() const;

    Camera* camera() const;
    void setCamera(Camera* c);

    unsigned int screenWidth() const;
    unsigned int screenHeight() const;

    void exitApp();
    ~App();
private:
    SDL_Window* m_window;
    SDL_GLContext m_glcontext;

    InputManager* m_inputManager;
    Renderer* m_renderer;

    Camera* m_camera;

    unsigned int m_screenWidth;
    unsigned int m_screenHeight;
};
