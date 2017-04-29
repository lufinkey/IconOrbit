
#pragma once

#include <vector>
#include "DesktopIcon.hpp"

namespace icorb
{
	class Desktop
	{
	public:
		static Desktop getMainDesktop();

		Desktop(HWND window);

		Rectangle getRect() const;

		void orbit();

	private:
		void updateIcons();

		Point rotate(Point origin, Point point, float degrees) const;
		float distance(Point point1, Point point2) const;

		HWND window;
		HWND iconsListView;
		std::vector<DesktopIcon> icons;
	};
}
