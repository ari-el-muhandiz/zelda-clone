#pragma once

#include "Texture.h"
#include "Material.h"

namespace Engine
{

    class SpriteSheet
    {
    private:
        Texture* texture;
        int columns;
        int rows;
        int frameWidth;
        int frameHeight;

    public:
        SpriteSheet(Texture* texture, int columns, int rows, int frameWidth, int frameHeight);
        ~SpriteSheet();
        
        Texture* getTexture() const { return texture; }
        int getColumns() const { return columns; }
        int getRows() const { return rows; }
        int getFrameWidth() const { return frameWidth; }
        int getFrameHeight() const { return frameHeight; }

        bool getFrameUV(int col, int row, float& outU, float& outV, float& outUSize, float& outVSize) const;
        bool applyFrame(int col, int row, Material* material) const;
    };

} // namespace Engine
