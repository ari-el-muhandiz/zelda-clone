//
// Created by Ari Firmanto on 29/07/25.
//

#pragma once
#include <SDL.h>

class InputManager {
public:
    void update();
    [[nodiscard]] bool isQuit() const;
    [[nodiscard]] bool isKeyDown(SDL_Scancode key) const;
private:
    bool quit = false;
    const Uint8* keyboardState = nullptr;
};