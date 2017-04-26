
#pragma once

namespace icorb
{
	class Rectangle
	{
	public:
		constexpr Rectangle() : x(0), y(0), width(0), height(0) {}
		constexpr Rectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {};
		
		float x;
		float y;
		float width;
		float height;
	};
}
