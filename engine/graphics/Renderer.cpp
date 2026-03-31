#include "Renderer.h"

namespace Engine
{

    Renderer::Renderer(GraphicsContext *ctx) : context(ctx)
    {
    }

    Renderer::~Renderer()
    {
        // Don't delete context - it's managed externally
    }

} // namespace Engine
