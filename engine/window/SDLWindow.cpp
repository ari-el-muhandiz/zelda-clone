#include "SDLWindow.h"
#include <iostream>

namespace Engine
{

    SDLWindow::SDLWindow(int width, int height, const char* title)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
            return;
        }

        // Set OpenGL attributes (context creation will happen in graphics engine)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Create window
        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if (!window)
        {
            std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        // Note: GL context is created by the graphics engine (OpenGLGraphicsEngine)
    }

    SDLWindow::~SDLWindow()
    {
        if (window)
        {
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
    }

    bool SDLWindow::isOpen() const
    {
        return window != nullptr && !shouldClose;
    }

    void SDLWindow::close()
    {
        shouldClose = true;
    }

    void SDLWindow::update()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    shouldClose = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        shouldClose = true;
                    }
                    break;
            }
        }
    }

    void SDLWindow::swapBuffers()
    {
        if (window)
        {
            SDL_GL_SwapWindow(window);
        }
    }

    int SDLWindow::getWidth() const
    {
        int w = 0;
        if (window)
        {
            SDL_GetWindowSize(window, &w, nullptr);
        }
        return w;
    }

    int SDLWindow::getHeight() const
    {
        int h = 0;
        if (window)
        {
            SDL_GetWindowSize(window, nullptr, &h);
        }
        return h;
    }

} // namespace Engine
