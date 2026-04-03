#include "Material.h"

namespace Engine
{

    Material::Material(Shader *shaderPtr) : shader(shaderPtr)
    {
    }

    Material::~Material()
    {
        // Don't delete shader - it might be shared between multiple materials
    }

    void Material::setFloat(const std::string &name, float value)
    {
        floatUniforms[name] = value;
    }

    void Material::setVec2(const std::string &name, float x, float y)
    {
        vec2Uniforms[name] = {x, y};
    }

    void Material::setInt(const std::string &name, int value)
    {
        intUniforms[name] = value;
    }

} // namespace Engine
