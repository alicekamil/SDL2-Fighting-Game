#include "TextureLoader.h"

SDL_Texture* TextureLoader::GetTextureFromPath(const char* path)
{
    return window->GetTextureFromPath(path);
}

SDL_Texture* TextureLoader::GetTextureFromSurface(SDL_Surface* surface)
{
    return window->GetTextureFromSurface(surface);
}

SDL_Texture* TextureLoader::GetTextureFromFont(const char* fontPath, int fontSize)
{
    return window->GetTextureFromFont(fontPath, fontSize);
}
