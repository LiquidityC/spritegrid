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
#include "Timer.h"
#include "Texture.h"

namespace fs = std::filesystem;

static const std::vector<std::string> FILE_SUFFIXES = {
	".png",
	".gif",
	".jpeg",
	".jpg",
	".img"
};

static SDL_Window	*gWindow;
static SDL_Renderer	*gRenderer;

static std::vector<std::string> filePaths;
static int32_t currentImageIndex = 0;

static bool
initSDL()
{
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;

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

	gWindow = SDL_CreateWindow(ss.str().c_str(),
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, 
								400,
								300,
								SDL_WINDOW_SHOWN);

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return true;
}

static void
close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
	SDL_Quit();
}

static void
reload_texture_from_file(Texture& texture, const std::string& path)
{
	texture.loadFromFile(path, gRenderer);
	SDL_SetWindowSize(gWindow, texture.getWidth(), texture.getHeight());
}

#define FPS 60
#define SCREEN_TICKS_PER_FRAME (1000 / FPS)

static int
gameLoop()
{
	static int32_t lastImageIndex = currentImageIndex;
	Timer capTimer;
	bool quit = false;

	Texture texture;
	reload_texture_from_file(texture, filePaths[currentImageIndex]);

	SDL_Event event;
	while (!quit) {
		capTimer.start();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;

			if (event.type != SDL_KEYDOWN)
				continue;

			switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					currentImageIndex--;
					if (currentImageIndex < 0)
						currentImageIndex = static_cast<int>(filePaths.size()) - 1;
					break;
				case SDLK_RIGHT:
					currentImageIndex++;
					if (currentImageIndex >= static_cast<int32_t>(filePaths.size()))
						currentImageIndex = 0;
					break;
				default:
					break;
			}
		}

		if (lastImageIndex != currentImageIndex) {
			reload_texture_from_file(texture, filePaths[currentImageIndex]);
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		texture.render(gRenderer);

		SDL_RenderPresent(gRenderer);

		uint32_t frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME) {
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
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
		if (hasAnySuffix(pathStr, FILE_SUFFIXES)) {
			filePaths.push_back(pathStr);
		}
	}

	if (argc == 1) {
		fs::path root(argv[0]);
		if (root.string() != ".") {
			if (root.has_filename())
				root.remove_filename();
		}

		for (auto &p: fs::directory_iterator(root)) {
			if (hasAnySuffix(p.path().string(), FILE_SUFFIXES)) {
				filePaths.push_back(p.path().string());
			}
		}
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
	gameLoop();
	close();
}
