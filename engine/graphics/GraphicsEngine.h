#pragma once

#include "GraphicsContext.h"
#include <memory>

namespace Engine
{

    class GraphicsEngine
    {
    public:
        virtual ~GraphicsEngine() = default;

        virtual std::unique_ptr<GraphicsContext> createContext() = 0;
    };

} // namespace Engine
