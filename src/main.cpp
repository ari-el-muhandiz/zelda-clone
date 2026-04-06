
#include <iostream>
#include <memory>
#include "input/InputManager.h"
#include "window/SDLWindow.h"
#include "core/Clock.h"
#include "core/Config.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Material.h"
#include "graphics/SpriteSheet.h"
#include "graphics/opengl/OpenGLGraphicsEngine.h"
#include "graphics/opengl/OpenGLRenderer.h"
#include "game/Game.h"
#include "game/GameObject.h"

int main(int argc, char *argv[])
{
    // Create window
    auto window = std::make_unique<Engine::SDLWindow>(
        Engine::Config::SCREEN_WIDTH,
        Engine::Config::SCREEN_HEIGHT,
        Engine::Config::WINDOW_TITLE);

    if (!window->isOpen())
    {
        std::cerr << "Failed to create window\n";
        return 1;
    }

    // Create graphics context
    auto graphicsEngine = std::make_unique<Engine::OpenGL::OpenGLGraphicsEngine>(
        window->getNativeSDLWindow());
    auto graphicsContext = graphicsEngine->createContext();
    if (!graphicsContext)
    {
        std::cerr << "Failed to create graphics context\n";
        return 1;
    }

    // Create renderer
    auto renderer = std::make_unique<Engine::OpenGL::OpenGLRenderer>(graphicsContext.get());

    auto shader = Engine::Shader::loadFromFiles(
        Engine::Config::Paths::SPRITE_SHADER_VERTEX,
         Engine::Config::Paths::SPRITE_SHADER_FRAGMENT);
    if (!shader)
    {
        std::cerr << "Failed to load sprite shaders\n";
        return 1;
    }
    auto texture = Engine::Texture::loadFromFile("assets/sprites/player.png");

    if (!texture)
    {
        std::cerr << "Failed to load texture\n";
        return 1;
    }

    auto spriteSheet = std::make_unique<Engine::SpriteSheet>(texture.get(), 16, 9, 16, 16);
    auto material = std::make_unique<Engine::Material>(shader.get());
    material->setFloat("scale", Engine::Config::Game::HERO_SCALE);
    material->setTexture(texture.get());
    if (!spriteSheet->applyFrame(0, 0, material.get()))
    {
        std::cerr << "Failed to apply sprite sheet frame (0,0), falling back to full texture UVs\n";
        material->setVec2("uvOffset", 0.0f, 0.0f);
        material->setVec2("uvScale", 1.0f, 1.0f);
    }

    auto quadMesh = std::unique_ptr<Engine::Mesh>(
        Engine::Mesh::createQuad2D());

    // Initialize game systems
    InputManager inputManager;
    Engine::Game game(renderer.get(), window.get(), &inputManager);

    // Create player GameObject
    Engine::GameObject* player = game.createGameObject("Player");
    player->setMesh(quadMesh.get());
    player->setMaterial(material.get());

    // Game loop
    Engine::Clock clock;
    while (game.isRunning())
    {
        clock.tick();
        float deltaTime = clock.getDeltaTime();

        // Update and render
        game.update(deltaTime);
        game.render();
    }

    // Cleanup is automatic with unique_ptr destructors
    return 0;
}
