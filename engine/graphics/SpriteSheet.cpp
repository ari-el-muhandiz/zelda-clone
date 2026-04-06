#include "SpriteSheet.h"

namespace Engine
{

    SpriteSheet::SpriteSheet(Texture* texture, int columns, int rows, int frameWidth, int frameHeight)
        : texture(texture), columns(columns), rows(rows), frameWidth(frameWidth), frameHeight(frameHeight)
    {
    }

    SpriteSheet::~SpriteSheet()
    {
        // Note: We do not own the texture, so we do not delete it here
    }

    bool SpriteSheet::getFrameUV(int col, int row, float& outU, float& outV, float& outUSize, float& outVSize) const
    {
        if (col < 0 || col >= columns || row < 0 || row >= rows)
        {
            return false; // Invalid frame index
        }

        outU = static_cast<float>(col) / static_cast<float>(columns);
        outV = static_cast<float>(row) / static_cast<float>(rows);
        outUSize = 1.0f / static_cast<float>(columns);
        outVSize = 1.0f / static_cast<float>(rows);
        return true;
    }

    bool SpriteSheet::applyFrame(int col, int row, Material* material) const
    {
        if (!material)
        {
            return false;
        }

        float u, v, uSize, vSize;
        if (!getFrameUV(col, row, u, v, uSize, vSize))
        {
            return false;
        }
        material->setVec2("uvOffset", u, v);
        material->setVec2("uvScale", uSize, vSize);
        return true;
    }

} // namespace Engine
