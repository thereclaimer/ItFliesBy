#pragma once

#include "ifb-win32.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

extern IMGUI_IMPL_API LRESULT 
ImGui_ImplWin32_WndProcHandler(
    HWND   hWnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam);

typedef const LRESULT (*IFBWin32WindowMessageHandler) (IFBWin32Window* window);

namespace ifb_win32 {

    //load/store
    IFBVoid         window_assert_store  (IFBWin32Window* window);
    IFBWin32Window* window_assert_load   (const HWND win32_window_handle);

    //callback
    LRESULT CALLBACK
    window_callback(
        HWND   window_handle,
        UINT   message,
        WPARAM w_param,
        LPARAM l_param);

    //message handlers
    const LRESULT   window_on_wm_size    (IFBWin32Window* window);
    const LRESULT   window_on_wm_move    (IFBWin32Window* window);
    const LRESULT   window_on_wm_quit    (IFBWin32Window* window);
    const LRESULT   window_on_wm_destroy (IFBWin32Window* window);

};

/**********************************************************************************/
/* WINDOW API                                                                     */
/**********************************************************************************/

ifb_internal const IFBU32 
ifb_win32::window_size(
    IFBVoid) {

    const IFBU32 size = ifb_macro_align_size_struct(IFBWin32Window);
    return(size);
}

ifb_internal const IFBB8
ifb_win32::window_create(
    IFBWin32Window* window) {

    IFBB8 result = true;
    
    //sanity check
    ifb_macro_assert(window);

    //-------------------------------------------
    // CREATE WINDOW
    //-------------------------------------------

    //window class
    WNDCLASSA window_class = {0};
    window_class.lpfnWndProc   = (WNDPROC)ifb_win32::window_callback;
    window_class.hInstance     = GetModuleHandle(NULL);  
    window_class.lpszClassName = "IFBWin32Window";
    window_class.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    //register the class
    const IFBB8 win32_is_window_class_registered = (RegisterClass(&window_class) != 0);

    //create the window handle
    const HWND win32_handle_window = CreateWindowA(
        window_class.lpszClassName,
        window->title,
        WS_OVERLAPPEDWINDOW,
        window->pos.x,
        window->pos.y,
        window->dims.width,
        window->dims.height,
        NULL,
        NULL,
        window_class.hInstance,
        NULL);

    //get the device context
    const HDC win32_handle_device = GetDC(win32_handle_window);

    //check that we have a window and device context
    result &= win32_is_window_class_registered;
    result &= (win32_handle_window != NULL);
    result &= (win32_handle_device != NULL);
    if (!result) return(false);

    //-------------------------------------------
    // INITIALIZE OPENGL
    //-------------------------------------------

    //set our preferred format descriptor
    PIXELFORMATDESCRIPTOR preferred_format_descriptor = {0};
    preferred_format_descriptor.nSize      = sizeof(preferred_format_descriptor);
    preferred_format_descriptor.nVersion   = 1;
    preferred_format_descriptor.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    preferred_format_descriptor.iPixelType = PFD_TYPE_RGBA;
    preferred_format_descriptor.cColorBits = 32;
    
    //set the pixel format
    const IFBS32 chosen_format_descriptor = ChoosePixelFormat (win32_handle_device, &preferred_format_descriptor);
    const IFBB8  pixel_format_is_set      =  SetPixelFormat   (win32_handle_device, chosen_format_descriptor,&preferred_format_descriptor);

    //create the opengl context and make it current
    const HGLRC win32_handle_opengl   = wglCreateContext (win32_handle_device);
    const IFBB8 opengl_context_active = wglMakeCurrent   (win32_handle_device,win32_handle_opengl);

    //make sure that our opengl context is active
    result &= pixel_format_is_set;
    result &= (win32_handle_opengl != NULL);
    result &= opengl_context_active; 
    if (!result) return(false);

    //-------------------------------------------
    // INITIALIZE IMGUI
    //-------------------------------------------
    
    //create the context
    ImGuiContext* imgui_context = IMGUI_CHECKVERSION() ? ImGui::CreateContext() : NULL;  
    result &= (imgui_context != NULL);
    
    //initialize win32/opengl methods for imgui
    if (result) {
        result &= (IFBB8)ImGui_ImplWin32_Init(win32_handle_window);
        result &= (IFBB8)ImGui_ImplOpenGL3_Init("#version 330");
    }

    //make sure we have an imgui context
    if (!result) return(false);

    //set the properties we initialized
    window->win32.handles.window     = win32_handle_window;
    window->win32.handles.device     = win32_handle_device;
    window->graphics_contexts.opengl = win32_handle_opengl;
    window->graphics_contexts.imgui  = imgui_context; 

    //store the window
    ifb_win32::window_assert_store(window);

    //we're done
    return(result);    
}

ifb_internal const IFBB8 
ifb_win32::window_destroy(
    IFBWin32Window* window) {

    PostQuitMessage(0);

    return(true);
}

ifb_internal const IFBB8 
ifb_win32::window_process_events(
    IFBWin32Window* window) {

    //start a new imgui frame if we have a context
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //go through the messages for the window 
    MSG window_message;
    while(PeekMessage(&window_message,window->win32.handles.window,0,0,PM_REMOVE)) {

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
                window->flags |= IFBPlatformWindowFlags_Closed;
            } break;
        }

        //handle the messages
        TranslateMessage(&window_message);
        DispatchMessage(&window_message);
    }

    return(true);
}

ifb_internal const IFBB8 
ifb_win32::window_swap_buffers(
    IFBWin32Window* window) {

    //render imgui
    //TODO: may move this to graphics library
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //swap the buffers
    SwapBuffers(window->win32.handles.device);

    //we're done
    return(true);
}

ifb_internal const IFBB8 
ifb_win32::window_show(
    IFBWin32Window* window) {
    
    //show the window
    const IFBB8  result = (IFBB8)ShowWindow(window->win32.handles.window,1);
    const IFBU32 error  = GetLastError();

    //set the handle
    window->flags |= IFBPlatformWindowFlags_Visible;

    //we're done
    return(true);
}

/**********************************************************************************/
/* STORE AND LOAD                                                                 */
/**********************************************************************************/

inline IFBVoid
ifb_win32::window_assert_store(
    IFBWin32Window* window) {

    //window
    ifb_macro_assert(window);

    //properties
    IFBB8 is_valid = true;
    is_valid &= (window->title                    != NULL);
    is_valid &= (window->graphics_contexts.imgui  != NULL);
    is_valid &= (window->graphics_contexts.opengl != NULL);
    is_valid &= (window->win32.handles.window     != NULL);
    is_valid &= (window->win32.handles.device     != NULL);
    ifb_macro_assert(is_valid);

    //store the window
    is_valid &= SetWindowLongPtr(
        window->win32.handles.window,
        GWLP_USERDATA,
        (LONG_PTR)window);
    ifb_macro_assert(is_valid);
}

inline IFBWin32Window*
ifb_win32::window_assert_load(
    const HWND win32_window_handle) {

    //handle
    ifb_macro_assert(win32_window_handle);

    //window
    IFBWin32Window* window = (IFBWin32Window*)GetWindowLongPtr(win32_window_handle,GWLP_USERDATA);
    ifb_macro_assert(window);

    //properties
    IFBB8 is_valid = true;
    is_valid &= (window->title                    != NULL);
    is_valid &= (window->graphics_contexts.imgui  != NULL);
    is_valid &= (window->graphics_contexts.opengl != NULL);
    is_valid &= (window->win32.handles.window     == win32_window_handle);
    is_valid &= (window->win32.handles.device     != NULL);
    ifb_macro_assert(is_valid);

    //we're done
    return(window);
}

/**********************************************************************************/
/* WINDOW CALLBACK                                                                */
/**********************************************************************************/

ifb_internal LRESULT CALLBACK
ifb_win32::window_callback(
    HWND   window_handle,
    UINT   message,
    WPARAM w_param,
    LPARAM l_param) {

    LRESULT message_handler_result = S_FALSE;

    //get the window
    IFBWin32Window* window = ifb_win32::window_assert_load(window_handle);
    
    //see if imgui needs to process this event
    message_handler_result = ImGui_ImplWin32_WndProcHandler(
        window_handle,message,w_param,l_param);

    //if imgui processed the event, we're done
    if (message_handler_result) return(S_OK);

    //get the messasge handler
    IFBWin32WindowMessageHandler window_message_handler = NULL;
    switch (message) {

        case WM_SIZE:    window_message_handler = ifb_win32::window_on_wm_size;    break; 
        case WM_MOVE:    window_message_handler = ifb_win32::window_on_wm_move;    break; 
        case WM_QUIT:    window_message_handler = ifb_win32::window_on_wm_quit;    break; 
        case WM_DESTROY: window_message_handler = ifb_win32::window_on_wm_destroy; break; 
    }

    //if we have a message handler
    //get the result
    message_handler_result = (window_message_handler != NULL)
            ? window_message_handler(window) 
            : S_FALSE; 
            
    //if nothing else, get the default window result for the event
    if (!message_handler_result) {
        message_handler_result = DefWindowProc(
            window_handle,message,w_param,l_param);
    } 

    //we're done
    return(message_handler_result);
}

/**********************************************************************************/
/* MESSAGE HANDLERS                                                               */
/**********************************************************************************/

inline const LRESULT 
ifb_win32::window_on_wm_size(
    IFBWin32Window* window) {

    //get parameters
    const IFBU32 window_width  = LOWORD(window->win32.message_params.l); 
    const IFBU32 window_height = HIWORD(window->win32.message_params.l); 
    
    //update dimensions
    window->dims.width  = window_width;
    window->dims.height = window_height;

    //set the flag
    window->flags |= IFBPlatformWindowFlags_Resized;

    //we're done
    return(S_OK);   
}

inline const LRESULT
ifb_win32::window_on_wm_move(
    IFBWin32Window* window) {

    //get the params
    const IFBU32 window_position_x = LOWORD(window->win32.message_params.l); 
    const IFBU32 window_position_y = HIWORD(window->win32.message_params.l); 

    //update the position
    window->pos.x = window_position_x;
    window->pos.y = window_position_y;

    //set the flag
    window->flags |= IFBPlatformWindowFlags_Moved;

    //we're done
    return(S_OK);
}

inline const LRESULT 
ifb_win32::window_on_wm_quit(
    IFBWin32Window* window) {

    //set the flag
    window->flags |= IFBPlatformWindowFlags_Closed;

    //we're done
    return(S_OK);
}

inline const LRESULT 
ifb_win32::window_on_wm_destroy(
    IFBWin32Window* window) {

    //set the flag
    window->flags |= IFBPlatformWindowFlags_Closed;

    //post the quit message
    PostQuitMessage(0);

    //we're done
    return(S_OK);
}