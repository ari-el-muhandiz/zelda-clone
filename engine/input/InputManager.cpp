//
// Created by Ari Firmanto on 29/07/25.
//

#include "InputManager.h"
#include <SDL3/SDL.h>

namespace
{
    SDL_Scancode toSDLScancode(Engine::Input::KeyCode key)
    {
        using Engine::Input::KeyCode;

        switch (key)
        {
            case KeyCode::Up:
                return SDL_SCANCODE_UP;
            case KeyCode::Down:
                return SDL_SCANCODE_DOWN;
            case KeyCode::Left:
                return SDL_SCANCODE_LEFT;
            case KeyCode::Right:
                return SDL_SCANCODE_RIGHT;
            case KeyCode::Escape:
                return SDL_SCANCODE_ESCAPE;
            case KeyCode::Unknown:
            default:
                return SDL_SCANCODE_UNKNOWN;
        }
    }
}

void InputManager::update() {
    // Note: SDL events are handled by Window::update()
    // InputManager only queries keyboard state, it doesn't consume events
    keyboardState = SDL_GetKeyboardState(nullptr);
}

bool InputManager::isQuit() const {
    return quit;
}

bool InputManager::isKeyDown(const Engine::Input::KeyCode key) const {
    if (!keyboardState)
    {
        return false;
    }

    const SDL_Scancode sdlKey = toSDLScancode(key);
    if (sdlKey == SDL_SCANCODE_UNKNOWN)
    {
        return false;
    }

    return keyboardState[sdlKey];
}

float InputManager::getMoveX() const {
    int moveX = 0.0f;
    if (isKeyDown(Engine::Input::KeyCode::Left)) { moveX = -1.0f; }
    if (isKeyDown(Engine::Input::KeyCode::Right)) { moveX += 1.0f; }
    return moveX;
}

float InputManager::getMoveY() const {
    int moveY = 0.0f;
    if (isKeyDown(Engine::Input::KeyCode::Up)) { moveY += 1.0f; }
    if (isKeyDown(Engine::Input::KeyCode::Down)) { moveY -= 1.0f; }
    return moveY;
}
