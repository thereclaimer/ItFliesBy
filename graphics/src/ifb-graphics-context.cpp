#pragma once

#include "ifb-graphics-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global IFBGraphicsContext* _ptr_context;

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

const ifb_b8
ifb_graphics::context_create(
    const IFBPlatformApi*            ptr_platform_api,
          IFBStack*                  ptr_stack,
    const IFBGraphicsColorFormat     color_format) {

    //sanity check
    ifb_macro_assert(_ptr_context == NULL);
    ifb_macro_assert(ptr_stack);

    //allocate the context
    const ifb_u32 context_size = ifb_macro_align_size_struct(IFBGraphicsContext);
    _ptr_context = (IFBGraphicsContext*)ifb_stack::push_absolute(ptr_stack,context_size);
    
    //update the context
    _ptr_context->ptr_stack        = ptr_stack;
    _ptr_context->ptr_platform_api = ptr_platform_api;
    _ptr_context->color_format     = color_format;
    _ptr_context->window_list      = {0};
}
    
const ifb_b8
ifb_graphics::context_destroy(
    ifb_void) {

    ifb_stack::reset(_ptr_context->ptr_stack);
    _ptr_context = NULL;
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

IFBStack*
ifb_graphics::context_get_stack(
    ifb_void) {

    ifb_macro_assert(_ptr_context);
    return(_ptr_context->ptr_stack);
}

const IFBPlatformApi*
ifb_graphics::context_get_platform_api(
    ifb_void) {
        
    ifb_macro_assert(_ptr_context);
    return(_ptr_context->ptr_platform_api);
}
    
const IFBGraphicsContextColorFormat
ifb_graphics::context_get_color_format(
    ifb_void) {
        
    ifb_macro_assert(_ptr_context);
    return(_ptr_context->color_format);
}   

IFBGraphicsWindowList&
ifb_graphics::context_get_window_list(
    ifb_void) {
        
    ifb_macro_assert(_ptr_context);
    return(_ptr_context->window_list);
}
