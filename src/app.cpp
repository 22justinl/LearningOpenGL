#include <iostream>

#include "app.hpp"

App::App(unsigned int w, unsigned int h): m_screenWidth(w), m_screenHeight(h) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Failed to initialize SDL" << std::endl;
        exit(1);
    }
    
    // Use OpenGL version 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create window and OpenGL context
    m_window = SDL_CreateWindow("window", screenWidth(), screenHeight(), SDL_WINDOW_OPENGL);
    m_glcontext = SDL_GL_CreateContext(window());
    SDL_GL_MakeCurrent(window(), glcontext());
    
    if (!SDL_GL_GetCurrentContext() || !gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        exit(1);
    }

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    SDL_GL_SetSwapInterval(1);

    SDL_SetRelativeMouseMode(true);
}

void App::Exit() {
    SDL_GL_DeleteContext(glcontext());
    SDL_DestroyWindow(m_window);

    SDL_Quit();
    exit(0);
}

App::~App() {
    Exit();
}
