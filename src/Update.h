#pragma once

#include <SDL.h>
#include "Input.h"

class Update
{
	public:
		Input input;
		SDL_Renderer *renderer;
		SDL_Rect drawRect;

		void handleEvent(const SDL_Event&);
};
