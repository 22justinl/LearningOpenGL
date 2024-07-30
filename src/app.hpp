#pragma once

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class App {
public:
    App(unsigned int w = 1280, unsigned int h = 720);

    unsigned int screenWidth() const { return m_screenWidth; };
    unsigned int screenHeight() const { return m_screenHeight; };

    SDL_Window* window() const { return m_window; };
    SDL_GLContext glcontext() const { return m_glcontext; };

    void Exit();
    ~App();
private:
    SDL_Window* m_window;
    SDL_GLContext m_glcontext;

    unsigned int m_screenWidth;
    unsigned int m_screenHeight;
};
