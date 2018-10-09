#pragma once

#include <SDL.h>

class Grid
{
	private:
		uint32_t spacing = 16;
		double scale = 1;

	public:
		void render(SDL_Renderer*, const SDL_Rect& drawRect);

		void setScale(double);

		double getScale() const;

		void increaseSpacing();

		void decreaseSpacing();
};
