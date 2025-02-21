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
    IFBGraphicsContext*    ptr_context     = ifb_macro_arena_commit_struct_absolute(arena_handle,IFBGraphicsContext);
    IFBGraphicsWindowList* ptr_window_list = ifb_macro_arena_commit_struct_absolute(arena_handle,IFBGraphicsWindowList);
    
    IFBB8 result = true;
    result &= (ptr_context     != NULL);
    result &= (ptr_window_list != NULL);
    if (!result) return(false);

    //initialize the context
    ptr_context->arena_handle = arena_handle;
    ptr_context->color_format = color_format;
    ptr_context->window_list  = ptr_window_list; 

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
    IFBWindowArgs* ptr_window_args) {

    //sanity check
    ifb_macro_assert(ptr_window_args);

    const IFBHNDArena arena = ifb_graphics::context_get_arena();

    ifb_macro_arena_commit_struct_absolute(arena,IFBWindow)
}


/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

const IFBHNDArena
ifb_graphics::context_get_arena(
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