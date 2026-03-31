#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Engine
{

    Shader::Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
        : vertexSource(vertexShaderSource), fragmentSource(fragmentShaderSource)
    {
    }

    Shader::~Shader()
    {
        // Resources are managed by renderer
    }

    std::unique_ptr<Shader> Shader::loadFromFiles(const std::string &vertexPath, const std::string &fragmentPath)
    {
        // Load vertex shader
        std::ifstream vertexFile(vertexPath);
        if (!vertexFile.is_open())
        {
            std::cerr << "Failed to open vertex shader file: " << vertexPath << std::endl;
            return nullptr;
        }
        std::stringstream vertexBuffer;
        vertexBuffer << vertexFile.rdbuf();
        std::string vertexSource = vertexBuffer.str();

        // Load fragment shader
        std::ifstream fragmentFile(fragmentPath);
        if (!fragmentFile.is_open())
        {
            std::cerr << "Failed to open fragment shader file: " << fragmentPath << std::endl;
            return nullptr;
        }
        std::stringstream fragmentBuffer;
        fragmentBuffer << fragmentFile.rdbuf();
        std::string fragmentSource = fragmentBuffer.str();

        return std::make_unique<Shader>(vertexSource, fragmentSource);
    }

} // namespace Engine
