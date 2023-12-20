#include "Window.h"

#include "TextureLoader.h"

Window::Window(int width, int height)
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	// initialize SDL_ttf for font loading
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//Start up SDL and create window
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	// Create Window and Renderer
	SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
	if (!window)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");  // make the scaled rendering look smoother.
	SDL_RenderSetLogicalSize(renderer, width, height);
	ScreenWidth = width;
	ScreenHeight = height;

	TextureLoader::window = this;
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Window::clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 120, 60, 255, 255);
	const SDL_Rect rect(0, 0, ScreenWidth, ScreenHeight);
	SDL_RenderFillRect(renderer, &rect);
}

void Window::present()
{
	SDL_RenderPresent(renderer);
}

void Window::CopyTextureToRenderer(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, texture, srcRect, dstRect, 0, NULL, flip);
}

SDL_Texture* Window::GetTextureFromPath(const char* path)
{
	SDL_Surface* loadedSurface = IMG_Load(path);
	return GetTextureFromSurface(loadedSurface);
}

SDL_Texture* Window::GetTextureFromFont(const char* fontPath, int fontSize)
{
	SDL_Texture* textTexture;

	auto font = TTF_OpenFont(fontPath, fontSize);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return nullptr;
	}

	SDL_Color textColor = { 0xff, 0xff, 0xff };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "The lazy fox, blah blah", textColor);
	return GetTextureFromSurface(textSurface);
}

SDL_Texture* Window::GetTextureFromSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = NULL;

	if (surface == NULL)
	{
		printf("Unable to load image");
		return nullptr;
	}
	//Convert surface to screen format
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		printf("Unable to create texture");
		return nullptr;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(surface);
	return texture;
}
