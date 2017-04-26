
#include "Desktop.hpp"
#include <CommCtrl.h>

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

	void Desktop::updateIcons()
	{
		//remove deleted icons
		for(size_t i=(icons.size()-1); i!=-1; i--)
		{
			if(!icons[i].checkIfExists())
			{
				icons.erase(icons.begin()+i);
			}
		}
		//add new icons
		size_t itemCount = (size_t)ListView_GetItemCount(iconsListView);
		for(size_t i=0; i<itemCount; i++)
		{
			bool foundItemIndex = false;
			for(size_t j=0; j<icons.size(); j++)
			{
				auto& icon = icons[i];
				if(icon.getLastKnownIndex()==i)
				{
					foundItemIndex = true;
					break;
				}
			}
			if(!foundItemIndex)
			{
				icons.push_back(DesktopIcon(iconsListView, i));
			}
		}
	}

	void Desktop::orbit()
	{
		//TODO orbit
	}
}
