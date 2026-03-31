#pragma once

#include <string>
#include <cstdint>

namespace Engine
{

    class Shader
    {
    private:
        std::string vertexSource;
        std::string fragmentSource;
        uint32_t programHandle = 0;
        bool compiled = false;

    public:
        Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);
        ~Shader();

        const std::string &getVertexSource() const { return vertexSource; }
        const std::string &getFragmentSource() const { return fragmentSource; }

        uint32_t getProgram() const { return programHandle; }
        bool isCompiled() const { return compiled; }

        void setProgram(uint32_t handle) { programHandle = handle; }
        void setCompiled(bool state) { compiled = state; }

        // Helper to load from files
        static Shader *loadFromFiles(const std::string &vertexPath, const std::string &fragmentPath);
    };

} // namespace Engine
