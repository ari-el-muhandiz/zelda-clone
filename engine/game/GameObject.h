#pragma once

#include "Transform.h"
#include "../graphics/Mesh.h"
#include "../graphics/Material.h"
#include "../graphics/Renderer.h"
#include <memory>

namespace Engine
{

    class GameObject
    {
    public:
        GameObject(const std::string& name = "GameObject");
        ~GameObject() = default;

        // Transform
        Transform& getTransform() { return transform; }
        const Transform& getTransform() const { return transform; }

        // Graphics
        void setMesh(Mesh* mesh) { this->mesh = mesh; }
        void setMaterial(Material* material) { this->material = material; }

        Mesh* getMesh() const { return mesh; }
        Material* getMaterial() const { return material; }

        // Rendering
        void render(Renderer* renderer);

        // GameObject info
        const std::string& getName() const { return name; }
        bool isActive() const { return active; }
        void setActive(bool state) { active = state; }

    private:
        std::string name;
        Transform transform;
        Mesh* mesh = nullptr;
        Material* material = nullptr;
        bool active = true;
    };

} // namespace Engine
