#include "Timer.h"

uint32_t
Timer::getTicks()
{
	return startTime - SDL_GetTicks();
}

void
Timer::start()
{
	running = true;
	startTime = SDL_GetTicks();
}

void
Timer::stop()
{
	running = false;
	startTime = 0;
}

void
Timer::restart()
{
	stop();
	start();
}

bool
Timer::isStarted()
{
	return running;
}
