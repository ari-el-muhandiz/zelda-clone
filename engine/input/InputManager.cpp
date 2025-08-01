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

float InputManager::getMoveX() const {
    int moveX = 0.0f;
    if (isKeyDown(SDL_SCANCODE_LEFT)) { moveX = -1.0f; }
    if (isKeyDown(SDL_SCANCODE_RIGHT)) { moveX += 1.0f; }
    return moveX;
}

float InputManager::getMoveY() const {
    int moveY = 0.0f;
    if (isKeyDown(SDL_SCANCODE_UP)) { moveY += 1.0f; }
    if (isKeyDown(SDL_SCANCODE_DOWN)) { moveY -= 1.0f; }
    return moveY;
}