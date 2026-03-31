#pragma once

#include "GraphicsContext.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

namespace Engine
{

    class Renderer
    {
    protected:
        GraphicsContext *context;

    public:
        Renderer(GraphicsContext *ctx);
        virtual ~Renderer();

        // High-level drawing operations
        virtual void clear(float r, float g, float b, float a) = 0;
        virtual void drawMesh(Mesh *mesh, Material *material) = 0;

        // Shader management
        virtual bool compileShader(Shader *shader) = 0;
        virtual void deleteShader(Shader *shader) = 0;

        // Mesh management
        virtual void uploadMesh(Mesh *mesh) = 0;
        virtual void deleteMesh(Mesh *mesh) = 0;

        // Frame operations
        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;

        GraphicsContext *getContext() { return context; }
    };

} // namespace Engine
