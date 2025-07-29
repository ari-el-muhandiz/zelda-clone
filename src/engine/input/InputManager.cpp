//
// Created by Ari Firmanto on 29/07/25.
//

#include "InputManager.h"

void InputManager::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
    }

    keyboardState = SDL_GetKeyboardState(nullptr);
}

bool InputManager::isQuit() const {
    return quit;
}

bool InputManager::isKeyDown(const SDL_Scancode key) const {
    return keyboardState && keyboardState[key];
}