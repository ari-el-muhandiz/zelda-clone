#pragma once

#include "GameObject.h"
#include "../input/InputManager.h"
#include "../window/Window.h"
#include <memory>
#include <vector>

namespace Engine
{

    class Game
    {
    public:
        Game(Renderer* renderer, Window* window, InputManager* inputManager);
        ~Game() = default;

        // Game lifecycle
        void update(float deltaTime);
        void render();

        // GameObject management
        GameObject* createGameObject(const std::string& name = "GameObject");
        void removeGameObject(GameObject* object);

        // Accessors
        Renderer* getRenderer() const { return renderer; }
        Window* getWindow() const { return window; }
        InputManager* getInputManager() const { return inputManager; }

        bool isRunning() const { return running; }
        void quit() { running = false; }

    private:
        void updateInput();
        void updateGameObjects(float deltaTime);
        void renderGameObjects();

        Renderer* renderer;
        Window* window;
        InputManager* inputManager;
        std::vector<std::unique_ptr<GameObject>> gameObjects;
        bool running = true;
    };

} // namespace Engine
