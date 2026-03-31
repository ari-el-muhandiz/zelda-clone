#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace Engine
{

    static std::string resolvePath(const std::string &relativePath)
    {
        // Use the engine's graphics directory as base
        // __FILE__ gives us the full path: /path/to/engine/graphics/Shader.cpp
        std::filesystem::path currentFile = __FILE__;
        std::filesystem::path graphicsDir = currentFile.parent_path();
        std::filesystem::path engineDir = graphicsDir.parent_path();
        std::filesystem::path projectRoot = engineDir.parent_path();
        std::filesystem::path shaderPath = projectRoot / relativePath;
        
        return shaderPath.string();
    }

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
        std::string resolvedVertexPath = resolvePath(vertexPath);
        std::string resolvedFragmentPath = resolvePath(fragmentPath);
        
        // Load vertex shader
        std::ifstream vertexFile(resolvedVertexPath);
        if (!vertexFile.is_open())
        {
            std::cerr << "Failed to open vertex shader file: " << resolvedVertexPath << std::endl;
            return nullptr;
        }
        std::stringstream vertexBuffer;
        vertexBuffer << vertexFile.rdbuf();
        std::string vertexSource = vertexBuffer.str();

        // Load fragment shader
        std::ifstream fragmentFile(resolvedFragmentPath);
        if (!fragmentFile.is_open())
        {
            std::cerr << "Failed to open fragment shader file: " << resolvedFragmentPath << std::endl;
            return nullptr;
        }
        std::stringstream fragmentBuffer;
        fragmentBuffer << fragmentFile.rdbuf();
        std::string fragmentSource = fragmentBuffer.str();

        return std::make_unique<Shader>(vertexSource, fragmentSource);
    }

} // namespace Engine
