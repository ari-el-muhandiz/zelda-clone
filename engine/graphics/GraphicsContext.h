#pragma once

#include <cstddef>
#include <cstdint>

namespace Engine
{

    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;

        // Shader operations
        virtual uint32_t createShader(uint32_t shaderType, const char *source) = 0;
        virtual void deleteShader(uint32_t shader) = 0;

        // Program operations
        virtual uint32_t createProgram() = 0;
        virtual void attachShader(uint32_t program, uint32_t shader) = 0;
        virtual void linkProgram(uint32_t program) = 0;
        virtual void useProgram(uint32_t program) = 0;
        virtual void deleteProgram(uint32_t program) = 0;

        // Buffer operations
        virtual void genVertexArrays(int n, uint32_t *arrays) = 0;
        virtual void genBuffers(int n, uint32_t *buffers) = 0;
        virtual void deleteVertexArrays(int n, const uint32_t *arrays) = 0;
        virtual void deleteBuffers(int n, const uint32_t *buffers) = 0;

        virtual void bindVertexArray(uint32_t array) = 0;
        virtual void bindBuffer(uint32_t target, uint32_t buffer) = 0;
        virtual void bufferData(uint32_t target, size_t size, const void *data, uint32_t usage) = 0;

        // Vertex attributes
        virtual void vertexAttribPointer(uint32_t index, int size, uint32_t type, bool normalized, int stride, const void *pointer) = 0;
        virtual void enableVertexAttribArray(uint32_t index) = 0;

        // Uniforms
        virtual int32_t getUniformLocation(uint32_t program, const char *name) = 0;
        virtual void uniform2f(int32_t location, float x, float y) = 0;
        virtual void uniform1f(int32_t location, float value) = 0;
        virtual void uniform1i(int32_t location, int value) = 0;

        // Rendering
        virtual void clearColor(float r, float g, float b, float a) = 0;
        virtual void clear(uint32_t mask) = 0;
        virtual void drawArrays(uint32_t mode, int first, int count) = 0;

        // Swap
        virtual void swapBuffers() = 0;

        // Texture operations
        virtual void genTextures(int n, uint32_t *textures) = 0;
        virtual void deleteTextures(int n, const uint32_t *textures) = 0;
        virtual void bindTexture(uint32_t target, uint32_t texture) = 0;
        virtual void activeTexture(uint32_t texture) = 0;
        virtual void texImage2D(uint32_t target, int level, int internalFormat, int width, int height, int border, uint32_t format, uint32_t type, const void *data) = 0;
        virtual void texParameteri(uint32_t target, uint32_t pname, int param) = 0;

        // Blending
        virtual void enable(uint32_t cap) = 0;
        virtual void disable(uint32_t cap) = 0;
        virtual void blendFunc(uint32_t sfactor, uint32_t dfactor) = 0;
    };

} // namespace Engine
