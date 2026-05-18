#pragma once

#include <entt/entity/entity.hpp>
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

    struct Camera2D { 
        float x = 0.0f; 
        float y = 0.0f; 
        float rotation = 0.0f; 
        float zoom = 1.0f; 
        float viewportWidth = 2.0f; 
        float viewportHeight = 2.0f; 
    };

    struct Camera3D { 
        float x = 0.0f; 
        float y = 0.0f; 
        float z = 3.0f;
        float yaw = -90.0f;
        float pitch = 0.0f;
        float fovDegrees = 60.0f;
        float nearPlane = 0.01f;
        float farPlane = 100.0f;
        float aspectRatio = 16.0f / 9.0f;
    };

    struct ActiveCamera {};

    struct FollowTarget { 
         entt::entity target = entt::null;
        float lerpSpeed = 5.0f;
    };
}
