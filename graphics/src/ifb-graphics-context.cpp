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
ifb_graphics::context_reserve_and_initialize(
    const IFBHNDMemoryArenaLinear linear_arena_handle,
    const IFBPlatformApi*         ptr_platform_api,
    const IFBColorFormat          color_format) {

    //sanity check
    ifb_macro_assert(_ptr_context == NULL);
    ifb_macro_assert(ptr_platform_api);
    ifb_macro_assert(linear_arena_handle.offset);

    //allocate the context
    const IFBU32 context_size = ifb_macro_align_size_struct(IFBGraphicsContext);
    _ptr_context = (IFBGraphicsContext*)ifb_memory::linear_arena_reserve_bytes_absolute(
        linear_arena_handle,
        context_size);

    //if that failed, we're done
    if (!_ptr_context) return(false);

    //initialize the context
    _ptr_context->memory.linear_arena_handle = linear_arena_handle;
    _ptr_context->memory.offsets             = {0};
    _ptr_context->ptr_platform_api           = (IFBPlatformApi*)ptr_platform_api;
    _ptr_context->color_format               = color_format;

    //commit the window lists
    if (!ifb_graphics::memory_commit_window_lists()) {
        ifb_macro_panic();
    }

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

IFBGraphicsMemory&
ifb_graphics::context_get_memory(
    IFBVoid) {

    ifb_macro_assert(_ptr_context);
    return(_ptr_context->memory);
}

const IFBPlatformApi*
ifb_graphics::context_get_platform_api(
    IFBVoid) {
        
    ifb_macro_assert(_ptr_context);
    return(_ptr_context->ptr_platform_api);
}

const IFBColorFormat
ifb_graphics::context_get_color_format(
    IFBVoid) {
    
    ifb_macro_assert(_ptr_context);
    return(_ptr_context->color_format);
}