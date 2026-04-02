#include "Texture.h"
#include <string>
#include <stb_image.h>

namespace Engine
{

    Texture::Texture(int width, int height, int channels)
        : width(width), height(height), channels(channels)
    {
    }

    Texture::~Texture()
    {
        if (pixelData)
        {
            stbi_image_free(pixelData);
        }
    }

    std::unique_ptr<Texture> Texture::loadFromFile(const std::string &filePath)
    {
        stbi_set_flip_vertically_on_load(true); // Flip the image vertically on load
        int width, height, channels;
        unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &channels, 4); // Force 4 channels (RGBA)
        if (!data)
        {
            return nullptr;
        }

        auto texture = std::make_unique<Texture>(width, height, channels);
        texture->pixelData = data;
        return texture;
    }

} // namespace Engine
