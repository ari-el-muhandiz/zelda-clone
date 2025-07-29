
#include <SDL.h>
#include <iostream>
#include "InputManager.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Zelda 2D Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Create Window Failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cerr << "Create Renderer Failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    InputManager inputManager;
    bool running = true;
    SDL_Event event;

    int heroX = SCREEN_WIDTH / 2 - 16;
    int heroY = SCREEN_HEIGHT / 2 - 16;

    while (running) {
        constexpr int heroSpeed = 4;
        inputManager.update();

        if (inputManager.isKeyDown(SDL_SCANCODE_ESCAPE) || inputManager.isQuit()) {
            running = false;
        }

        // Handle hero movement
        heroX += inputManager.getMoveX() * heroSpeed;
        heroY += inputManager.getMoveY() * heroSpeed;

        SDL_SetRenderDrawColor(renderer, 30, 30, 60, 255);
        SDL_RenderClear(renderer);

        // Render a placeholder "hero"
        SDL_Rect hero = { heroX, heroY, 32, 32 };
        SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
        SDL_RenderFillRect(renderer, &hero);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
