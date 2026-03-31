#pragma once

namespace Engine
{

    struct Transform
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

} // namespace Engine
