#pragma once

#include "Shader.h"
#include <unordered_map>
#include <string>
#include "Texture.h"

namespace Engine
{

    class Material
    {
    private:
        Shader *shader;
        std::unordered_map<std::string, float> floatUniforms;
        std::unordered_map<std::string, std::pair<float, float>> vec2Uniforms;
        Texture *texture = nullptr;

    public:
        Material(Shader *shaderPtr);
        ~Material();

        Shader *getShader() const { return shader; }

        // Set uniform values
        void setFloat(const std::string &name, float value);
        void setVec2(const std::string &name, float x, float y);

        // Get uniform values
        const std::unordered_map<std::string, float> &getFloatUniforms() const { return floatUniforms; }
        const std::unordered_map<std::string, std::pair<float, float>> &getVec2Uniforms() const { return vec2Uniforms; }

        // Texture management
        void setTexture(Texture *tex) { texture = tex; }
        Texture *getTexture() const { return texture; }
    };

} // namespace Engine
