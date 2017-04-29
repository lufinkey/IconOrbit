
#pragma once

namespace icorb
{
	const long double PI = 3.14159265358979323846264338328L;

	class Point
	{
	public:
		constexpr Point() : x(0), y(0) {}
		constexpr Point(float x, float y) : x(x), y(y) {}

		float x;
		float y;
	};
}
