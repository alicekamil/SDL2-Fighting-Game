#pragma once
#include "Component.h"
#include "../Window.h"

class Collider;

class ObjectRenderer : public Component
{
    friend Collider;
    
    SDL_Texture* texture;
    bool isSpriteSheet;
    int columnCount;
    int rowCount;
    int cellWidth;
    int cellHeight;
    int currentColumnIndex;
    int currentRowIndex;

    Collider* collider;

    SDL_Rect GetSourceRect();
    SDL_Rect GetDestinationRect();
public:
    bool flipped = false;
    
    virtual void Start() override;
    void SetTexture(const char* imagePath);
    void SetTextureColor(Uint8 r, Uint8 g, Uint8 b);
    void SetSpriteSheet(const char* imagePath, int columnCount, int rowCount = 1);
    void SetSpriteSheetIndex(int columnIndex, int rowIndex = 0);
    void Render(Window* window);
};
