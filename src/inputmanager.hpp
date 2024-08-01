#pragma once

#include <SDL3/SDL.h>

#include "camera.hpp"

class InputManager {
public:
    InputManager();

    void setCamera(Camera* c);
    Camera* camera();

    bool handleEvents();
private:
    Camera* m_camera;
    SDL_Event m_event;

    const Uint8* m_keys;
};
