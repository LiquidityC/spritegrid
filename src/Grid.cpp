#include "Grid.h"

void
Grid::render(SDL_Renderer *renderer, const SDL_Rect& drawRect)
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);

	double increment = static_cast<double>(spacing) * scale;
	for (double i = 0; i < static_cast<double>(drawRect.h); i += increment)
		SDL_RenderDrawLine(renderer, 0, (int) i, drawRect.w, (int) i);
	for (double i = 0; i < static_cast<double>(drawRect.w); i += increment)
		SDL_RenderDrawLine(renderer, (int) i, 0, (int) i, drawRect.h);
}

void
Grid::setScale(double newScale)
{
	scale = newScale;
}

double
Grid::getScale() const
{
	return scale;
}

void
Grid::increaseSpacing()
{
	if (spacing == 8) {
		spacing += 8;
	} else if (spacing < 96) {
		spacing += 16;
	}
}

void
Grid::decreaseSpacing()
{
	if (spacing == 16) {
		spacing -= 8;
	} else if (spacing >= 16) {
		spacing -= 16;
	}
}
