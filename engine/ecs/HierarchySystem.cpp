#include "HierarchySystem.h"
#include "Components.h"

#include <cmath>
#include <unordered_set>

namespace Engine
{
    namespace {
        [[maybe_unused]]
        WorldTransform composeTransforms(const WorldTransform& parent, const LocalTransform& local) {
            WorldTransform world{};

            const float c = std::cos(parent.rotation);
            const float s = std::sin(parent.rotation);

            world.x = parent.x + local.x * c * parent.scaleX - local.y * s * parent.scaleY;
            world.y = parent.y + local.x * s * parent.scaleX + local.y * c * parent.scaleY;
            world.rotation = parent.rotation + local.rotation;
            world.scaleX = parent.scaleX * local.scaleX;
            world.scaleY = parent.scaleY * local.scaleY;
            world.needsUpdate = false; // Mark as updated

            return world;
        }

        [[maybe_unused]]
        void updateChildrenRecursive(
            entt::registry& registry, 
            entt::entity parentEntity, 
            const WorldTransform& parentWorld,
            std::unordered_set<entt::entity>& recursionStack) {
            auto childrenView = registry.view<Parent, LocalTransform, WorldTransform>();
            childrenView.each([&](auto childEntity, auto& parent, auto& local, auto& world) {
                if (parent.entity != parentEntity) {
                    return; // Not a child of the current parent, skip
                }

                if (recursionStack.count(childEntity) > 0) {
                    // Detected a cycle in the hierarchy, skip to prevent infinite recursion
                    return;
                }
                // Update world transform based on parent's world transform and local transform
                world = composeTransforms(parentWorld, local);

                // Add child to recursion stack before processing its children
                recursionStack.insert(childEntity);
                // Recursively update this child's children
                updateChildrenRecursive(registry, childEntity, world, recursionStack);
                // Remove child from recursion stack after processing its children
                recursionStack.erase(childEntity);
            });
        }
    }
    void hierarchySystem(entt::registry& registry)
    {
         auto rootView = registry.view<LocalTransform, WorldTransform>(entt::exclude<Parent>);
         rootView.each([&](auto rootEntity, auto& local, auto& world) {
             // For root entities, world transform is the same as local transform
             world.setPosition(local.x, local.y);
             world.setRotation(local.rotation);
             world.setScale(local.scaleX, local.scaleY);
             world.needsUpdate = false;

            // Recursively update children
            std::unordered_set<entt::entity> recursionStack;
            recursionStack.insert(rootEntity);
            updateChildrenRecursive(registry, rootEntity, world, recursionStack);
         });

    }
} // namespace Engine
