#pragma once

#include "../GraphicsEngine.h"
#include <SDL.h>

namespace Engine
{
    namespace OpenGL
    {

        class OpenGLGraphicsEngine : public GraphicsEngine
        {
        private:
            SDL_Window *window = nullptr;

        public:
            OpenGLGraphicsEngine(SDL_Window *window);
            ~OpenGLGraphicsEngine() override;

            std::unique_ptr<GraphicsContext> createContext() override;
        };

    } // namespace OpenGL
} // namespace Engine
