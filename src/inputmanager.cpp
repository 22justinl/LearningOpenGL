#include <iostream>

#include "inputmanager.hpp"

InputManager::InputManager() {

}

void InputManager::setCamera(Camera* c) {
    m_camera = c;
}

Camera* InputManager::camera() {
    return m_camera;
}

bool InputManager::handleEvents() {
    // Events
    while (SDL_PollEvent(&m_event) != 0) {
        switch (m_event.type) {
            case SDL_EVENT_MOUSE_MOTION:
                camera()->mouseTurn(m_event.motion.xrel, m_event.motion.yrel);
                break;
            case SDL_EVENT_QUIT:
                std::cout << "Quit" << std::endl;
                return true;
        }
    }

    // Keys
    m_keys = SDL_GetKeyboardState(NULL);
    if (m_keys[SDL_SCANCODE_ESCAPE]) {
            std::cout << "Quit" << std::endl;
            return true;
    }
    if (m_keys[SDL_SCANCODE_W]) {
        camera()->moveForward();
    }
    if (m_keys[SDL_SCANCODE_S]) {
        camera()->moveBackward();
    }
    if (m_keys[SDL_SCANCODE_D]) {
        camera()->moveRight();
    }
    if (m_keys[SDL_SCANCODE_A]) {
        camera()->moveLeft();
    }
    if (m_keys[SDL_SCANCODE_SPACE]) {
        camera()->moveUp();
    }
    if (m_keys[SDL_SCANCODE_LSHIFT]) {
        camera()->moveDown();
    }
    return false;
}
