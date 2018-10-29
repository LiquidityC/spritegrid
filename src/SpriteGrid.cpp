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
#include "Grid.h"
#include "Util.h"
#include "Update.h"
#include "GridComponent.h"

namespace fs = std::filesystem;

static const std::vector<std::string> FILE_SUFFIXES = {
	".png",
	".gif",
	".jpeg",
	".jpg",
	".img"
};

static SDL_Rect gViewport{};
static std::string gTitle;

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
	gTitle = ss.str();

	gWindow = SDL_CreateWindow(gTitle.c_str(),
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, 
								400,
								300,
								SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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
resize_window(const SDL_Rect& rect)
{
	SDL_SetWindowSize(gWindow, rect.w, rect.h);
	gViewport = rect;
	debug("Viewport: " + rect);
}

static SDL_Rect
reload_texture_from_file(Texture& texture, const std::string& path, double scale)
{
	debug("Reloading texture: " + path);

	texture.loadFromFile(path, gRenderer);
	SDL_Rect rect = { 0, 0, (int) texture.getWidth(), (int) texture.getHeight() };

	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	int32_t widthLimit = static_cast<uint32_t>(dm.w * 0.75);
	int32_t heightLimit = static_cast<uint32_t>(dm.h * 0.75);

	if (rect.w > widthLimit || rect.h > heightLimit) {
		rect.w = rect.w >> 1;
		rect.h = rect.h >> 1;
	}

	rect.w = static_cast<int>(rect.w * scale);
	rect.h = static_cast<int>(rect.h * scale);

	SDL_SetWindowTitle(gWindow, std::string(gTitle + " - " + path).c_str());
	resize_window(rect);

	return rect;
}

#define FPS 60
#define SCREEN_TICKS_PER_FRAME (1000 / FPS)

static int
gameLoop()
{
	static int32_t lastImageIndex = currentImageIndex;
	double scale = 1;
	Timer capTimer;
	bool quit = false;
	Grid grid;
	grid.addComponent(new GridComponent());

	Update update;
	update.renderer = gRenderer;

	Texture texture;
	update.drawRect = reload_texture_from_file(texture,
											   filePaths[currentImageIndex],
											   scale);

	SDL_RenderSetViewport(gRenderer, &gViewport);

	SDL_Event event;
	while (!quit) {
		capTimer.start();

		update.input.reset();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.type == SDL_KEYDOWN) {
				quit = event.key.keysym.sym == SDLK_ESCAPE;
			}

			update.handleEvent(event);
		}

		if (update.input.isPressed(K_LEFT)) {
			currentImageIndex--;
			if (currentImageIndex < 0)
				currentImageIndex = static_cast<int>(filePaths.size()) - 1;
		} else if (update.input.isPressed(K_RIGHT)) {
			currentImageIndex++;
			if (currentImageIndex >= static_cast<int32_t>(filePaths.size()))
				currentImageIndex = 0;
		}

		if (update.input.isPressed(K_C_PLUS)) {
			update.drawRect.w = static_cast<int>(update.drawRect.w * 1.2);
			update.drawRect.h = static_cast<int>(update.drawRect.h * 1.2);
			resize_window(update.drawRect);
		} else if (update.input.isPressed(K_C_MINUS)) {
			update.drawRect.w = static_cast<int>(update.drawRect.w * 0.8);
			update.drawRect.h = static_cast<int>(update.drawRect.h * 0.8);
			resize_window(update.drawRect);
		}

		if (lastImageIndex != currentImageIndex) {
			update.drawRect = reload_texture_from_file(texture, filePaths[currentImageIndex], scale);
			lastImageIndex = currentImageIndex;
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		texture.render(gRenderer, nullptr, &update.drawRect);
		grid.update(update);

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

		if (root.empty())
			root = fs::path(".");

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
	if (filePaths.empty()) {
		std::cerr << "No image files found" << std::endl;
		return 1;
	}
	if (!initSDL())
		return 1;
	gameLoop();
	close();
}
