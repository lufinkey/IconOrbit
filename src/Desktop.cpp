
#include <CommCtrl.h>
#include "Desktop.hpp"

namespace icorb
{
	Desktop Desktop::getMainDesktop()
	{
		HWND shellWnd = GetShellWindow();
		return Desktop(shellWnd);
	}

	Desktop::Desktop(HWND window)
		: window(window)
	{
		HWND defWnd = FindWindowExA(window, nullptr, "SHELLDLL_defVIEW", nullptr);
		iconsListView = FindWindowExA(defWnd, nullptr, "SysListView32", nullptr);
		size_t itemCount = (size_t)ListView_GetItemCount(iconsListView);
		icons.reserve(itemCount);
		for(size_t i=0; i<itemCount; i++)
		{
			icons.push_back(DesktopIcon(iconsListView, i));
		}
	}

	void orbit()
	{
		//TODO orbit
	}
}
