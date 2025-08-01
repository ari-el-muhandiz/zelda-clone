
#include <SDL.h>
#include <iostream>
#include "InputManager.h"
#include <glad/glad.h> // Download glad and include its loader

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

// Vertex and fragment shader source
auto vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
uniform vec2 offset;
uniform float scale;
void main() {
    gl_Position = vec4((aPos * scale) + offset, 0.0, 1.0);
}
)";

auto fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(0.2, 0.7, 0.3, 1.0);
}
)";

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set OpenGL version (e.g., 3.3 Core)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create window with OpenGL flag
    SDL_Window* window = SDL_CreateWindow("Zelda 2D Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Create Window Failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create OpenGL context
    const SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // (Optional) Enable VSync
    SDL_GL_SetSwapInterval(1);

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Compile vertex shader
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Compile fragment shader
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Link shaders into a program
    const GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Triangle vertices
    constexpr float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    InputManager inputManager;
    bool running = true;

    float heroX = 0.0f, heroY = 0.0f;

    while (running) {
        constexpr float heroSpeed = 0.01f;
        inputManager.update();

        if (inputManager.isKeyDown(SDL_SCANCODE_ESCAPE) || inputManager.isQuit()) {
            running = false;
        }

        // Handle hero movement
        heroX += inputManager.getMoveX() * heroSpeed;
        heroY += inputManager.getMoveY() * heroSpeed;

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Set offset uniform
        const GLint offsetLoc = glGetUniformLocation(shaderProgram, "offset");
        glUniform2f(offsetLoc, heroX, heroY);

        const GLint scaleLoc = glGetUniformLocation(shaderProgram, "scale");
        glUniform1f(scaleLoc, 0.2f); // 0.5f downsizes the triangle to half

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    SDL_GL_DeleteContext(glContext);
    // SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
