#ifndef ITFLIESBY_PLATFORM_WIN32_HPP
#define ITFLIESBY_PLATFORM_WIN32_HPP

#include <Windows.h>
#include <itfliesby.hpp>

#define itfliesby_platform_win32_main wWinMain

struct ItfliesbyPlatformWin32Window {
    HANDLE window_handle;
};

#endif //ITFLIESBY_PLATFORM_WIN32_HPP