#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <sstream>

#include "Config.h"

static SDL_Window *g_window;

static bool
initSDL()
{
	int imgFlags = IMG_INIT_PNG;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Could not initiate SDL2: " <<  SDL_GetError() << std::endl;
		return false;
	}

	if ( (IMG_Init(imgFlags) & imgFlags) == 0 ) {
		std::cerr
			<< "Unable to initiate img loading: "
			<< IMG_GetError()
			<< std::endl;
		return false;
	}

	std::stringstream ss;
	ss << APP_TITLE << " "
		<< MAJOR_VERSION << "."
		<< MINOR_VERSION << "."
		<< PATCH_VERSION << " "
		<< RELEASE_TYPE;

	g_window = SDL_CreateWindow(ss.str().c_str(),
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, 
								400,
								300,
								SDL_WINDOW_SHOWN);
	return true;
}

static int
gameLoop()
{
	bool quit = false;

	while (!quit) {
	}
	return 0;
}

int
main()
{
	if (!initSDL())
		return 1;
	return gameLoop();
}
