
#pragma once

#include "Point.hpp"

namespace icorb
{
	class Rectangle
	{
	public:
		constexpr Rectangle() : x(0), y(0), width(0), height(0) {}
		constexpr Rectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {};

		constexpr Point getCenter() const { return Point(x+(width/2), y+(height/2)); }
		
		float x;
		float y;
		float width;
		float height;
	};
}
