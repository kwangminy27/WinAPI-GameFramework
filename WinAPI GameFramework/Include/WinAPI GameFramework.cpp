#include "core.h"
#include "resource.h"

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prev_instance, PWSTR cmd_line, int cmd_show)
{
	if (!Core::instance()->Initialize(L"WinAPI GameFramework", L"WinAPI GameFramework", 
		instance, LoadIcon(instance, MAKEINTRESOURCE(IDI_ICON1))))
		return -1;

	Core::instance()->Run();

	return 0;
}