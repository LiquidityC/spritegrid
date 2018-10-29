#include "Input.h"

static int getKey(const SDL_Event& event)
{
	if (event.key.keysym.mod == KMOD_NONE) {
		switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				return K_LEFT;
			case SDLK_RIGHT:
				return K_LEFT;
			case SDLK_PLUS:
				return K_PLUS;
			case SDLK_MINUS:
				return K_MINUS;
			default:
				break;
		}
	}
	if (event.key.keysym.mod & KMOD_CTRL) {
		switch (event.key.keysym.sym) {
			case SDLK_PLUS:
				return K_C_PLUS;
			case SDLK_MINUS:
				return K_C_MINUS;
			default:
				break;
		}
	}
	return 0;
}

void Input::reset()
{
	lastKeys = currentKeys;
}

void Input::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION) {
		mousePosition.x = event.motion.x;
		mousePosition.y = event.motion.y;
	}

	if (event.type == SDL_KEYDOWN) {
		currentKeys |= getKey(event);
	} else if (event.type == SDL_KEYUP) {
		currentKeys &= ~getKey(event);
	}
}

bool Input::isDown(uint32_t key) const
{
	return key & currentKeys;
}

bool Input::isPressed(uint32_t key) const
{
	return !(key & lastKeys) && key & currentKeys;
}

bool Input::isReleased(uint32_t key) const
{
	return key & lastKeys && !(key & currentKeys);
}
