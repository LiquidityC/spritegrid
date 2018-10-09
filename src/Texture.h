#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Dimension.h"

class Texture
{
	private:
		SDL_Texture *texture = nullptr;
		Dimension dim = { 0, 0 }; 

	public:
		bool loadFromFile(const std::string& path, SDL_Renderer *renderer);

		void render(SDL_Renderer *renderer,
					const SDL_Rect* clip,
					const SDL_Rect* area);

		uint32_t getWidth() const;

		uint32_t getHeight() const;
};
