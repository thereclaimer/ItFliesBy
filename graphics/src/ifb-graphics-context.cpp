#pragma once

#include "ifb-graphics-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global IFBGraphicsContext* _ptr_context;

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

const IFBB8
ifb_graphics::context_create(
    const IFBHNDArena    arena_handle,
    const IFBColorFormat color_format) {

    //sanity check
    if (!ifb_memory_macro_handle_valid(arena_handle)) return(false);
    
    //allocate the struct 
    IFBGraphicsContext* ptr_context = ifb_macro_arena_commit_struct_absolute(arena_handle,IFBGraphicsContext);
    
    IFBB8 result = true;
    result &= (ptr_context != NULL);
    if (!result) return(false);

    //initialize the context
    ptr_context->arena_handle = arena_handle;
    ptr_context->color_format = color_format;

    //set the context pointer
    _ptr_context = ptr_context;

    //we're done
    return(true);
}

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

const IFBHNDWindow
ifb_graphics::context_commit_window(
    const IFBWindowArgs* ptr_window_args) {

    IFBHNDWindow window_handle;
    window_handle.pointer = 0;

    //sanity check
    ifb_macro_assert(ptr_window_args);
    ifb_macro_assert(ptr_window_args->title);

    //commit the window
    const IFBHNDArena arena       = ifb_graphics::context_get_arena_handle();
    const IFBU32      window_size = ifb_macro_align_size_struct(IFBWindow);
    const IFBU32      offset      = ifb_memory::arena_commit_bytes_relative(arena,window_size);

    //if that failed, we're done
    if (!offset) return(window_handle);

    //get the pointer
    IFBWindow* ptr_window = (IFBWindow*)ifb_memory::arena_get_pointer(arena,offset);
    ifb_macro_assert(ptr_window);

    //initialize create the window on the platform side
    const IFBB8 window_created = ifb_platform::window_create(
        ptr_window_args->title,
        ptr_window_args->dimensions.width,
        ptr_window_args->dimensions.height,
        ptr_window_args->position.x,
        ptr_window_args->position.y);

    //add contexts for rendering
    IFBGLContext  context_gl    = ifb_platform::window_opengl_init();
    ImGuiContext* context_imgui = ifb_platform::window_imgui_init();

    //the window is initialiized IF...
    IFBB8 window_initialized = true;
    window_initialized &= window_created;           // ...the window is created AND
    window_initialized &= (context_gl    != NULL);  // ...we have a GL context AND
    window_initialized &= (context_imgui != NULL);  // ...we have an ImGui context
    if (!window_initialized) return(window_handle); // if that failed, we're done

    //update the window
    ptr_window->platform_contexts.opengl = context_gl; 
    ptr_window->platform_contexts.imgui  = context_imgui; 
    ptr_window->dimensions               = ptr_window_args->dimensions;
    ptr_window->position                 = ptr_window_args->position;
    ptr_window->handle                   = window_handle;

    //copy the window title
    const IFBChar* ptr_window_title = ptr_window_args->title;
    for (
        IFBU32 char_index = 0;
               char_index < IFB_WINDOW_TITLE_LENGTH_MAX;
             ++char_index) {
        
        //get the char
        const IFBChar char_current = ptr_window_title[char_index];
        if (char_current == '\0') break;

        //update the title
        ptr_window->title.c_str[char_index] = char_current;
    }

    //update the context
    _ptr_context->window = ptr_window;

    //return the handle
    window_handle.pointer = (IFBPtr)ptr_window;
    return(window_handle);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

const IFBHNDArena
ifb_graphics::context_get_arena_handle(
    IFBVoid) {

    ifb_macro_assert(_ptr_context);
    return(_ptr_context->arena_handle);
}

const IFBColorFormat
ifb_graphics::context_get_color_format(
    IFBVoid) {
        
    ifb_macro_assert(_ptr_context);
    return(_ptr_context->color_format);
}

IFBWindow*
ifb_graphics::context_get_window(
    const IFBHNDWindow window_handle) {

    ifb_macro_assert(_ptr_context);
    IFBWindow* ptr_window = (IFBWindow*)window_handle.pointer;
    ifb_macro_assert(ptr_window);
    return(ptr_window);
}