#include "OpenGLContext.h"
#include <glad/glad.h>

namespace Engine
{
    namespace OpenGL
    {

        OpenGLContext::OpenGLContext(SDL_GLContext context, SDL_Window* win)
            : glContext(context), window(win)
        {
        }

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

        void OpenGLContext::uniform1i(int32_t location, int value)
        {
            glUniform1i(location, value);
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
            glFinish();
            SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
        }

        void OpenGLContext::makeCurrent()
        {
            if (window && glContext)
            {
                SDL_GL_MakeCurrent(window, glContext);
            }
        }

        void OpenGLContext::setViewport(int x, int y, int width, int height)
        {
            glViewport(x, y, width, height);
        }

        void OpenGLContext::genTextures(int n, uint32_t *textures)
        {
            glGenTextures(n, textures);
        }

        void OpenGLContext::deleteTextures(int n, const uint32_t *textures)
        {
            glDeleteTextures(n, textures);
        }

        void OpenGLContext::bindTexture(uint32_t target, uint32_t texture)
        {
            glBindTexture(target, texture);
        }

        void OpenGLContext::activeTexture(uint32_t texture)
        {
            glActiveTexture(texture);
        }

        void OpenGLContext::texImage2D(uint32_t target, int level, int internalFormat, int width, int height, int border, uint32_t format, uint32_t type, const void *data)
        {
            glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
        }

        void OpenGLContext::texParameteri(uint32_t target, uint32_t pname, int param)
        {
            glTexParameteri(target, pname, param);
        }

        void OpenGLContext::enable(uint32_t cap)
        {
            glEnable(cap);
        }

        void OpenGLContext::disable(uint32_t cap)
        {
            glDisable(cap);
        }

        void OpenGLContext::blendFunc(uint32_t sfactor, uint32_t dfactor)
        {
            glBlendFunc(sfactor, dfactor);
        }

    } // namespace OpenGL
} // namespace Engine
