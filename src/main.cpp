
#include "Desktop.hpp"

int main(int argc, char* argv[])
{
	icorb::Desktop desktop(GetShellWindow());
	desktop.orbit();
	return 0;
}
