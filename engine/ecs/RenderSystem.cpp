#include "RenderSystem.h"
#include "Components.h"
#include "../graphics/Renderer.h"

namespace Engine
{
    void renderSystem(entt::registry& registry, Renderer* renderer)
    {
        registry.view<Active, LocalTransform, Sprite>().each([renderer](const LocalTransform& transform, const Sprite& sprite)
        {
            if (!sprite.mesh || !sprite.material || !renderer)
            {
                return; // Skip rendering if mesh or material is missing
            }

            sprite.material->setVec2("offset", transform.x, transform.y);
            renderer->drawMesh(sprite.mesh, sprite.material);
        });
    }
} // namespace Engine
