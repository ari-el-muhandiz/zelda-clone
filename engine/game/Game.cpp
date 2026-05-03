#include "Game.h"
#include <algorithm>
#include <cmath>

#include "../core/Config.h"
#include "../ecs/Components.h"
#include "../ecs/MovementSystem.h"
#include "../ecs/RenderSystem.h"
#include "ecs/HierarchySystem.h"

namespace Engine
{

    Game::Game(Renderer* renderer, Window* window, InputManager* inputManager)
        : renderer(renderer), window(window), inputManager(inputManager)
    {
    }

    void Game::update(float deltaTime)
    {
        if (!running || !window->isOpen())
        {
            running = false;
            return;
        }

        updateInput();
        updateGameObjects(deltaTime);
    }

    void Game::render()
    {
        if (!renderer)
        {
            return;
        }

        renderer->beginFrame();
        renderer->clear(
            Config::Graphics::CLEAR_COLOR_R,
            Config::Graphics::CLEAR_COLOR_G,
            Config::Graphics::CLEAR_COLOR_B,
            Config::Graphics::CLEAR_COLOR_A);

        renderGameObjects();

        renderer->endFrame();
    }


    void Game::updateInput()
    {
        inputManager->update();
        window->update();

        if (inputManager->isKeyDown(Engine::Input::KeyCode::Escape))
        {
            running = false;
        }
    }

    void Game::updateGameObjects(float deltaTime)
    {
        movementSystem(registry, inputManager, deltaTime);
        hierarchySystem(registry);
    }

    void Game::renderGameObjects()
    {
        renderSystem(registry, renderer);
    }

    void Game::attachChild(entt::entity parent, entt::entity child)
    {
        if (!registry.valid(parent) || !registry.valid(child)) {
            return;
        }

        if (child == parent) {
            return; // Prevent attaching an entity to itself
        }

        // Prevent indirect cycles by walking the ancestor chain of the parent.
        for (entt::entity current = parent; current != entt::null; ) {
            if (current == child) {
                return;
            }

            auto *ancestor = registry.try_get<Parent>(current);
            current = ancestor ? ancestor->entity : entt::null;
        }

        auto* parentEntity = registry.try_get<Parent>(child);
        if (parentEntity && parentEntity->entity != entt::null) {
            detachChild(child);
        }

        registry.emplace_or_replace<Parent>(child, Parent{parent});

        // if parent has children, append child to vector; else emplace Children{std::vector{child}}.
        auto* children = registry.try_get<Children>(parent);
        if (children) {
            if (std::find(children->entities.begin(), children->entities.end(), child) == children->entities.end()) {
                children->entities.push_back(child);
            }
        } else {
            registry.emplace<Children>(parent, Children{std::vector<entt::entity>{child}});
        }

        // Convert child's LocalTransform to be relative to parent
        auto& parentWorld = registry.get<WorldTransform>(parent);
        auto& childWorld = registry.get<WorldTransform>(child);
        auto& childLocal = registry.get<LocalTransform>(child);

        // compute localChild = inverse(parentWorld) * childWorld. This preserves child's world position after attachment.
        const float c = std::cos(-parentWorld.rotation);
        const float s = std::sin(-parentWorld.rotation);
        const float invScaleX = 1.0f / parentWorld.scaleX;
        const float invScaleY = 1.0f / parentWorld.scaleY;
        const float dx = childWorld.x - parentWorld.x;
        const float dy = childWorld.y - parentWorld.y;
        childLocal.x = (dx * c - dy * s) * invScaleX;
        childLocal.y = (dx * s + dy * c) * invScaleY;
        childLocal.rotation = childWorld.rotation - parentWorld.rotation;
        childLocal.scaleX = childWorld.scaleX * invScaleX;
        childLocal.scaleY = childWorld.scaleY * invScaleY;
    }

    void Game::detachChild(entt::entity child)
    {
        auto* parentEntity = registry.try_get<Parent>(child);
        if (!parentEntity || parentEntity->entity == entt::null) {
            return; // Child has no parent, nothing to detach
        }

        entt::entity parent = parentEntity->entity;
        const WorldTransform preservedWorld = registry.get<WorldTransform>(child);

        registry.remove<Parent>(child);

        auto* children = registry.try_get<Children>(parent);
        if (children) {
            auto& entities = children->entities;
            entities.erase(std::remove(entities.begin(), entities.end(), child), entities.end());
            if (entities.empty()) {
                registry.remove<Children>(parent);
            }
        }

        // After detaching, the entity becomes a root, so its local transform
        // must match its current world transform to preserve its position.
        auto& childLocal = registry.get<LocalTransform>(child);
        auto& childWorld = registry.get<WorldTransform>(child);

        childLocal.x = preservedWorld.x;
        childLocal.y = preservedWorld.y;
        childLocal.rotation = preservedWorld.rotation;
        childLocal.scaleX = preservedWorld.scaleX;
        childLocal.scaleY = preservedWorld.scaleY;

        childWorld = preservedWorld;
        childWorld.needsUpdate = true;
    }

    entt::entity Game::createEntity(const std::string& name)
    {
        entt::entity entity = registry.create();
        registry.emplace<Name>(entity, Name{name});
        registry.emplace<LocalTransform>(entity);
        registry.emplace<WorldTransform>(entity);
        registry.emplace<Active>(entity);
        return entity;
    }

} // namespace Engine
