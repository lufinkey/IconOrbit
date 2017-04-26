
#include "DesktopIcon.hpp"
#include <CommCtrl.h>

namespace icorb
{
	DesktopIcon::DesktopIcon(HWND listView, size_t index)
		: listView(listView),
		lastKnownIndex(index),
		itemID(0)
	{
		LVITEM itemInfo;
		ZeroMemory(&itemInfo, sizeof(LVITEM));
		itemInfo.iItem = (int)index;
		itemInfo.mask = LVIF_PARAM;
		ListView_GetItem(listView, &itemInfo);
		itemID = itemInfo.lParam;
		position = getRealPosition();
	}

	bool DesktopIcon::checkIfExists()
	{
		if(lastKnownIndex==-1)
		{
			return false;
		}
		if(changedIndex())
		{
			lastKnownIndex = findItemIndex();
			if(lastKnownIndex==-1)
			{
				return false;
			}
		}
		return true;
	}

	bool DesktopIcon::changedIndex() const
	{
		if(lastKnownIndex==-1)
		{
			return false;
		}
		if((int)lastKnownIndex >= ListView_GetItemCount(listView))
		{
			return true;
		}
		LVITEM itemInfo;
		ZeroMemory(&itemInfo, sizeof(LVITEM));
		itemInfo.iItem = (int)lastKnownIndex;
		itemInfo.mask = LVIF_PARAM;
		ListView_GetItem(listView, &itemInfo);
		if(itemID != itemInfo.lParam)
		{
			return true;
		}
		return false;
	}

	size_t DesktopIcon::findItemIndex() const
	{
		int iconCount = ListView_GetItemCount(listView);
		for(int i=0; i<iconCount; i++)
		{
			LVITEM itemInfo;
			ZeroMemory(&itemInfo, sizeof(LVITEM));
			itemInfo.iItem = (int)lastKnownIndex;
			itemInfo.mask = LVIF_PARAM;
			ListView_GetItem(listView, &itemInfo);
			if(itemID == itemInfo.lParam)
			{
				return (size_t)i;
			}
		}
		return -1;
	}
	
	size_t DesktopIcon::getUsableItemIndex() const
	{
		if(lastKnownIndex==-1)
		{
			return -1;
		}
		size_t index = lastKnownIndex;
		if(!changedIndex())
		{
			index = findItemIndex();
		}
		return index;
	}

	size_t DesktopIcon::getLastKnownIndex() const
	{
		return lastKnownIndex;
	}

	void DesktopIcon::setPosition(const Point& position_arg)
	{
		position = position_arg;
		if(!checkIfExists())
		{
			return;
		}
		ListView_SetItemPosition(listView, (int)lastKnownIndex, (int)position.x, (int)position.y);
	}

	const Point& DesktopIcon::getPosition() const
	{
		return position;
	}

	Point DesktopIcon::getRealPosition() const
	{
		size_t index = getUsableItemIndex();
		if(index == -1)
		{
			return Point(0,0);
		}
		POINT pos;
		pos.x = 0;
		pos.y = 0;
		ListView_GetItemPosition(listView, (int)index, &pos);
		return Point((float)pos.x, (float)pos.y);
	}
	
	Rectangle DesktopIcon::getBounds() const
	{
		size_t index = getUsableItemIndex();
		if(index == -1)
		{
			return Rectangle(0,0,0,0);
		}
		RECT rect;
		ZeroMemory(&rect, sizeof(RECT));
		ListView_GetItemRect(listView, (int)index, &rect, LVIR_BOUNDS);
		return Rectangle((float)rect.left, (float)rect.top, (float)(rect.right-rect.left), (float)(rect.bottom-rect.top));
	}
}
