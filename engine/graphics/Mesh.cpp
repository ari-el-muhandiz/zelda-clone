#include "Mesh.h"

namespace Engine
{

    Mesh::Mesh(const std::vector<float> &vertexData, const std::vector<VertexAttribute> &attribs)
        : vertices(vertexData), attributes(attribs), indexCount(0)
    {
        // Calculate vertex count based on first attribute stride
        if (!attribs.empty())
        {
            uint32_t vertexSize = attribs[0].stride;
            vertexCount = vertexData.size() / (vertexSize / sizeof(float));
        }
        else
        {
            vertexCount = 0;
        }
    }

    Mesh::Mesh(const std::vector<float> &vertexData, const std::vector<uint32_t> &indexData,
               const std::vector<VertexAttribute> &attribs)
        : vertices(vertexData), indices(indexData), attributes(attribs), indexCount(indexData.size())
    {
        // Calculate vertex count based on first attribute stride
        if (!attribs.empty())
        {
            uint32_t vertexSize = attribs[0].stride;
            vertexCount = vertexData.size() / (vertexSize / sizeof(float));
        }
        else
        {
            vertexCount = 0;
        }
    }

    Mesh::~Mesh()
    {
        // Resources are managed by renderer, so we don't delete them here
        // This prevents double-deletion if mesh is destroyed before renderer
    }

    Mesh *Mesh::createSimple2D(const std::vector<float> &positions)
    {
        // Simple 2D mesh with position attribute only
        VertexAttribute posAttr;
        posAttr.location = 0;
        posAttr.componentCount = 2;
        posAttr.type = 0x1406; // GL_FLOAT
        posAttr.normalized = false;
        posAttr.stride = 2 * sizeof(float);
        posAttr.offset = 0;

        return new Mesh(positions, {posAttr});
    }

    Mesh *Mesh::createQuad2D()
    {
        // Create a simple quad (two triangles) for 2D rendering
        std::vector<float> quadVertices = {
            -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
             0.5f, -0.5f, 1.0f, 0.0f, // Bottom-right
             0.5f,  0.5f, 1.0f, 1.0f, // Top-right
            -0.5f,  0.5f, 0.0f, 1.0f  // Top-left
        };

        std::vector<uint32_t> quadIndices = {
            0, 1, 2, // First triangle
            2, 3, 0  // Second triangle
        };

        VertexAttribute posAttr;
        posAttr.location = 0;
        posAttr.componentCount = 2;
        posAttr.type = 0x1406; // GL_FLOAT
        posAttr.normalized = false;
        posAttr.stride = 4 * sizeof(float);
        posAttr.offset = 0; // Position starts at the beginning

        VertexAttribute texAttr;
        texAttr.location = 1;
        texAttr.componentCount = 2;
        texAttr.type = 0x1406; // GL_FLOAT
        texAttr.normalized = false;
        texAttr.stride = 4 * sizeof(float);
        texAttr.offset = 2 * sizeof(float); // Texture coordinates start after position

        return new Mesh(quadVertices, quadIndices, {posAttr, texAttr});
    }

} // namespace Engine
