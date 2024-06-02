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
} My2dObject;

using std::vector;

// -------------- DEFINES -------------
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGHT   720

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("window", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_Event e;
    const Uint8* keys;

    vector<My2dObject> objs;

    // SDL_Surface* surf = SDL_CreateSurface(200, 200, SDL_PIXELFORMAT_RGBA32);
    // Uint32 surf_color = SDL_MapRGBA(surf->format, 255, 255, 0, 255);
    // SDL_FillSurfaceRect(surf, NULL, surf_color);

    SDL_FRect r = {0.f, 0.f, 100.f, 100.f};
    ColorRGBA obj1_color = {255, 255, 0, 255};
    My2dObject obj1 = {0, 0, r, obj1_color};
    objs.push_back(obj1);

    r = {200.f, 200.f, 150.f, 500.f};
    ColorRGBA obj2_color = {0, 0, 255, 255};
    My2dObject obj2 = {0, 0, r, obj2_color};
    objs.push_back(obj2);

    bool running = true;
    while (running) {
        if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    std::cout << "Quit" << std::endl;
                    break;
            }
        }

        keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_ESCAPE]) {
                running = false;
                std::cout << "Quit" << std::endl;
                break;
        }

        for (const My2dObject& o : objs) {
            SDL_SetRenderDrawColor(renderer, o.color.r, o.color.g, o.color.b, o.color.a);
            SDL_RenderFillRect(renderer, &o.rect);
        }

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
