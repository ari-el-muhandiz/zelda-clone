#include "OpenGLContext.h"
#include <glad/glad.h>

namespace Engine
{
    namespace OpenGL
    {

        OpenGLContext::OpenGLContext(SDL_GLContext context) : glContext(context) {}

        OpenGLContext::~OpenGLContext()
        {
            if (glContext)
            {
                SDL_GL_DeleteContext(glContext);
            }
        }

        uint32_t OpenGLContext::createShader(uint32_t shaderType, const char *source)
        {
            GLuint shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &source, nullptr);
            glCompileShader(shader);
            return shader;
        }

        void OpenGLContext::deleteShader(uint32_t shader)
        {
            glDeleteShader(shader);
        }

        uint32_t OpenGLContext::createProgram()
        {
            return glCreateProgram();
        }

        void OpenGLContext::attachShader(uint32_t program, uint32_t shader)
        {
            glAttachShader(program, shader);
        }

        void OpenGLContext::linkProgram(uint32_t program)
        {
            glLinkProgram(program);
        }

        void OpenGLContext::useProgram(uint32_t program)
        {
            glUseProgram(program);
        }

        void OpenGLContext::deleteProgram(uint32_t program)
        {
            glDeleteProgram(program);
        }

        void OpenGLContext::genVertexArrays(int n, uint32_t *arrays)
        {
            glGenVertexArrays(n, arrays);
        }

        void OpenGLContext::genBuffers(int n, uint32_t *buffers)
        {
            glGenBuffers(n, buffers);
        }

        void OpenGLContext::deleteVertexArrays(int n, const uint32_t *arrays)
        {
            glDeleteVertexArrays(n, arrays);
        }

        void OpenGLContext::deleteBuffers(int n, const uint32_t *buffers)
        {
            glDeleteBuffers(n, buffers);
        }

        void OpenGLContext::bindVertexArray(uint32_t array)
        {
            glBindVertexArray(array);
        }

        void OpenGLContext::bindBuffer(uint32_t target, uint32_t buffer)
        {
            glBindBuffer(target, buffer);
        }

        void OpenGLContext::bufferData(uint32_t target, size_t size, const void *data, uint32_t usage)
        {
            glBufferData(target, size, data, usage);
        }

        void OpenGLContext::vertexAttribPointer(uint32_t index, int size, uint32_t type, bool normalized, int stride, const void *pointer)
        {
            glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        }

        void OpenGLContext::enableVertexAttribArray(uint32_t index)
        {
            glEnableVertexAttribArray(index);
        }

        int32_t OpenGLContext::getUniformLocation(uint32_t program, const char *name)
        {
            return glGetUniformLocation(program, name);
        }

        void OpenGLContext::uniform2f(int32_t location, float x, float y)
        {
            glUniform2f(location, x, y);
        }

        void OpenGLContext::uniform1f(int32_t location, float value)
        {
            glUniform1f(location, value);
        }

        void OpenGLContext::clearColor(float r, float g, float b, float a)
        {
            glClearColor(r, g, b, a);
        }

        void OpenGLContext::clear(uint32_t mask)
        {
            glClear(mask);
        }

        void OpenGLContext::drawArrays(uint32_t mode, int first, int count)
        {
            glDrawArrays(mode, first, count);
        }

        void OpenGLContext::swapBuffers()
        {
            SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
        }

    } // namespace OpenGL
} // namespace Engine
