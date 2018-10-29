#include <iostream>
#include "GridComponent.h"

void GridComponent::update(const Update& update)
{
	if (update.input.isPressed(K_PLUS))
		increaseSpacing();
	if (update.input.isPressed(K_MINUS))
		decreaseSpacing();
	if (update.input.isPressed(K_C_PLUS))
		scale *= 1.2;
	if (update.input.isPressed(K_C_MINUS))
		scale *= 0.8;

	SDL_SetRenderDrawColor(update.renderer, 0xFF, 0x0, 0x0, 0xFF);

	double increment = static_cast<double>(spacing) * scale;
	for (double i = 0; i < static_cast<double>(update.drawRect.h); i += increment)
		SDL_RenderDrawLine(update.renderer, 0, (int) i, update.drawRect.w, (int) i);
	for (double i = 0; i < static_cast<double>(update.drawRect.w); i += increment)
		SDL_RenderDrawLine(update.renderer, (int) i, 0, (int) i, update.drawRect.h);
}

void GridComponent::receive(const Message& message)
{
	(void) message;
}

void GridComponent::increaseSpacing()
{
	if (spacing == 8) {
		spacing += 8;
	} else if (spacing < 96) {
		spacing += 16;
	}
}

void GridComponent::decreaseSpacing()
{
	if (spacing == 16) {
		spacing -= 8;
	} else if (spacing >= 16) {
		spacing -= 16;
	}
}
