
#pragma once

namespace icorb
{
	class Point
	{
	public:
		constexpr Point() : x(0), y(0) {}
		constexpr Point(float x, float y) : x(x), y(y) {}

		float x;
		float y;
	};
}
