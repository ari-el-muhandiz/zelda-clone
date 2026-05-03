#pragma once

#include <entt/entity/fwd.hpp>
#include <string>
#include <vector>

#include "graphics/Material.h"
#include "graphics/Mesh.h"

namespace Engine
{
    struct Sprite 
    {
        Mesh* mesh = nullptr;
        Material* material = nullptr;
    };

    struct Name
    {
        std::string value;
    };

    struct PlayerInput
    {

    };

    struct Active {

    };

    struct LocalTransform
    {
        float x = 0.0f;
        float y = 0.0f;
        float rotation = 0.0f;
        float scaleX = 1.0f;
        float scaleY = 1.0f;

        // Utility methods
        void setPosition(float px, float py)
        {
            x = px;
            y = py;
        }

        void translate(float dx, float dy)
        {
            x += dx;
            y += dy;
        }

        void setScale(float sx, float sy)
        {
            scaleX = sx;
            scaleY = sy;
        }

        void setRotation(float angle)
        {
            rotation = angle;
        }
    };

    struct WorldTransform
    {
        float x = 0.0f;
        float y = 0.0f;
        float rotation = 0.0f;
        float scaleX = 1.0f;
        float scaleY = 1.0f;
        bool needsUpdate = true; // Flag to indicate if world transform needs recalculation

        // Utility methods
        void setPosition(float px, float py)
        {
            x = px;
            y = py;
        }

        void translate(float dx, float dy)
        {
            x += dx;
            y += dy;
        }

        void setScale(float sx, float sy)
        {
            scaleX = sx;
            scaleY = sy;
        }

        void setRotation(float angle)
        {
            rotation = angle;
        }
    };

    struct Parent { 
        entt::entity entity; 
    };

    struct Children { 
        std::vector<entt::entity> entities; 
    };
}
