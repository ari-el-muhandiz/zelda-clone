#pragma once

#include <string>

#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "Transform.h"

namespace Engine
{
    struct Sprite 
    {
        Mesh* mesh = nullptr;
        Material* material = nullptr;
    };

    struct Name
    {
        std::string value;
    };

    struct PlayerInput
    {

    };

    struct Active {

    };
}
