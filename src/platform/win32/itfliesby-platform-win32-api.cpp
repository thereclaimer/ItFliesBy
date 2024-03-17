#pragma once

#include "itfliesby-platform-win32.hpp"

global u64 bytes_read = 0;

void CALLBACK
itfliesby_platform_win32_api_file_io_completion_routine(
    u64 error_code,
    u64 bytes_transferred,
    LPOVERLAPPED lpOverlapped) {
        
    bytes_read = bytes_transferred;
}


internal handle
itfliesby_platform_win32_api_opengl_initialize(
    handle window_reference) {
    
    ItfliesbyPlatformWin32Window* window = (ItfliesbyPlatformWin32Window*)window_reference;
    
    //==============================
    // DUMMY CONTEXT
    //==============================
    WNDCLASSA window_class = {0};
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = DefWindowProcA;
    window_class.hInstance = GetModuleHandle(0);
    window_class.lpszClassName = "Dummy_WGL_djuasiodwa";


    ITFLIESBY_ASSERT(RegisterClassA(&window_class));

    HWND dummy_window = CreateWindowExA(
        0,
        window_class.lpszClassName,
        "Dummy OpenGL Window",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        window_class.hInstance,
        0);

    ITFLIESBY_ASSERT(dummy_window);

    HDC dummy_context = GetDC(dummy_window);

    //set the pixel format
    PIXELFORMATDESCRIPTOR desired_pixel_format = {0};
    desired_pixel_format.nSize = sizeof(desired_pixel_format);
    desired_pixel_format.nVersion = 1;
    desired_pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    desired_pixel_format.cColorBits = 32;
    desired_pixel_format.cAlphaBits = 8;
    desired_pixel_format.iLayerType = PFD_MAIN_PLANE;
    desired_pixel_format.cDepthBits = 24;
    desired_pixel_format.cStencilBits = 8;

    s32 suggested_pixel_format_index = ChoosePixelFormat(dummy_context, &desired_pixel_format);
    PIXELFORMATDESCRIPTOR suggested_pixel_format = {0};
    DescribePixelFormat(
        dummy_context,
        suggested_pixel_format_index,
        sizeof(suggested_pixel_format),
        &suggested_pixel_format
    );

    SetPixelFormat(
        dummy_context,
        suggested_pixel_format_index,
        &suggested_pixel_format
    );

    HGLRC dummy_opengl_rendering_context = wglCreateContext(dummy_context);
    ITFLIESBY_ASSERT(wglMakeCurrent(dummy_context, dummy_opengl_rendering_context));

    ItfliesbyPlatformWin32WglApi wgl_api = {0};
    wgl_api.create_context      = (func_itfliesby_platform_win32_wgl_create_context_attribs_arb_type)wglGetProcAddress("wglCreateContextAttribsARB");
    wgl_api.choose_pixel_format = (func_itfliesby_platform_win32_wgl_choose_pixel_format_arb_type)wglGetProcAddress("wglChoosePixelFormatARB");

    wglDeleteContext(dummy_opengl_rendering_context);
    ReleaseDC(dummy_window, dummy_context);
    DestroyWindow(dummy_window);

    //==============================
    // REAL CONTEXT
    //==============================
 
    //set our real pixel format
    int pixel_format_attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };

    s32 pixel_format = 0;
    u32 num_formats = 0;
    wgl_api.choose_pixel_format(
        window->device_context,
        pixel_format_attribs, 
        0,
        1,
        &pixel_format, 
        &num_formats
    );

    PIXELFORMATDESCRIPTOR pixel_format_descriptor = {0};
    DescribePixelFormat(
        window->device_context,
        pixel_format,
        sizeof(pixel_format_descriptor),
        &pixel_format_descriptor
    );
    
    ITFLIESBY_ASSERT(SetPixelFormat(window->device_context, pixel_format, &pixel_format_descriptor));

    //create the real  opengl rendering context
    int gl33_attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC opengl_rendering_context = wgl_api.create_context(window->device_context, 0, gl33_attribs);
    ITFLIESBY_ASSERT(opengl_rendering_context);

    //attach the opengl and device contexts
    ITFLIESBY_ASSERT(wglMakeCurrent(window->device_context, opengl_rendering_context));

    window->opengl_context = opengl_rendering_context;

    return((handle)opengl_rendering_context);
}




internal u64
itfliesby_platform_win32_api_file_get_file_size_bytes(
    HANDLE file_handle) {

    u64 file_size = 
        (file_handle == INVALID_HANDLE_VALUE)
        ? 0
        : GetFileSize(file_handle, NULL);

    return(file_size);
}

internal HANDLE
itfliesby_platform_win32_api_open_file(
    str file_path,
    b8  create_new) {

    HANDLE file_handle = 
        CreateFile(
            file_path,
            (GENERIC_READ | GENERIC_WRITE),
            (FILE_SHARE_READ | FILE_SHARE_WRITE),
            NULL,
            create_new ? CREATE_ALWAYS : OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
            NULL
    );

    return (file_handle == INVALID_HANDLE_VALUE)
        ? NULL
        : file_handle;
}

internal void
itfliesby_platform_win32_api_close_file(
    HANDLE file_handle) {

    CloseHandle(file_handle);
}


internal void
itfliesby_platform_win32_api_read_file(
    HANDLE file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer) {

    ITFLIESBY_ASSERT(file_handle);
    ITFLIESBY_ASSERT(allocated_buffer);

    OVERLAPPED overlapped = {0};

    //these happen to be the same value, but they have 2 different meanings
    //one is size, one is an index
    //DONT GET CONFUSED!!!
    u64 actual_file_size      = allocated_buffer_size - 1;
    u64 null_terminator_index = allocated_buffer_size - 1;

    overlapped.Offset = offset;

    // bool read_result = 
    //     ReadFileEx(file_handle,
    //         allocated_buffer,
    //         actual_file_size,
    //         &overlapped,
    //         itfliesby_platform_win32_api_file_io_completion_routine
    // );

    allocated_buffer[null_terminator_index] = '\0';
}

internal void
itfliesby_platform_win32_api_write_file(
    handle file_handle,
    u64    allocated_buffer_size,
    u64    offset,
    memory allocated_buffer) {

    OVERLAPPED overlapped = {0};

    overlapped.Offset = offset;

    // bool read_result = WriteFileEx(
    //     file_handle,
    //     allocated_buffer,
    //     allocated_buffer_size,
    //     &overlapped,
    //     itfliesby_platform_win32_api_file_io_completion_routine
    // );
}

internal handle
itfliesby_platform_win32_api_allocate_memory(u64 size) {

    handle memory = VirtualAlloc(0,size,MEM_COMMIT,PAGE_READWRITE);

    return (memory);
}

internal void
itfliesby_platform_win32_api_free_memory(handle memory, u64 size) {

    VirtualFree(memory,size,MEM_RELEASE);
}