#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <set>
#include <vector>

#include "Config.h"
#include "Definitions.h"
#include "StringUtil.h"

namespace fs = std::filesystem;

static const std::vector<std::string> FILE_SUFFIXES = {
	".png",
	".gif",
	".jpeg",
	".jpg",
	".img"
};

static SDL_Window *g_window;
static std::set<std::string> filePaths;

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
		quit = true;
	}
	return 0;
}

static void
printUsage(const std::string &cmd)
{
	std::cerr << "Usage: " << cmd << " "
		<< "[file(s)]" << std::endl;
}

static void
loadFilesForArgs(int argc, char **argv)
{
	for (auto i = 0; i < argc; ++i) {
		std::string pathStr(argv[i]);
		if (hasSuffix(pathStr, ".png")) {
			filePaths.insert(pathStr);
		}
	}

	for (auto &p: fs::directory_iterator(".")) {
		std::cout << p << std::endl;
	}
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		printUsage(argv[0]);
		return 1;
	}
	loadFilesForArgs(argc-1, argv+1);
	if (!initSDL())
		return 1;
	return gameLoop();
}
