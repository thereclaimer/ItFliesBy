#pragma once

#include "ifb-platform-win32-internal.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

extern IMGUI_IMPL_API LRESULT 
ImGui_ImplWin32_WndProcHandler(
    HWND   hWnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam);

typedef const LRESULT (*IFBWin32OnWmMessage)(IFBWin32Window* win32_window);

namespace ifb_platform {

    IFBWin32Window* win32_window_load_and_assert_valid (const HWND win32_window_handle);
};

/**********************************************************************************/
/* WIN32 WINDOW                                                                   */
/**********************************************************************************/

ifb_internal const IFBU32
ifb_platform::win32_window_size(
    IFBVoid) {

    const IFBU32 context_size = ifb_macro_align_size_struct(IFBWin32Window);
    return(context_size);
}

ifb_internal const IFBB8
ifb_platform::win32_window_create(
    IFBWin32Window* win32_window) {

    //sanity check
    ifb_macro_assert(win32_window);

    //------------------------------
    // CREATE WINDOW
    //------------------------------

    //window class
    WNDCLASSA window_class = {0};
    window_class.lpfnWndProc   = (WNDPROC)ifb_platform::win32_window_callback;
    window_class.hInstance     = GetModuleHandle(NULL);
    window_class.lpszClassName = "IFBWin32Window";
    window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    //register class
    const ATOM window_class_registered = RegisterClass(&window_class);

    //create the window handle
    const HWND window_handle = CreateWindowA(
        window_class.lpszClassName,
        win32_window->title,
        WS_OVERLAPPEDWINDOW,
        win32_window->pos.x,
        win32_window->pos.y,
        win32_window->dims.width,
        win32_window->dims.height,
        NULL,
        NULL,
        window_class.hInstance,
        NULL);

    //get the device context
    const HDC window_device_context = GetDC(window_handle);

    //check to make sure everything is valid
    IFBB8 result = true;
    result &= (window_class_registered != 0);
    result &= (window_handle           != NULL);
    result &= (window_device_context   != NULL);
    if (!result) return(false);

    //------------------------------
    // INITIALIZE OPENGL
    //------------------------------

    //set our preferred format descriptor
    PIXELFORMATDESCRIPTOR preferred_pixel_format_descriptor = {0};
    preferred_pixel_format_descriptor.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
    preferred_pixel_format_descriptor.nVersion   = 1;
    preferred_pixel_format_descriptor.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    preferred_pixel_format_descriptor.iPixelType = PFD_TYPE_RGBA;
    preferred_pixel_format_descriptor.cColorBits = 32;
    
    // query for the closest format descriptor
    // then set the chosen pixel format
    const IFBS32 pixel_format_descriptor    = ChoosePixelFormat (window_device_context, &preferred_pixel_format_descriptor);
    const IFBB8  pixel_format_is_set        = SetPixelFormat    (window_device_context, pixel_format_descriptor,&preferred_pixel_format_descriptor);

    //create the opengl context and make it current
    const HGLRC win32_opengl_context        = wglCreateContext  (window_device_context);
    const IFBB8 win32_opengl_context_active = wglMakeCurrent    (window_device_context,win32_opengl_context);

    //sanity check
    result &= (pixel_format_is_set);
    result &= (win32_opengl_context        != NULL);
    result &= (win32_opengl_context_active);
    if (!result) return(false);

    //------------------------------
    // INITIALIZE IMGUI
    //------------------------------
    
    // check the version before initialization
    // the program will crash if we try to initialize with an invalid version
    result &= (IMGUI_CHECKVERSION() == true);
    if (!result) return(false);

    // create the imgui context for win32 opengl
    ImGuiContext* win32_imgui_context = ImGui::CreateContext();
    result &= (win32_imgui_context != NULL);
    result &= (IFBB8)ImGui_ImplWin32_Init(window_handle);
    result &= (IFBB8)ImGui_ImplOpenGL3_Init("#version 330");
    if (!result) return(false);

    //------------------------------
    // FINALIZE WINDOW
    //------------------------------ 


    //set handles and context pointers
    win32_window->contexts.imgui  = win32_imgui_context;
    win32_window->contexts.opengl = win32_opengl_context;
    win32_window->handles.window  = window_handle;
    win32_window->handles.device  = window_device_context;
    
    //last check
    result &= (win32_window->contexts.imgui  != NULL); 
    result &= (win32_window->contexts.opengl != NULL);
    result &= (win32_window->handles.window  != NULL);
    result &= (win32_window->handles.device  != NULL);
    
    result &= (SetWindowLongPtr(window_handle,GWLP_USERDATA,(LONG_PTR)win32_window) != 0);

    //store the window
    //we have no way of retrieving it for message handling
    //if this doesn't work
    ifb_macro_assert(result);

    //we're done
    return(true);    
}

ifb_internal const IFBB8 
ifb_platform::win32_window_destroy(
    IFBWin32Window* win32_window) {

    PostQuitMessage(0);

    return(true);
}

ifb_internal const IFBB8 
ifb_platform::win32_window_frame_start(
    IFBWin32Window* win32_window) {

    //start a new imgui frame if we have a context
    if (win32_window->contexts.imgui) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    //go through the messages for the window 
    MSG window_message;
    while(PeekMessage(&window_message,win32_window->handles.window,0,0,PM_REMOVE)) {

        switch(window_message.message) {

            //key down
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN: {

                // const IFBKeyCode keycode = ifb_win32::user_input_keycode((IFBU32)window_message.wParam);

            } break;

            //key up
            case WM_KEYUP:
            case WM_SYSKEYUP: {

                // const IFBKeyCode keycode = ifb_win32::user_input_keycode((IFBU32)window_message.wParam);

            } break;
        }

        //handle the messages
        TranslateMessage(&window_message);
        DispatchMessage(&window_message);
    }

    return(true);
}

ifb_internal const IFBB8 
ifb_platform::win32_window_frame_render(
    IFBWin32Window* win32_window) {

    //if we have an imgui context, render the draw data
    if (win32_window->contexts.imgui) {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    //swap the buffers
    SwapBuffers(win32_window->handles.device);

    //we're done
    return(true);
}

ifb_internal const IFBB8 
ifb_platform::win32_window_show(
    IFBWin32Window* win32_window) {
    
    //show the window
    const IFBB8 result = (IFBB8)ShowWindow(win32_window->handles.window,1);

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBWin32Window*
ifb_platform::win32_window_load_and_assert_valid(
    const HWND window_handle) {

    //load the context
    IFBWin32Window* win32_window = (IFBWin32Window*)GetWindowLongPtr(
        window_handle,
        GWLP_USERDATA);

    //validate pointers / win32 window handle
    IFBB8 is_valid = true; 
    is_valid &= (win32_window != NULL);
    is_valid &= (win32_window->contexts.imgui  != NULL);
    is_valid &= (win32_window->contexts.opengl != NULL);
    is_valid &= (win32_window->handles.window  != NULL);
    is_valid &= (win32_window->handles.device  != NULL);    
    is_valid &= (win32_window->handles.window == window_handle);

    //assert valid
    ifb_macro_assert(is_valid);

    //we're done
    return(win32_window);    
}

ifb_internal LRESULT CALLBACK
ifb_platform::win32_window_callback(
    HWND   window_handle,
    UINT   message,
    WPARAM w_param,
    LPARAM l_param) {

    //get the window
    IFBWin32Window* window = ifb_platform::win32_window_load_and_assert_valid(window_handle);
    
    //give imgui a chance to handle this event
    const LRESULT imgui_result = ImGui_ImplWin32_WndProcHandler(
                window_handle,
                message,
                w_param,
                l_param);

    //if imgui handled it, we're done
    if (imgui_result) {
        return(S_OK);
    }

    //store the params
    window->message_params.w = w_param;
    window->message_params.l = l_param;

    //select the message handler
    IFBWin32OnWmMessage wm_message_handler = NULL;
    switch (message) {

        case WM_SIZE:    wm_message_handler = ifb_platform::win32_window_on_wm_size;    break; 
        case WM_MOVE:    wm_message_handler = ifb_platform::win32_window_on_wm_move;    break; 
        case WM_DESTROY: wm_message_handler = ifb_platform::win32_window_on_wm_destroy; break; 
    }

    //handle the message
    const LRESULT wm_message_result = wm_message_handler(window);

    //if that wasn't handled, just get the windows default
    const LRESULT result = wm_message_result 
        ? wm_message_result
        : DefWindowProc(window_handle,message,w_param,l_param);

    return(result);
}

inline const LRESULT 
ifb_platform::win32_window_on_wm_size(
    IFBWin32Window* window) {

    //update width and height
    const IFBU32 window_width  = LOWORD(window->message_params.l); 
    const IFBU32 window_height = HIWORD(window->message_params.l); 
    
    window->dims.width  = window_width;
    window->dims.height = window_height;

    //we're done
    return(S_OK);   
}

inline const LRESULT
ifb_platform::win32_window_on_wm_move(
    IFBWin32Window* window) {
    
    //update the position
    const IFBU32 window_position_x = LOWORD(window->message_params.l); 
    const IFBU32 window_position_y = HIWORD(window->message_params.l); 

    window->pos.x = window_position_x;
    window->pos.y = window_position_y;

    //we're done
    return(S_OK);
}

// inline const LRESULT 
// ifb_platform::win32_window_on_wm_quit(
//     IFBWin32Window* window) {

//     //TODO(SAM): this event isn't being received for some reason

//     //we're done
//     return(S_OK);
// }

inline const LRESULT 
ifb_platform::win32_window_on_wm_destroy(
    IFBWin32Window* window) {

    //post the quit message
    PostQuitMessage(0);

    //we're done
    return(S_OK);
}

