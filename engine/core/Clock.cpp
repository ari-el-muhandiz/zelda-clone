#include "Clock.h"

namespace Engine
{

    Clock::Clock()
        : lastTime(std::chrono::high_resolution_clock::now())
    {
    }

    void Clock::tick()
    {
        auto now = std::chrono::high_resolution_clock::now();
        
        if (isFirstTick)
        {
            deltaTime = 0.0f;
            isFirstTick = false;
        }
        else
        {
            std::chrono::duration<float> elapsed = now - lastTime;
            deltaTime = elapsed.count();
        }
        
        lastTime = now;
    }

    float Clock::getElapsedTime() const
    {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = now - lastTime;
        return elapsed.count();
    }

} // namespace Engine
