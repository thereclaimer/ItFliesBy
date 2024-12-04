#pragma once

#include "ifb-win32.hpp"

/**********************************************************************************/
/* WINDOW API                                                                     */
/**********************************************************************************/

ifb_internal const ifb_b8
ifb_win32::window_create(
    IFBPlatformWindow* platform_window_ptr) {

    ifb_b8 result = true;

    //get context info
    const HINSTANCE h_instance = ifb_win32::context_args_h_instance();

    //cast the window memory to win32 info
    IFBWin32Window* win32_window_ptr = ifb_win32::window_platform_memory(platform_window_ptr);

    //regizster class
    WNDCLASSA window_class = {0};
    window_class.lpfnWndProc   = (WNDPROC)ifb_win32::window_callback;
    window_class.hInstance     = h_instance; 
    window_class.lpszClassName = "IFBWin32Window";
    window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&window_class)) {
        result = false;
    }

    //create the window handle
    win32_window_ptr->window_handle = CreateWindowA(
        window_class.lpszClassName,
        platform_window_ptr->title,
        WS_OVERLAPPEDWINDOW,
        platform_window_ptr->position_x,
        platform_window_ptr->position_y,
        platform_window_ptr->width,
        platform_window_ptr->height,
        NULL,
        NULL,
        h_instance,
        NULL);

    result &= win32_window_ptr->window_handle != NULL;

    //get the device context
    win32_window_ptr->device_context = GetDC(window.window_handle);

    //we're done
    return(result);    
}

ifb_internal const ifb_b8 
ifb_win32::window_destroy(
    IFBPlatformWindow* platform_window_ptr) {

    PostQuitMessage(0);

    return(true);
}

ifb_internal const ifb_b8 
ifb_win32::window_frame_start(
    IFBPlatformWindow* platform_window_ptr) {

    IFBWin32Window* window_ptr = ifb_win32::window_platform_memory(platform_window_ptr);

    //start a new imgui frame if we have a context
    if (window_ptr->imgui_context) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    //go through the messages for the window 
    MSG window_message;
    while(PeekMessage(&window_message,window_ptr->window_handle,0,0,PM_REMOVE)) {

        //handle the messages
        TranslateMessage(&window_message);
        DispatchMessage(&window_message);

        //if it was a quit, set the quit received flag
        if (window_message.message == WM_QUIT) {
            platform_window_ptr->quit_received = true;
        }
    }

    return(!platform_window_ptr->quit_received);
}

ifb_internal const ifb_b8 
ifb_win32::window_frame_render(
    IFBPlatformWindow* platform_window_ptr) {

    //get the window
    IFBWin32Window* window_ptr = ifb_win32::window_platform_memory(platform_window_ptr);

    //if we have an imgui context, render the draw data
    if (window_ptr->imgui_context) {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    //swap the buffers
    SwapBuffers(window_ptr->device_context);

    //return quit event status
    return(!platform_window_ptr->quit_received);
}

ifb_internal const ifb_b8 
ifb_win32::window_show(
    IFBPlatformWindow* platform_window_ptr) {

    //get the window
    IFBWin32Window* window_ptr = ifb_win32::window_platform_memory(platform_window_ptr);

    const ifb_b8 result = (ifb_b8)ShowWindow(window_ptr->window_handle,1);

    return(true);
}

ifb_internal const ifb_b8 
ifb_win32::window_opengl_init(
    IFBPlatformWindow* platform_window_ptr) {

    //set our preferred format descriptor
    PIXELFORMATDESCRIPTOR preferred_format_descriptor = {0};
    preferred_format_descriptor.nSize      = sizeof(preferred_format_descriptor);
    preferred_format_descriptor.nVersion   = 1;
    preferred_format_descriptor.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    preferred_format_descriptor.iPixelType = PFD_TYPE_RGBA;
    preferred_format_descriptor.cColorBits = 32;

    //get the window
    IFBWin32Window* window_ptr = ifb_win32::window_platform_memory(platform_window_ptr);


    //query for the closest format descriptor
    const ifb_s32 chosen_format_descriptor = 
        ChoosePixelFormat(
            window_ptr->device_context,
            &preferred_format_descriptor);

    //set the chosen pixel format
    const ifb_b8 pixel_format_is_set = 
        SetPixelFormat(
            window_ptr->device_context,
            chosen_format_descriptor,
            &preferred_format_descriptor);

    //create the opengl context
    window_ptr->opengl_context = wglCreateContext(window_ptr->device_context);

    //make the context current
    const ifb_b8 context_active = wglMakeCurrent(platform_window_ptr->device_context, window_ptr->opengl_context);

    //sanity check
    ifb_b8 result = (
        chosen_format_descriptor &&
        pixel_format_is_set      &&
        opengl_context           &&
        context_active);

    //we're done
    return(result);
}

ifb_internal const ifb_b8 
ifb_win32::window_imgui_init(
    IFBPlatformWindow* platform_window_ptr) {

    return(true);
}

/**********************************************************************************/
/* INLINE                                                                         */
/**********************************************************************************/

inline IFBWin32Window* 
ifb_win32::window_platform_memory(
    const IFBPlatformWindow* platform_window_ptr) {

    IFBWin32Window* window_ptr = (IFBWin32Window*)platform_window_ptr->memory_start;
}

ifb_internal LRESULT CALLBACK
ifb_win32::window_callback(
    HWND   window_handle,
    UINT   message,
    WPARAM w_param,
    LPARAM l_param) {

    ifb_win32_funcptr_on_wm_message_t wm_message_handler = NULL;

    if (ifb_win32::context_window_has_imgui()) {
        
        const LRESULT imgui_result =
            ImGui_ImplWin32_WndProcHandler(
                window_handle,
                message,
                w_param,
                l_param);

        if (imgui_result) {
            return(true);
        }
    }

    switch (message) {

        case WM_SIZE:    wm_message_handler = ifb_win32::window_on_wm_size;    break; 
        case WM_MOVE:    wm_message_handler = ifb_win32::window_on_wm_move;    break; 
        case WM_QUIT:    wm_message_handler = ifb_win32::window_on_wm_quit;    break; 
        case WM_DESTROY: wm_message_handler = ifb_win32::window_on_wm_destroy; break; 
    }

    LRESULT wm_message_result =
        wm_message_handler
            ? wm_message_handler(w_param,l_param)
            : DefWindowProc(
                window_handle,
                message,
                w_param,
                l_param);

    return(wm_message_result);
}

/**********************************************************************************/
/* INLINE                                                                         */
/**********************************************************************************/

inline const LRESULT 
ifb_win32::window_on_wm_size(
    const WPARAM w_param, 
    const LPARAM l_param) {

    const ifb_u32 window_width  = LOWORD(l_param);
    const ifb_u32 window_height = HIWORD(l_param);

    ifb_engine::platform_window_update_position(window_width, window_height);

    return(S_OK);   
}

inline const LRESULT
ifb_win32::window_on_wm_move(
    const WPARAM w_param, 
    const LPARAM l_param) {

    const ifb_u32 window_position_x = LOWORD(l_param);
    const ifb_u32 window_position_y = HIWORD(l_param);

    ifb_engine::platform_window_update_size(window_position_x, window_position_y);

    return(S_OK);
}

inline const LRESULT 
ifb_win32::window_on_wm_quit(
    const WPARAM w_param, 
    const LPARAM l_param) {

    IFBWin32Window& window_ref = ifb_win32::context_window_ref();

    window_ref.quit_received = true;

    return(S_OK);
}

inline const LRESULT 
ifb_win32::window_on_wm_destroy(
    const WPARAM w_param, 
    const LPARAM l_param) {

    PostQuitMessage(0);

    return(S_OK);
}

inline ifb_void 
ifb_win32::window_api_initialize(
    IFBEnginePlatformWindow& window_api_ref) {
    
    window_api_ref.create       = ifb_win32::window_create;
    window_api_ref.destroy      = ifb_win32::window_destroy;
    window_api_ref.frame_start  = ifb_win32::window_frame_start;
    window_api_ref.frame_render = ifb_win32::window_frame_render;
    window_api_ref.show         = ifb_win32::window_show;
    window_api_ref.opengl_init  = ifb_win32::window_opengl_init;
    window_api_ref.imgui_init   = ifb_win32::window_imgui_init;
}