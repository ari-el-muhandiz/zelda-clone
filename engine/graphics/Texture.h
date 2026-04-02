#pragma once
#include <cstdint>
#include <memory>

namespace Engine
{

    class Texture
    {
    private:
        uint32_t textureHandle = 0;
        int width = 0;
        int height = 0;
        int channels = 0;
        bool uploaded = false;
        unsigned char* pixelData = nullptr;

    public:
        Texture(int width, int height, int channels);
        ~Texture();

        uint32_t getHandle() const { return textureHandle; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        int getChannels() const { return channels; }
        bool isUploaded() const { return uploaded; }


        void setHandle(uint32_t handle) { textureHandle = handle; }
        void setUploaded(bool state) { uploaded = state; }
        void setDimensions(int w, int h, int c)
        {
            width = w;
            height = h;
            channels = c;
        }

        // Helper to load from file
        static std::unique_ptr<Texture> loadFromFile(const std::string &filePath);

        const unsigned char* getPixelData() const { return pixelData; }
    };

} // namespace Engine
