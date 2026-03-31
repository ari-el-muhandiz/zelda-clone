#include "GameObject.h"

namespace Engine
{

    GameObject::GameObject(const std::string& name)
        : name(name)
    {
    }

    void GameObject::render(Renderer* renderer)
    {
        if (!active || !mesh || !material || !renderer)
        {
            return;
        }

        // Apply transform offset to material
        material->setVec2("offset", transform.x, transform.y);

        // Draw mesh
        renderer->drawMesh(mesh, material);
    }

} // namespace Engine
