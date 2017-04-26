
#pragma once

#include <Windows.h>
#include "Point.hpp"
#include "Rectangle.hpp"

namespace icorb
{
	class DesktopIcon
	{
	public:
		DesktopIcon(HWND listView, size_t index);

		bool checkIfExists();

		size_t getLastKnownIndex() const;

		bool changedIndex() const;

		void setPosition(const Point& position);
		const Point& getPosition() const;
		Point getRealPosition() const;
		
		Rectangle getBounds() const;

	private:
		bool changedIndex() const;
		size_t findItemIndex() const;
		size_t getUsableItemIndex() const;

		HWND listView;
		size_t lastKnownIndex;
		LPARAM itemID;

		Point position;
	};
}
