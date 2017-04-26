
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

		void orbit();

	private:
		HWND window;
		HWND iconsListView;
		std::vector<DesktopIcon> icons;
	};
}
