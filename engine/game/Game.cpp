#include "Game.h"
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
