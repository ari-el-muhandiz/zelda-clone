#pragma once
#include <entt/entt.hpp>

namespace Engine
{
    class Renderer;
    
    void renderSystem(entt::registry& registry, Renderer* renderer);
}
