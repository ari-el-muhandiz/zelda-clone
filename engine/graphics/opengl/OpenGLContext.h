#pragma once

#include "../GraphicsContext.h"
#include <SDL.h>

namespace Engine
{
    namespace OpenGL
    {

        class OpenGLContext : public GraphicsContext
        {
        private:
            SDL_GLContext glContext = nullptr;
            SDL_Window* window = nullptr;

        public:
            OpenGLContext(SDL_GLContext context, SDL_Window* win);
            ~OpenGLContext() override;

            // Shader operations
            uint32_t createShader(uint32_t shaderType, const char *source) override;
            void deleteShader(uint32_t shader) override;

            // Program operations
            uint32_t createProgram() override;
            void attachShader(uint32_t program, uint32_t shader) override;
            void linkProgram(uint32_t program) override;
            void useProgram(uint32_t program) override;
            void deleteProgram(uint32_t program) override;

            // Buffer operations
            void genVertexArrays(int n, uint32_t *arrays) override;
            void genBuffers(int n, uint32_t *buffers) override;
            void deleteVertexArrays(int n, const uint32_t *arrays) override;
            void deleteBuffers(int n, const uint32_t *buffers) override;

            void bindVertexArray(uint32_t array) override;
            void bindBuffer(uint32_t target, uint32_t buffer) override;
            void bufferData(uint32_t target, size_t size, const void *data, uint32_t usage) override;

            // Vertex attributes
            void vertexAttribPointer(uint32_t index, int size, uint32_t type, bool normalized, int stride, const void *pointer) override;
            void enableVertexAttribArray(uint32_t index) override;

            // Uniforms
            int32_t getUniformLocation(uint32_t program, const char *name) override;
            void uniform2f(int32_t location, float x, float y) override;
            void uniform1f(int32_t location, float value) override;
            void uniform1i(int32_t location, int value) override;

            // Rendering
            void clearColor(float r, float g, float b, float a) override;
            void clear(uint32_t mask) override;
            void drawArrays(uint32_t mode, int first, int count) override;

            // Swap
            void swapBuffers() override;

            // Context management
            void makeCurrent();
            void setViewport(int x, int y, int width, int height);

            // Texture operations
            void genTextures(int n, uint32_t *textures) override;
            void deleteTextures(int n, const uint32_t *textures) override;
            void bindTexture(uint32_t target, uint32_t texture) override;
            void activeTexture(uint32_t texture) override;
            void texImage2D(uint32_t target, int level, int internalFormat, int width, int height, int border, uint32_t format, uint32_t type, const void *data) override;
            void texParameteri(uint32_t target, uint32_t pname, int param) override;

            // Blending
            void enable(uint32_t cap) override;
            void disable(uint32_t cap) override;
            void blendFunc(uint32_t sfactor, uint32_t dfactor) override;

        };

    } // namespace OpenGL
} // namespace Engine
