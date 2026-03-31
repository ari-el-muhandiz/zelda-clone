#include "Game.h"
#include "../core/Config.h"
#include <algorithm>

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

    GameObject* Game::createGameObject(const std::string& name)
    {
        auto gameObject = std::make_unique<GameObject>(name);
        GameObject* ptr = gameObject.get();
        gameObjects.push_back(std::move(gameObject));
        return ptr;
    }

    void Game::removeGameObject(GameObject* object)
    {
        auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
                               [object](const std::unique_ptr<GameObject>& go) {
                                   return go.get() == object;
                               });
        if (it != gameObjects.end())
        {
            gameObjects.erase(it);
        }
    }

    void Game::updateInput()
    {
        inputManager->update();
        window->update();

        if (inputManager->isKeyDown(SDL_SCANCODE_ESCAPE))
        {
            running = false;
        }
    }

    void Game::updateGameObjects(float deltaTime)
    {
        for (auto& gameObject : gameObjects)
        {
            if (!gameObject->isActive())
            {
                continue;
            }

            // Simple movement for player (demo)
            // In a real game, this would come from a component system
            Transform& transform = gameObject->getTransform();
            float moveX = inputManager->getMoveX() * Config::Game::HERO_SPEED * deltaTime;
            float moveY = inputManager->getMoveY() * Config::Game::HERO_SPEED * deltaTime;
            transform.translate(moveX, moveY);
        }
    }

    void Game::renderGameObjects()
    {
        for (auto& gameObject : gameObjects)
        {
            if (gameObject->isActive())
            {
                gameObject->render(renderer);
            }
        }
    }

} // namespace Engine
