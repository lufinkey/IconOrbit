
#include "Desktop.hpp"
#include <algorithm>
#include <thread>
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
		printf("itemCount: %i\n", (int)itemCount);
		icons.reserve(itemCount);
		for(size_t i=0; i<itemCount; i++)
		{
			icons.push_back(DesktopIcon(iconsListView, i));
		}
	}

	Rectangle Desktop::getRect() const
	{
		RECT listViewRect;
		GetWindowRect(iconsListView, &listViewRect);
		return Rectangle((float)listViewRect.left, (float)listViewRect.top, (float)(listViewRect.right-listViewRect.left), (float)(listViewRect.bottom-listViewRect.top));
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
		//sort icons
		std::stable_sort(icons.begin(), icons.end(), [](const DesktopIcon& icon1, const DesktopIcon& icon2){
			if(icon1.getLastKnownIndex() < icon2.getLastKnownIndex())
			{
				return true;
			}
			return false;
		});
	}

	Point Desktop::rotate(Point origin, Point point, float degrees) const
	{
		point.x -= origin.x;
		point.y -= origin.y;

		float radians = degrees*((float)PI/180.0);
		float c = std::cos(radians);
		float s = std::sin(radians);

		float xnew = point.x * c - point.y * s;
		float ynew = point.x * s + point.y * c;

		return Point(origin.x+xnew, origin.y+ynew);
	}

	float Desktop::distance(Point point1, Point point2) const
	{
		float xDist = point2.x-point1.x;
		float yDist = point2.y-point1.y;
		return std::sqrt((xDist*xDist)+(yDist*yDist));
	}

	void Desktop::orbit()
	{
		double moveSpeed = 3;
		double rotationSpeed = 3;

		while(true)
		{
			int listCount = ListView_GetItemCount(iconsListView);
			printf("listCount: %i\n", listCount);

			if(listCount!=0)
			{
				//updateIcons();

				auto windowRect = getRect();
				auto center = windowRect.getCenter();
				for(auto& icon : icons)
				{
					Point position = rotate(center, icon.getPosition(), rotationSpeed);
					float dist = distance(position, center);
					float targetDist = icon.getTargetDistance();
					float moveAmount = moveSpeed;
					if(std::abs(dist-targetDist) < moveAmount)
					{
						moveAmount = dist - targetDist;
					}
					float movePortion = moveAmount/dist;
					position.x += movePortion*(center.x-position.x);
					position.y += movePortion*(center.y-position.y);
					if(position.x < windowRect.x)
					{
						position.x = windowRect.x;
					}
					else if(position.x >(windowRect.x+windowRect.width))
					{
						position.x = windowRect.x + windowRect.width;
					}
					if(position.y < windowRect.y)
					{
						position.y = windowRect.y;
					}
					else if(position.y >(windowRect.y+windowRect.height))
					{
						position.y = windowRect.y + windowRect.height;
					}
					icon.setPosition(position);
				}
			}
			else
			{
				auto shellWindow = GetShellWindow();
				if(shellWindow!=nullptr)
				{
					window = shellWindow;
					HWND defWnd = FindWindowExA(window, nullptr, "SHELLDLL_defVIEW", nullptr);
					iconsListView = FindWindowExA(defWnd, nullptr, "SysListView32", nullptr);
					updateIcons();
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(33));
		}
	}
}
