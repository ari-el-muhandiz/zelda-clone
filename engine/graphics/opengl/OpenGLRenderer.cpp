#include "OpenGLRenderer.h"
#include "OpenGLContext.h"
#include <SDL.h>

// OpenGL constants
constexpr int GL_VERTEX_SHADER = 0x8B31;
constexpr int GL_FRAGMENT_SHADER = 0x8B30;
constexpr int GL_TRIANGLES = 0x0004;
constexpr int GL_COLOR_BUFFER_BIT = 0x00004000;
constexpr int GL_ARRAY_BUFFER = 0x8892;
constexpr int GL_ELEMENT_ARRAY_BUFFER = 0x8893;
constexpr int GL_STATIC_DRAW = 0x88E4;

namespace Engine
{
    namespace OpenGL
    {

        OpenGLRenderer::OpenGLRenderer(GraphicsContext *ctx) : Renderer(ctx)
        {
        }

        OpenGLRenderer::~OpenGLRenderer()
        {
        }

        void OpenGLRenderer::clear(float r, float g, float b, float a)
        {
            // Ensure context is current
            OpenGLContext* glContext = dynamic_cast<OpenGLContext*>(context);
            if (glContext)
            {
                glContext->makeCurrent();
            }
            
            context->clearColor(r, g, b, a);
            context->clear(GL_COLOR_BUFFER_BIT);
        }

        bool OpenGLRenderer::compileShader(Shader *shader)
        {
            if (shader->isCompiled())
            {
                return true;
            }

            // Compile vertex shader
            uint32_t vertexShader = context->createShader(GL_VERTEX_SHADER, shader->getVertexSource().c_str());

            // Compile fragment shader
            uint32_t fragmentShader = context->createShader(GL_FRAGMENT_SHADER, shader->getFragmentSource().c_str());

            // Link shaders into a program
            uint32_t shaderProgram = context->createProgram();
            context->attachShader(shaderProgram, vertexShader);
            context->attachShader(shaderProgram, fragmentShader);
            context->linkProgram(shaderProgram);

            context->deleteShader(vertexShader);
            context->deleteShader(fragmentShader);

            shader->setProgram(shaderProgram);
            shader->setCompiled(true);

            return true;
        }

        void OpenGLRenderer::deleteShader(Shader *shader)
        {
            if (shader->isCompiled())
            {
                context->deleteProgram(shader->getProgram());
                shader->setCompiled(false);
            }
        }

        void OpenGLRenderer::uploadMesh(Mesh *mesh)
        {
            if (mesh->isUploaded())
            {
                return;
            }

            uint32_t VAO, VBO, EBO = 0;
            context->genVertexArrays(1, &VAO);
            context->genBuffers(1, &VBO);

            context->bindVertexArray(VAO);
            context->bindBuffer(GL_ARRAY_BUFFER, VBO);
            context->bufferData(GL_ARRAY_BUFFER,
                                mesh->getVertices().size() * sizeof(float),
                                mesh->getVertices().data(),
                                GL_STATIC_DRAW);

            // Set up vertex attributes
            for (const auto &attr : mesh->getAttributes())
            {
                context->vertexAttribPointer(attr.location, attr.componentCount, attr.type,
                                             attr.normalized, attr.stride, (void *)(size_t)attr.offset);
                context->enableVertexAttribArray(attr.location);
            }

            // Handle indices if present
            if (mesh->hasIndices())
            {
                context->genBuffers(1, &EBO);
                context->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                context->bufferData(GL_ELEMENT_ARRAY_BUFFER,
                                    mesh->getIndices().size() * sizeof(uint32_t),
                                    mesh->getIndices().data(),
                                    GL_STATIC_DRAW);
                mesh->setEBO(EBO);
            }

            mesh->setVAO(VAO);
            mesh->setVBO(VBO);
            mesh->setUploaded(true);
        }

        void OpenGLRenderer::deleteMesh(Mesh *mesh)
        {
            if (mesh->isUploaded())
            {
                uint32_t vao = mesh->getVAO();
                uint32_t vbo = mesh->getVBO();
                context->deleteVertexArrays(1, &vao);
                context->deleteBuffers(1, &vbo);

                if (mesh->hasIndices())
                {
                    uint32_t ebo = mesh->getEBO();
                    context->deleteBuffers(1, &ebo);
                }

                mesh->setUploaded(false);
            }
        }

        void OpenGLRenderer::drawMesh(Mesh *mesh, Material *material)
        {
            // Ensure mesh is uploaded
            if (!mesh->isUploaded())
            {
                uploadMesh(mesh);
            }

            // Ensure shader is compiled
            Shader *shader = material->getShader();
            if (!shader->isCompiled())
            {
                compileShader(shader);
            }

            // Use shader program
            context->useProgram(shader->getProgram());

            // Set material uniforms
            for (const auto &[name, value] : material->getFloatUniforms())
            {
                int32_t location = context->getUniformLocation(shader->getProgram(), name.c_str());
                if (location >= 0)
                {
                    context->uniform1f(location, value);
                }
            }

            for (const auto &[name, value] : material->getVec2Uniforms())
            {
                int32_t location = context->getUniformLocation(shader->getProgram(), name.c_str());
                if (location >= 0)
                {
                    context->uniform2f(location, value.first, value.second);
                }
            }

            // Draw mesh
            context->bindVertexArray(mesh->getVAO());
            context->drawArrays(GL_TRIANGLES, 0, mesh->getVertexCount());
        }

        void OpenGLRenderer::beginFrame()
        {
            // Make the OpenGL context current before rendering
            if (context)
            {
                OpenGLContext* glContext = dynamic_cast<OpenGLContext*>(context);
                if (glContext)
                {
                    glContext->makeCurrent();
                }
            }
        }

        void OpenGLRenderer::endFrame()
        {
            context->swapBuffers();
        }

    } // namespace OpenGL
} // namespace Engine
