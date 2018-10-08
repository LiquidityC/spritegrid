#pragma once

#include <SDL.h>

class Timer
{
	private:
		bool running = false;
		uint32_t startTime = 0;

	public:
		uint32_t getTicks();

		void start();

		void stop();

		void restart();

		bool isStarted();
};
