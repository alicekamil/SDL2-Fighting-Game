#pragma once

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Window
{
	SDL_Window* window{};
	SDL_Surface* screenSurface{};
	bool success;

public:
	SDL_Renderer* renderer;
	inline static int ScreenWidth;
	inline static int ScreenHeight;
	
	Window(int width, int height);
	~Window();
	bool wasSuccessful() { return success; }
	void clear();
	void present();

	void CopyTextureToRenderer(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_Texture* GetTextureFromPath(const char* path);
	SDL_Texture* GetTextureFromSurface(SDL_Surface* surface);
	SDL_Texture* GetTextureFromFont(const char* fontPath, int fontSize);
};

