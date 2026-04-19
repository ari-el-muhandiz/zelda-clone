#pragma once

#include "../graphics/Renderer.h"
#include "../input/InputManager.h"
#include "../window/Window.h"
#include <entt/entt.hpp>

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

        // Accessors
        Renderer* getRenderer() const { return renderer; }
        Window* getWindow() const { return window; }
        InputManager* getInputManager() const { return inputManager; }

        bool isRunning() const { return running; }
        void quit() { running = false; }

        entt::registry& getRegistry() { return registry; }
        entt::entity createEntity(const std::string& name);

    private:
        void updateInput();
        void updateGameObjects(float deltaTime);
        void renderGameObjects();

        Renderer* renderer;
        Window* window;
        InputManager* inputManager;
        bool running = true;
        entt::registry registry;
    };

} // namespace Engine
