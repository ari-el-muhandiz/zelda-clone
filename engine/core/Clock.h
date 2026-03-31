#pragma once

#include <chrono>

namespace Engine
{

    class Clock
    {
    private:
        std::chrono::high_resolution_clock::time_point lastTime;
        float deltaTime = 0.0f;
        bool isFirstTick = true;

    public:
        Clock();

        // Call this once per frame
        void tick();

        // Get time elapsed since last tick (in seconds)
        float getDeltaTime() const { return deltaTime; }

        // Get total elapsed time since clock creation (in seconds)
        float getElapsedTime() const;
    };

} // namespace Engine
