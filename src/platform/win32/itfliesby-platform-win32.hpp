#ifndef ITFLIESBY_PLATFORM_WIN32_HPP
#define ITFLIESBY_PLATFORM_WIN32_HPP

#include <Windows.h>
#include <itfliesby.hpp>

#define itfliesby_platform_win32_main wWinMain

struct ItfliesbyPlatformWin32Window {
    HWND                        window_handle;
    HDC                         device_context;
    bool                        full_screen;
    bool                        maximized;
    u64                         window_style;
    u64                         window_ex_style;
    ItfliesbyViewportDimensions viewport_dimensions;
    ItfliesbyUserInput          user_input;
    bool                        running;
    HGLRC                       opengl_context;
};

typedef HGLRC
(*func_itfliesby_platform_win32_wgl_create_context_attribs_arb_type)
(
    HDC       hdc, 
    HGLRC     share_context,
    const int *attrib_list
);

typedef BOOL
(*func_itfliesby_platform_win32_wgl_choose_pixel_format_arb_type)
(
    HDC          hdc,
    const int*   attrib_list_int,
    const FLOAT* attrib_list_float, 
    UINT         max_formats,
    int*         formats, 
    UINT*        num_formats
);

struct ItfliesbyPlatformWin32WglApi {
    func_itfliesby_platform_win32_wgl_create_context_attribs_arb_type create_context;
    func_itfliesby_platform_win32_wgl_choose_pixel_format_arb_type    choose_pixel_format;
};

#endif //ITFLIESBY_PLATFORM_WIN32_HPP