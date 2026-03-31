#pragma once

#include "Window.h"
#include <SDL.h>

namespace Engine
{

    class SDLWindow : public Window
    {
    private:
        SDL_Window* window = nullptr;
        bool shouldClose = false;

    public:
        SDLWindow(int width, int height, const char* title);
        ~SDLWindow() override;

        bool isOpen() const override;
        void close() override;
        void update() override;
        void swapBuffers() override;

        int getWidth() const override;
        int getHeight() const override;

        void* getNativeWindow() const override { return window; }
        SDL_Window* getNativeSDLWindow() const { return window; }
    };

} // namespace Engine
