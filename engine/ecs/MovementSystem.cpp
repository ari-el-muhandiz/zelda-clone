#include "MovementSystem.h"
#include "Components.h"
#include "input/InputManager.h"
#include "core/Config.h"

namespace Engine
{
    void movementSystem(entt::registry& registry, ::InputManager* input, float deltaTime)
    {
        if (!input)
        {
            return;
        }

        // Process player input and update positions
        registry.view<Active, Transform, PlayerInput>().each([input, deltaTime](Transform& transform)
        {
            auto moveX = input->getMoveX() * Config::Game::HERO_SPEED * deltaTime;
            auto moveY = input->getMoveY() * Config::Game::HERO_SPEED * deltaTime;

            transform.translate(moveX, moveY);
        });
    }
} // namespace Engine
