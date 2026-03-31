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

} // namespace Engine
