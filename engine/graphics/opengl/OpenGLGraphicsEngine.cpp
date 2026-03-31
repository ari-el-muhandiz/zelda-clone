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

            // Make context current before GLAD initialization
            SDL_GL_MakeCurrent(window, glContext);

            // Enable VSync
            SDL_GL_SetSwapInterval(1);

            // Initialize GLAD
            if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
            {
                std::cerr << "Failed to initialize GLAD" << std::endl;
                SDL_GL_DeleteContext(glContext);
                return nullptr;
            }

            auto context = std::make_unique<OpenGLContext>(glContext, window);
            
            // Set initial viewport
            int w, h;
            SDL_GetWindowSize(window, &w, &h);
            context->setViewport(0, 0, w, h);

            return context;
        }

    } // namespace OpenGL
} // namespace Engine
