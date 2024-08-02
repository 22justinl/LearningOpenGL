#pragma once

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "camera.hpp"
#include "inputmanager.hpp"

class App {
public:
    App(unsigned int w = 1280, unsigned int h = 720);

    SDL_Window* window() const;
    SDL_GLContext glcontext() const;

    InputManager* inputManager() const;

    Camera* camera() const;
    void setCamera(Camera* c);

    unsigned int screenWidth() const;
    unsigned int screenHeight() const;

    void exitApp();
    ~App();
private:
    SDL_Window* m_window;
    SDL_GLContext m_glcontext;
    FT_Library m_library;

    InputManager* m_inputManager;

    Camera* m_camera;

    unsigned int m_screenWidth;
    unsigned int m_screenHeight;
};
