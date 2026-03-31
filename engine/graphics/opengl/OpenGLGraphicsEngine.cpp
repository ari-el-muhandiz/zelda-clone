#include "OpenGLGraphicsEngine.h"
#include "OpenGLContext.h"
#include <glad/glad.h>
#include <iostream>

namespace Engine
{
    namespace OpenGL
    {

        OpenGLGraphicsEngine::OpenGLGraphicsEngine(SDL_Window *window) : window(window) {}

        OpenGLGraphicsEngine::~OpenGLGraphicsEngine() = default;

        std::unique_ptr<GraphicsContext> OpenGLGraphicsEngine::createContext()
        {
            SDL_GLContext glContext = SDL_GL_CreateContext(window);
            if (!glContext)
            {
                std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
                return nullptr;
            }

            // Enable VSync
            SDL_GL_SetSwapInterval(1);

            // Initialize GLAD
            if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
            {
                std::cerr << "Failed to initialize GLAD" << std::endl;
                SDL_GL_DeleteContext(glContext);
                return nullptr;
            }

            return std::make_unique<OpenGLContext>(glContext);
        }

    } // namespace OpenGL
} // namespace Engine
