#include <cstdio>
#include "Texture.h"

bool
Texture::loadFromFile(const std::string& path, SDL_Renderer *renderer)
{
	// Cleanup first
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		dim = { 0, 0 };
	}

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
		return false;
	} else {
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( texture == nullptr ) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
			return false;
		}

		// Update texture dimensions
		dim = {
			(uint32_t) loadedSurface->w,
			(uint32_t) loadedSurface->h
		};

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return true;
}

void
Texture::render(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}
