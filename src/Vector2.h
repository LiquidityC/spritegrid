#pragma once

template<typename T>
class Vector2
{
	public:
		T x, y;

		Vector2(T dx, T dy) : x(dx), y(dy) { };
};
