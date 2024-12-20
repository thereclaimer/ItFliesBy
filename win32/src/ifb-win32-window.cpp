#pragma once

#include "ifb-win32.hpp"

/**********************************************************************************/
/* WINDOW API                                                                     */
/**********************************************************************************/

inline ifb_void 
ifb_win32::window_api_initialize(
    IFBPlatformWindowApi& window_api_ref) {
    
    window_api_ref.create       = ifb_win32::window_create;
    window_api_ref.destroy      = ifb_win32::window_destroy;
    window_api_ref.frame_start  = ifb_win32::window_frame_start;
    window_api_ref.frame_render = ifb_win32::window_frame_render;
    window_api_ref.show         = ifb_win32::window_show;
    window_api_ref.opengl_init  = ifb_win32::window_opengl_init;
    window_api_ref.imgui_init   = ifb_win32::window_imgui_init;
}

ifb_internal const ifb_b8
ifb_win32::window_create(
    const ifb_cstr title,
    const ifb_u32  width,
    const ifb_u32  height,
    const ifb_u32  position_x,
    const ifb_u32  position_y) {

    ifb_b8 result = true;

    //get the window
    IFBWin32Window& window_ref = ifb_win32::context_get_window();

    //get context info
    const HINSTANCE h_instance = ifb_win32::context_args_get_h_instance();

    //register class
    WNDCLASSA window_class = {0};
    window_class.lpfnWndProc   = (WNDPROC)ifb_win32::window_callback;
    window_class.hInstance     = h_instance; 
    window_class.lpszClassName = "IFBWin32Window";
    window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&window_class)) {
        result = false;
    }

    //create the window handle
    window_ref.window_handle = CreateWindowA(
        window_class.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW,
        position_x,
        position_y,
        width,
        height,
        NULL,
        NULL,
        h_instance,
        NULL);

    result &= window_ref.window_handle != NULL;

    //get the device context
    window_ref.device_context = GetDC(window_ref.window_handle);
    result &= window_ref.device_context != NULL;

    //we're done
    return(result);    
}

ifb_internal const ifb_b8 
ifb_win32::window_destroy(
    ifb_void) {

    PostQuitMessage(0);

    return(true);
}

ifb_internal const ifb_b8 
ifb_win32::window_frame_start(
    ifb_void) {

    //get the window
    IFBWin32Window& window_ref = ifb_win32::context_get_window();

    //start a new imgui frame if we have a context
    if (window_ref.imgui_context) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    //go through the messages for the window 
    MSG window_message;
    while(PeekMessage(&window_message,window_ref.window_handle,0,0,PM_REMOVE)) {

        //handle the messages
        TranslateMessage(&window_message);
        DispatchMessage(&window_message);

        //if it was a quit, set the quit received flag
        if (window_message.message == WM_QUIT) {
            window_ref.quit_received = true;
        }
    }

    return(true);
}

ifb_internal const ifb_b8 
ifb_win32::window_frame_render(
    ifb_void) {

    //get the window
    IFBWin32Window& window_ref = ifb_win32::context_get_window();

    //if we have an imgui context, render the draw data
    if (window_ref.imgui_context) {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    //swap the buffers
    SwapBuffers(window_ref.device_context);

    //we're done
    return(true);
}

ifb_internal const ifb_b8 
ifb_win32::window_show(
    ifb_void) {

    //get the window
    IFBWin32Window& window_ref = ifb_win32::context_get_window();

    //show the window
    const ifb_b8 result = (ifb_b8)ShowWindow(window_ref.window_handle,1);

    //we're done
    return(result);
}

ifb_internal const ifb_b8 
ifb_win32::window_opengl_init(
    ifb_void) {

    //set our preferred format descriptor
    PIXELFORMATDESCRIPTOR preferred_format_descriptor = {0};
    preferred_format_descriptor.nSize      = sizeof(preferred_format_descriptor);
    preferred_format_descriptor.nVersion   = 1;
    preferred_format_descriptor.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    preferred_format_descriptor.iPixelType = PFD_TYPE_RGBA;
    preferred_format_descriptor.cColorBits = 32;

    //get the window
    IFBWin32Window& window_ref = ifb_win32::context_get_window();

    //query for the closest format descriptor
    const ifb_s32 chosen_format_descriptor = 
        ChoosePixelFormat(
            window_ref.device_context,
            &preferred_format_descriptor);

    //set the chosen pixel format
    const ifb_b8 pixel_format_is_set = 
        SetPixelFormat(
            window_ref.device_context,
            chosen_format_descriptor,
            &preferred_format_descriptor);

    //create the opengl context
    window_ref.opengl_context = wglCreateContext(window_ref.device_context);

    //make the context current
    const ifb_b8 context_active = wglMakeCurrent(
        window_ref.device_context,
        window_ref.opengl_context);

    //sanity check
    const ifb_b8 result = (
        chosen_format_descriptor  &&
        pixel_format_is_set       &&
        window_ref.opengl_context &&
        context_active);

    //we're done
    return(result);
}

ifb_internal const ifb_b8 
ifb_win32::window_imgui_init(
    ifb_void) {

    // ifb_macro_panic();

    return(true);
}

/**********************************************************************************/
/* INLINE                                                                         */
/**********************************************************************************/


ifb_internal LRESULT CALLBACK
ifb_win32::window_callback(
    HWND   window_handle,
    UINT   message,
    WPARAM w_param,
    LPARAM l_param) {

    ifb_win32_funcptr_on_wm_message_t wm_message_handler = NULL;

    //get the window
    IFBWin32Window& window_ref = ifb_win32::context_get_window();

    if (window_ref.imgui_context) {
        
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

inline const LRESULT 
ifb_win32::window_on_wm_size(
    const WPARAM w_param, 
    const LPARAM l_param) {

    //get the window
    IFBWin32Window& window_ref = ifb_win32::context_get_window();

    //update width and height
    window_ref.width  = LOWORD(l_param);
    window_ref.height = HIWORD(l_param);

    //we're done
    return(S_OK);   
}

inline const LRESULT
ifb_win32::window_on_wm_move(
    const WPARAM w_param, 
    const LPARAM l_param) {

    //get the window
    IFBWin32Window& window_ref = ifb_win32::context_get_window();

    //update the position
    window_ref.position_x = LOWORD(l_param);
    window_ref.position_y = HIWORD(l_param);

    //we're done
    return(S_OK);
}

inline const LRESULT 
ifb_win32::window_on_wm_quit(
    const WPARAM w_param, 
    const LPARAM l_param) {

    //get the window
    IFBWin32Window& window_ref = ifb_win32::context_get_window();
    
    //set quit received
    window_ref.quit_received = true;

    //we're done
    return(S_OK);
}

inline const LRESULT 
ifb_win32::window_on_wm_destroy(
    const WPARAM w_param, 
    const LPARAM l_param) {

    //post the quit message
    PostQuitMessage(0);

    //we're done
    return(S_OK);
}