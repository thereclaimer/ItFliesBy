#pragma once

#include "ifb-win32.hpp"

/**********************************************************************************/
/* WINDOW API                                                                     */
/**********************************************************************************/

ifb_internal const IFBB8
ifb_win32::window_create(
    const IFBCStr title,
    const IFBU32  width,
    const IFBU32  height,
    const IFBU32  position_x,
    const IFBU32  position_y) {

    IFBB8 result = true;

    //get the window and args
    IFBWin32Window* window_ptr = ifb_win32::context_get_window();
    IFBWin32Args*   args_ptr   = ifb_win32::context_get_args();

    const HINSTANCE h_instance = args_ptr->h_instance; 

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
    window_ptr->window_handle = CreateWindowA(
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

    result &= window_ptr->window_handle != NULL;

    //get the device context
    window_ptr->device_context = GetDC(window_ptr->window_handle);
    result &= window_ptr->device_context != NULL;

    //we're done
    return(result);    
}

ifb_internal const IFBB8 
ifb_win32::window_destroy(
    IFBVoid) {

    PostQuitMessage(0);

    return(true);
}

ifb_internal const IFBB8 
ifb_win32::window_frame_start(
    IFBVoid) {

    //get the window
    IFBWin32Window* window_ptr = ifb_win32::context_get_window();

    //start a new imgui frame if we have a context
    if (window_ptr->imgui_context) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    //go through the messages for the window 
    MSG window_message;
    while(PeekMessage(&window_message,window_ptr->window_handle,0,0,PM_REMOVE)) {

        switch(window_message.message) {

            //key down
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN: {

                const IFBKeyCode keycode = ifb_win32::user_input_keycode((IFBU32)window_message.wParam);

            } break;

            //key up
            case WM_KEYUP:
            case WM_SYSKEYUP: {

                const IFBKeyCode keycode = ifb_win32::user_input_keycode((IFBU32)window_message.wParam);

            } break;

            case WM_QUIT: {
                window_ptr->quit_received = true;
            } break;
        }

        //handle the messages
        TranslateMessage(&window_message);
        DispatchMessage(&window_message);
    }

    return(true);
}

ifb_internal const IFBB8 
ifb_win32::window_frame_render(
    IFBVoid) {

    //get the window
    IFBWin32Window* window_ptr = ifb_win32::context_get_window();

    //if we have an imgui context, render the draw data
    if (window_ptr->imgui_context) {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    //swap the buffers
    SwapBuffers(window_ptr->device_context);

    //we're done
    return(true);
}

ifb_internal const IFBB8 
ifb_win32::window_show(
    IFBVoid) {

    //get the window
    IFBWin32Window* window_ptr = ifb_win32::context_get_window();
    
    //show the window
    const IFBB8  result = (IFBB8)ShowWindow(window_ptr->window_handle,1);
    const IFBU32 error  = GetLastError();

    //we're done
    return(true);
}

ifb_internal IFBGLContext 
ifb_win32::window_opengl_init(
    IFBVoid) {

    //set our preferred format descriptor
    PIXELFORMATDESCRIPTOR preferred_format_descriptor = {0};
    preferred_format_descriptor.nSize      = sizeof(preferred_format_descriptor);
    preferred_format_descriptor.nVersion   = 1;
    preferred_format_descriptor.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    preferred_format_descriptor.iPixelType = PFD_TYPE_RGBA;
    preferred_format_descriptor.cColorBits = 32;

    //get the window
    IFBWin32Window* window_ptr = ifb_win32::context_get_window();
    
    //query for the closest format descriptor
    const IFBS32 chosen_format_descriptor = 
        ChoosePixelFormat(
            window_ptr->device_context,
            &preferred_format_descriptor);

    //set the chosen pixel format
    const IFBB8 pixel_format_is_set = 
        SetPixelFormat(
            window_ptr->device_context,
            chosen_format_descriptor,
            &preferred_format_descriptor);

    //create the opengl context
    window_ptr->opengl_context = wglCreateContext(window_ptr->device_context);

    //make the context current
    const IFBB8 context_active = wglMakeCurrent(
        window_ptr->device_context,
        window_ptr->opengl_context);

    //sanity check
    const IFBB8 result = (
        chosen_format_descriptor  &&
        pixel_format_is_set       &&
        window_ptr->opengl_context &&
        context_active);

    //we're done
    return((IFBGLContext)window_ptr->opengl_context);
}

ifb_internal ImGuiContext*
ifb_win32::window_imgui_init(
    IFBVoid) {

    //sanity check
    IFBB8 result = IMGUI_CHECKVERSION();

    //get the window
    IFBWin32Window* window_ptr = ifb_win32::context_get_window();
        
    //create the imgui context for win32 opengl
    window_ptr->imgui_context = ImGui::CreateContext();
    result &= window_ptr->imgui_context != NULL;
    result &= (IFBB8)ImGui_ImplWin32_Init(window_ptr->window_handle);
    result &= (IFBB8)ImGui_ImplOpenGL3_Init("#version 330");

    //we're done
    return(result ? window_ptr->imgui_context : NULL);
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
    IFBWin32Window* window_ptr = ifb_win32::context_get_window();
    
    if (window_ptr->imgui_context) {
        
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
    IFBWin32Window*         window_ptr        = ifb_win32::context_get_window();
    IFBEngineContextUpdate* engine_update_ptr = ifb_win32::context_get_engine_update(); 

    //update width and height
    const IFBU32 window_width  = LOWORD(l_param); 
    const IFBU32 window_height = HIWORD(l_param); 
    
    window_ptr->width  = window_width;
    window_ptr->height = window_height;

    //update engine window dimensions
    if (engine_update_ptr) {
        IFBDimensions& window_dimensions_ref = engine_update_ptr->window_update.dimensions;
        window_dimensions_ref.width  = window_width;
        window_dimensions_ref.height = window_height;
    }

    //we're done
    return(S_OK);   
}

inline const LRESULT
ifb_win32::window_on_wm_move(
    const WPARAM w_param, 
    const LPARAM l_param) {

    //get the window
    IFBWin32Window*         window_ptr        = ifb_win32::context_get_window();
    IFBEngineContextUpdate* engine_update_ptr = ifb_win32::context_get_engine_update(); 
    
    const IFBU32 window_position_x = LOWORD(l_param); 
    const IFBU32 window_position_y = HIWORD(l_param); 

    //update the position
    window_ptr->position_x = window_position_x;
    window_ptr->position_y = window_position_y;

    //update the engine if we have a context
    if (engine_update_ptr) {
        IFBPosition& window_position_ref = engine_update_ptr->window_update.position;
        window_position_ref.x = window_position_x;
        window_position_ref.y = window_position_y;
    }
    
    //we're done
    return(S_OK);
}

inline const LRESULT 
ifb_win32::window_on_wm_quit(
    const WPARAM w_param, 
    const LPARAM l_param) {

    //TODO(SAM): this event isn't being received for some reason

    //get the window
    IFBWin32Window*         window_ptr        = ifb_win32::context_get_window();
    IFBEngineContextUpdate* engine_update_ptr = ifb_win32::context_get_engine_update(); 

    //set quit received
    window_ptr->quit_received                      = true;
    engine_update_ptr->window_update.quit_received = true;

    //we're done
    return(S_OK);
}

inline const LRESULT 
ifb_win32::window_on_wm_destroy(
    const WPARAM w_param, 
    const LPARAM l_param) {

    //get the window
    IFBWin32Window*         window_ptr        = ifb_win32::context_get_window();
    IFBEngineContextUpdate* engine_update_ptr = ifb_win32::context_get_engine_update(); 

    //set quit received
    window_ptr->quit_received                      = true;
    engine_update_ptr->window_update.quit_received = true;

    //post the quit message
    PostQuitMessage(0);

    //we're done
    return(S_OK);
}