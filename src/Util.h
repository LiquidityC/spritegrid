#pragma once

#include <SDL.h>
#include <string>
#include <iostream>

#define debug(t) debug_print(__LINE__, __FILE__, t)

template<typename T> void
debug_print(int line, const std::string& file, const T& t)
{
#ifdef DEBUG
	std::cout << "[" << file << ":" << line << "]:\t" << t << std::endl;
#endif
}

std::ostream&
operator<<(std::ostream& out, const SDL_Rect& rect);

std::string
operator+(const std::string& dest, const SDL_Rect& rect);
