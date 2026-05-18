#pragma once

#include "../Renderer.h"

namespace Engine
{
    namespace OpenGL
    {

        class OpenGLRenderer : public Renderer
        {
        public:
            OpenGLRenderer(GraphicsContext *ctx);
            ~OpenGLRenderer() override;

            // High-level drawing operations
            void clear(float r, float g, float b, float a) override;
            void drawMesh(Mesh *mesh, Material *material) override;

            // Shader management
            bool compileShader(Shader *shader) override;
            void deleteShader(Shader *shader) override;

            // Mesh management
            void uploadMesh(Mesh *mesh) override;
            void deleteMesh(Mesh *mesh) override;

            // Frame operations
            void beginFrame() override;
            void endFrame() override;
            void setViewProjection(const float* mat4x4ColMajor) override;
            void resetViewProjection() override;

            // Texture management
            void uploadTexture(Texture *texture) override;
            void deleteTexture(Texture *texture) override;

        private:
            // Internal state for view-projection matrix
            float storedViewProjection[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
        };

    } // namespace OpenGL
} // namespace Engine
