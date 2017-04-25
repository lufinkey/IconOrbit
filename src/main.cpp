
#include <stdio.h>
#include <thread>
#include <chrono>
#include "Windows.h"
#include "Commctrl.h"

HWND GetDesktopIconsListView()
{
	HWND shellWnd = GetShellWindow();
	HWND defWnd = FindWindowExA(shellWnd, nullptr, "SHELLDLL_defVIEW", nullptr);
	HWND deskIconsWnd = FindWindowExA(defWnd, nullptr, "SysListView32", nullptr);
	return deskIconsWnd;
}

int main(int argc, char* argv[])
{
	HWND iconsListView = GetDesktopIconsListView();
	int x = 0;
	while(x < 600)
	{
		ListView_SetItemPosition(iconsListView, 0, x, 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(33));
		x += 3;
	}
	system("PAUSE");
	return 0;
}
