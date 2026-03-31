#pragma once

namespace Engine
{

    class Window
    {
    public:
        virtual ~Window() = default;

        // Window lifecycle
        virtual bool isOpen() const = 0;
        virtual void close() = 0;
        virtual void update() = 0;
        virtual void swapBuffers() = 0;

        // Dimensions
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        // Platform-specific (for graphics context creation)
        virtual void* getNativeWindow() const = 0;
    };

} // namespace Engine
