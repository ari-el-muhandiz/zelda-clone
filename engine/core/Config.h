#pragma once

namespace Engine
{

    // Game Configuration Constants
    namespace Config
    {
        // Window
        constexpr int SCREEN_WIDTH = 640;
        constexpr int SCREEN_HEIGHT = 480;
        constexpr const char* WINDOW_TITLE = "Zelda 2D Engine";

        // OpenGL
        constexpr int GL_MAJOR_VERSION = 3;
        constexpr int GL_MINOR_VERSION = 3;

        // Rendering
        namespace Graphics
        {
            constexpr float CLEAR_COLOR_R = 0.1f;
            constexpr float CLEAR_COLOR_G = 0.1f;
            constexpr float CLEAR_COLOR_B = 0.2f;
            constexpr float CLEAR_COLOR_A = 1.0f;
        }

        // Game
        namespace Game
        {
            constexpr float HERO_SPEED = 0.5f;  // Units per second
            constexpr float HERO_SCALE = 0.2f;
        }

        // Paths
        namespace Paths
        {
            constexpr const char* SHADER_VERTEX = "engine/shaders/vertex.glsl";
            constexpr const char* SHADER_FRAGMENT = "engine/shaders/fragment.glsl";
            constexpr const char* SPRITE_SHADER_VERTEX = "engine/shaders/sprite_vertex.glsl";
            constexpr const char* SPRITE_SHADER_FRAGMENT = "engine/shaders/sprite_fragment.glsl";
        }
    }

} // namespace Engine
