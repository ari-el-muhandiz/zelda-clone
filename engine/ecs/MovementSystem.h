#pragma once

#include <entt/entt.hpp>

class InputManager;

namespace Engine
{
    void movementSystem(entt::registry& registry, ::InputManager* input, float deltaTime);
}
