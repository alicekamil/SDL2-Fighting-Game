#include "ObjectRenderer.h"

#include "Collider.h"
#include "Transform.h"
#include "../TextureLoader.h"
#include "../Math/VectorInt.h"

void ObjectRenderer::Start()
{
    Component::Start();
}

void ObjectRenderer::SetTexture(const char* imagePath)
{
    SDL_Surface* loadedSurface = IMG_Load(imagePath);

    cellWidth = loadedSurface->w;
    cellHeight = loadedSurface->h;
    currentColumnIndex = 0;
    currentRowIndex = 0;
    
    texture = TextureLoader::GetTextureFromSurface(loadedSurface);
    
    isSpriteSheet = false;
}

void ObjectRenderer::SetTextureColor(Uint8 r, Uint8 g, Uint8 b)
{
    if(texture == nullptr)
        return;

    SDL_SetTextureColorMod(texture, r, g, b);
}

void ObjectRenderer::SetSpriteSheet(const char* imagePath, int columnCount, int rowCount)
{
    SDL_Surface* loadedSurface = IMG_Load(imagePath);

    this->columnCount = columnCount;
    this->rowCount = rowCount;
    cellWidth = loadedSurface->w / columnCount;
    cellHeight = loadedSurface->h / rowCount;
    currentColumnIndex = 0;
    currentRowIndex = 0;
    
    texture = TextureLoader::GetTextureFromSurface(loadedSurface);

    isSpriteSheet = true;
}

void ObjectRenderer::SetSpriteSheetIndex(int columnIndex, int rowIndex)
{
    currentColumnIndex = columnIndex;
    currentRowIndex = rowIndex;
}

void ObjectRenderer::Render(Window* window)
{
    if(texture == nullptr)
        return;
    
    SDL_Rect destinationRectangle = GetDestinationRect();
    SDL_Rect sourceRectangle = GetSourceRect();
    window->CopyTextureToRenderer(texture, &sourceRectangle, &destinationRectangle, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    if(collider)
    {
        if(collider->debugLines)
        {
            collider->DrawDebugBound(window);
        }
    }
}

SDL_Rect ObjectRenderer::GetSourceRect()
{
    return SDL_Rect(currentColumnIndex * cellWidth, currentRowIndex * cellHeight,
                    cellWidth, cellHeight);
}

SDL_Rect ObjectRenderer::GetDestinationRect()
{
    const VectorInt transformScreenPos = transform->WorldToScreenPos();
    VectorInt transformScreenScale = transform->WorldToScreenScale();

    transformScreenScale.y = static_cast<int>(static_cast<float>(transformScreenScale.y) * (static_cast<float>(cellHeight) / static_cast<float>(cellWidth))); 
    
    return SDL_Rect{
        transformScreenPos.x - transformScreenScale.x / 2,
        transformScreenPos.y - transformScreenScale.y / 2,
        transformScreenScale.x,
        transformScreenScale.y
    };
}
