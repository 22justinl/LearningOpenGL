#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// -------------- INCLUDES ------------
#include <iostream>
#include <vector>

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

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("window", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    // SDL_Event e;
    // const Uint8* keys;

    // vector<My2dObject*> objs;

    // SDL_FRect r1 = {0.f, 0.f, 100.f, 100.f};
    // ColorRGBA obj1_color = {255, 255, 0, 255};
    // My2dObject* obj1 = new My2dObject(0, 0, r1, obj1_color);
    // objs.push_back(obj1);

    // SDL_FRect r2 = {200.f, 200.f, 150.f, 500.f};
    // ColorRGBA obj2_color = {0, 0, 255, 255};
    // My2dObject* obj2 = new My2dObject(0.5, 0, r2, obj2_color);
    // objs.push_back(obj2);

    // My2dObject* player = objs[0];

    // bool running = true;
    // while (running) {
    //     if (SDL_PollEvent(&e) != 0) {
    //         switch (e.type) {
    //             case SDL_EVENT_QUIT:
    //                 running = false;
    //                 std::cout << "Quit" << std::endl;
    //                 break;
    //         }
    //     }

    //     keys = SDL_GetKeyboardState(NULL);
    //     if (keys[SDL_SCANCODE_ESCAPE]) {
    //             running = false;
    //             std::cout << "Quit" << std::endl;
    //             break;
    //     }

    //     if (keys[SDL_SCANCODE_W]) {
    //         player->dy = -1;
    //     } else if (keys[SDL_SCANCODE_S]) {
    //         player->dy = 1;
    //     } else {
    //         player->dy = 0;
    //     }

    //     if (keys[SDL_SCANCODE_A]) {
    //         player->dx = -1;
    //     } else if (keys[SDL_SCANCODE_D]) {
    //         player->dx = 1;
    //     } else {
    //         player->dx = 0;
    //     }

    //     // moving 2d rects
    //     for (My2dObject* o : objs) {
    //         o->rect.x += o->dx;
    //         o->rect.y += o->dy;
    //     }

    //     for (const My2dObject* o : objs) {
    //         SDL_SetRenderDrawColor(renderer, o->color.r, o->color.g, o->color.b, o->color.a);
    //         SDL_RenderFillRect(renderer, &o->rect);
    //     }
    //     SDL_RenderPresent(renderer);
    //     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //     SDL_RenderClear(renderer);
    // }
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
