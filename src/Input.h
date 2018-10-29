#pragma once

#include <SDL.h>
#include "Vector2.h"

#define K_PLUS		0x1
#define K_MINUS		0x2
#define K_C_PLUS	0x4
#define K_C_MINUS	0x6
#define K_RIGHT		0x8
#define K_LEFT		0x10

class Input
{
	private:
		int64_t lastKeys = 0,
				currentKeys = 0;

	public:
		SDL_Renderer *renderer;
		Vector2<int> mousePosition = Vector2(0, 0);	

	public:
		Input() { }

		void reset();

		void handleEvent(const SDL_Event&);

		bool isDown(uint32_t key) const;

		bool isPressed(uint32_t key) const;

		bool isReleased(uint32_t key) const;
};
