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

#include "utils.hpp"
#include "camera.h"

#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720

void Initialize(SDL_Window*& window, SDL_GLContext& glcontext) {
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
    window = SDL_CreateWindow("window", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    glcontext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glcontext);
    
    if (!SDL_GL_GetCurrentContext() || !gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        exit(1);
    }
    SDL_GL_SetSwapInterval(1);

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

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

int main() {
    SDL_Window* window;
    SDL_GLContext glcontext;
    Initialize(window, glcontext);

    // setup square
    std::vector<GLfloat> squareVertexPos =     {-0.5f   , -0.5f , 0.0f,
                                                0.5f    , -0.5f , 0.0f,
                                                0.5f    , 0.5f  , 0.0f,
                                                -0.5f   , 0.5f  , 0.0f};

    std::vector<GLfloat> squareVertexCol =     {1.0f    , 0.0f  , 0.0f,
                                                0.0f    , 1.0f  , 0.0f,
                                                0.0f    , 0.0f  , 1.0f,
                                                0.0f    , 0.0f  , 1.0f};

    std::vector<GLuint> squareVertexIndices =  {0, 1, 3,
                                                1, 2, 3};
    GLuint squareVertexCount = squareVertexIndices.size();

    // access data
    GLuint vao;
    GLuint vbo_pos;
    GLuint vbo_col;
    GLuint ibo;

    // Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex Buffer Object
    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, squareVertexPos.size() * sizeof(GLfloat), squareVertexPos.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);

    glGenBuffers(1, &vbo_col);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_col);
    glBufferData(GL_ARRAY_BUFFER, squareVertexCol.size() * sizeof(GLfloat), squareVertexCol.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, squareVertexIndices.size() * sizeof(GLuint), squareVertexIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    GLuint program;
    CreateGraphicsPipeline(program, "shaders/vertexshader.glsl", "shaders/fragshader.glsl");

    SDL_Event e;
    const Uint8* keys;
    bool quit = false;
    while (!quit) {
        if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    quit = true;
                    std::cout << "Quit" << std::endl;
                    break;
            }
        }
        keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_ESCAPE]) {
                quit = true;
                std::cout << "Quit" << std::endl;
                break;
        }

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, squareVertexCount, GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;

    return 0;
}

