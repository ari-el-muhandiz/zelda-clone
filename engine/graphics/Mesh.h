#pragma once

#include <vector>
#include <cstdint>

namespace Engine
{

    struct VertexAttribute
    {
        uint32_t location;
        uint32_t componentCount; // 1, 2, 3, or 4
        uint32_t type;           // GL_FLOAT, etc.
        bool normalized;
        uint32_t stride;
        uint32_t offset;
    };

    class Mesh
    {
    private:
        std::vector<float> vertices;
        std::vector<uint32_t> indices;
        std::vector<VertexAttribute> attributes;
        uint32_t vertexCount;
        uint32_t indexCount;

        // GPU resource handles (managed by renderer)
        uint32_t vao = 0;
        uint32_t vbo = 0;
        uint32_t ebo = 0;
        bool uploaded = false;

    public:
        Mesh(const std::vector<float> &vertexData, const std::vector<VertexAttribute> &attribs);
        Mesh(const std::vector<float> &vertexData, const std::vector<uint32_t> &indexData,
             const std::vector<VertexAttribute> &attribs);
        ~Mesh();

        // Accessors
        const std::vector<float> &getVertices() const { return vertices; }
        const std::vector<uint32_t> &getIndices() const { return indices; }
        const std::vector<VertexAttribute> &getAttributes() const { return attributes; }
        uint32_t getVertexCount() const { return vertexCount; }
        uint32_t getIndexCount() const { return indexCount; }
        bool hasIndices() const { return !indices.empty(); }

        // GPU resource management (accessed by renderer)
        uint32_t getVAO() const { return vao; }
        uint32_t getVBO() const { return vbo; }
        uint32_t getEBO() const { return ebo; }
        bool isUploaded() const { return uploaded; }

        void setVAO(uint32_t handle) { vao = handle; }
        void setVBO(uint32_t handle) { vbo = handle; }
        void setEBO(uint32_t handle) { ebo = handle; }
        void setUploaded(bool state) { uploaded = state; }

        // Helper function to create simple 2D mesh
        static Mesh *createSimple2D(const std::vector<float> &positions);
        static Mesh *createQuad2D();
        
    };

} // namespace Engine
