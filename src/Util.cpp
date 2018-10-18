#include <sstream>
#include "Util.h"

std::ostream&
operator<<(std::ostream& out, const SDL_Rect& rect)
{
	out << rect.x << "," << rect.y << " " << rect.w << "x" << rect.h;
	return out;
}

std::string
operator+(const std::string& dest, const SDL_Rect& rect)
{
	std::stringstream ss;
	ss << dest << rect;
	return ss.str();
}
