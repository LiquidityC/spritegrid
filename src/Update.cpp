#include "Update.h"

void Update::handleEvent(const SDL_Event& event)
{
	input.handleEvent(event);
}
