#pragma once

#include <cstdint>

namespace Engine
{
    namespace Input
    {
        // Backend-agnostic key identifiers used by gameplay code.
        enum class KeyCode : uint8_t
        {
            Unknown = 0,
            Up,
            Down,
            Left,
            Right,
            Escape,
        };
    }
}
