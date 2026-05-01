//
// Created by Ari Firmanto on 29/07/25.
//

#pragma once
#include "KeyCode.h"

class InputManager {
public:
    void update();
    [[nodiscard]] bool isQuit() const;
    [[nodiscard]] bool isKeyDown(Engine::Input::KeyCode key) const;
    [[nodiscard]] float getMoveX() const;
    [[nodiscard]] float getMoveY() const;
private:
    bool quit = false;
    const bool* keyboardState = nullptr;
};
