#define GL_SILENCE_DEPRECATION

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glm/glm.hpp>

// -------------- INCLUDES ------------
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

typedef struct ColorRGBA {
    int r;
    int g;
    int b;
    int a;
} ColorRGBA;

typedef struct My2dObject{
    float dx;
    float dy;
    SDL_FRect rect;
    ColorRGBA color;
    My2dObject(float _dx, float _dy, SDL_FRect _rect, ColorRGBA _color): dx(_dx), dy(_dy), rect(_rect), color(_color) {}
} My2dObject;

using std::vector;

// -------------- DEFINES -------------
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720

SDL_Window* window;
SDL_GLContext glcontext;

SDL_Event e;
const Uint8* keys;
bool quit;

GLuint vao;
GLuint vbo;
GLuint ibo;

std::string vsspath = "shaders/vertexshader.glsl";
std::string fsspath = "shaders/fragshader.glsl";

GLuint program;

std::string LoadShaderFromFile(const std::string& path) {
    std::string result;
    std::string line;
    std::ifstream file(path.c_str());
    if (file.is_open()) {
        while (file.good()) {
            std::getline(file, line);
            result += line + "\n";
        }
        file.close();
    }
    return result;
}

void Initialize() {
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

int main() {
    Initialize();
    quit = false;

    // triangle
    const vector<GLfloat> vertexData {
        // First triangle
        -0.5f, -0.5f, 0.0f,
            1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,
            0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,
            0.0f, 0.0f, 1.0f,
        // Second triangle
        0.5f, 0.5f, 0.0f,
            0.0f, 0.0f, 1.0f
    };

    // Create Vertex Array Object (stores how we access vertex data)
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create Vertex Buffer Object (vertex data)
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);
    // Setup Vertex Array 
    // enable specified generic vertex attribute array
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);
    //      attribute index, 
    //      number of elements in attribute, 
    //      type, 
    //      normalize?, 
    //      stride (byte offset between consecutive instances of this attribute), 
    //      pointer (offset of the first component of the first of this attribute in the array)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

    const vector<GLuint> vertexIndices {2,0,1,3,2,1};
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(GLuint), vertexIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


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
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
