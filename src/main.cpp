
#include <SDL.h>
#include <iostream>
#include <memory>
#include "input/InputManager.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Material.h"
#include "graphics/opengl/OpenGLGraphicsEngine.h"
#include "graphics/opengl/OpenGLRenderer.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set OpenGL version (e.g., 3.3 Core)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create window with OpenGL flag
    SDL_Window *window = SDL_CreateWindow("Zelda 2D Engine",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr << "Create Window Failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create graphics engine
    auto graphicsEngine = std::make_unique<Engine::OpenGL::OpenGLGraphicsEngine>(window);
    auto graphicsContext = graphicsEngine->createContext();
    if (!graphicsContext)
    {
        std::cerr << "Failed to create graphics context\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Create renderer
    auto renderer = std::make_unique<Engine::OpenGL::OpenGLRenderer>(graphicsContext.get());

    // Load and compile shader
    auto shader = Engine::Shader::loadFromFiles(
        "engine/shaders/vertex.glsl",
        "engine/shaders/fragment.glsl");
    if (!shader)
    {
        std::cerr << "Failed to load shaders\n";
        return -1;
    }

    // Create material with the shader
    auto material = std::make_unique<Engine::Material>(shader.get());
    material->setFloat("scale", 0.2f);

    // Create triangle mesh
    std::vector<float> triangleVertices = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f};
    auto triangleMesh = std::unique_ptr<Engine::Mesh>(
        Engine::Mesh::createSimple2D(triangleVertices));

    InputManager inputManager;
    bool running = true;

    float heroX = 0.0f, heroY = 0.0f;

    while (running)
    {
        constexpr float heroSpeed = 0.01f;
        inputManager.update();

        if (inputManager.isKeyDown(SDL_SCANCODE_ESCAPE) || inputManager.isQuit())
        {
            running = false;
        }

        // Handle hero movement
        heroX += inputManager.getMoveX() * heroSpeed;
        heroY += inputManager.getMoveY() * heroSpeed;

        // Update material uniforms
        material->setVec2("offset", heroX, heroY);

        // Render
        renderer->beginFrame();
        renderer->clear(0.1f, 0.1f, 0.2f, 1.0f);
        renderer->drawMesh(triangleMesh.get(), material.get());
        renderer->endFrame();
    }

    // Cleanup
    renderer->deleteMesh(triangleMesh.get());
    renderer->deleteShader(shader.get());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
