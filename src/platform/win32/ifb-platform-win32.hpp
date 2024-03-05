#ifndef IFB_PLATFORM_WIN32_HPP
#define IFB_PLATFORM_WIN32_HPP

#include <Windows.h>

#define ifb_platform_win32_main wWinMain

struct IfbPlatformWin32Window {
    HANDLE window_handle;
};

#endif //IFB_PLATFORM_WIN32_HPP