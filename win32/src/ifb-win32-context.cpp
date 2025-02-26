#pragma once

#include "ifb-win32.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global IFBWin32Context* _ptr_context; 

/**********************************************************************************/
/* WIN32 CONTEXT                                                                  */
/**********************************************************************************/

inline const IFBB8
ifb_win32::context_create(
    const IFBPlatformApi& platform_api_ref,
    const IFBWin32Args&   win32_args_ref) {

    //engine memory
    const IFBU64      reservation_gb = 4UL;
    const IFBU64      engine_memory_reserved_size = ifb_macro_size_gigabytes(reservation_gb);
    const IFBU32      engine_memory_stack_size    = ifb_macro_size_kilobytes(512);
    ifb_local IFBByte engine_memory_stack_buffer[engine_memory_stack_size];

    //create the engine context
    const IFBHNDEngineArena win32_arena = ifb_engine::context_create(
        &platform_api_ref,
        engine_memory_stack_buffer,
        engine_memory_stack_size,
        engine_memory_reserved_size);

    //calculate sizes
    const IFBU32 win32_context_size = ifb_macro_align_size_struct(IFBWin32Context);
    const IFBU32 win32_memory_size  = ifb_macro_align_size_struct(IFBWin32Memory);
    
    //commit context structures
    IFBWin32Context* win32_context_ptr = (IFBWin32Context*)ifb_engine::arena_commit_bytes_absolute(win32_arena, win32_context_size);
    IFBWin32Memory*  win32_memory_ptr  =  (IFBWin32Memory*)ifb_engine::arena_commit_bytes_absolute(win32_arena, win32_memory_size);

    //sanity check
    ifb_macro_assert(win32_context_ptr);
    ifb_macro_assert(win32_memory_ptr);

    //calculate handle sizes
    const IFBU32 size_args   = ifb_macro_align_size_struct(IFBWin32Args);
    const IFBU32 size_window = ifb_macro_align_size_struct(IFBWin32Window);

    //intialize memory
    win32_memory_ptr->arena_handle = win32_arena;
    win32_memory_ptr->win32_handles.args   = ifb_engine::arena_commit_bytes_relative(win32_arena,size_args);
    win32_memory_ptr->win32_handles.window = ifb_engine::arena_commit_bytes_relative(win32_arena,size_window);

    //update the context
    win32_context_ptr->ptr_memory = win32_memory_ptr;
    _ptr_context = win32_context_ptr;

    //set the args
    IFBWin32Args* args = ifb_win32::context_get_args();
    args->h_instance      = win32_args_ref.h_instance;
    args->h_prev_instance = win32_args_ref.h_prev_instance;
    args->p_cmd_line      = win32_args_ref.p_cmd_line;
    args->n_cmd_show      = win32_args_ref.n_cmd_show;

    //we're done
    return(true);
}

inline const IFBB8
ifb_win32::context_main_loop(
    IFBVoid) {

    IFBB8 result = true;

    //start the engine context
    _ptr_context->ptr_engine_update = ifb_engine::context_startup();
    if (!_ptr_context->ptr_engine_update) return(false);

    //main loop
    IFBB8 running = true;
    while(running) {

        //render the next frame
        running = ifb_engine::context_render_frame(
            _ptr_context->ptr_engine_update);
    }

    return(true);
}

inline const IFBB8
ifb_win32::context_destroy(
    IFBVoid) {

    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBWin32Memory*
ifb_win32::context_get_memory(
    IFBVoid) {

    ifb_macro_assert(_ptr_context);
    return(_ptr_context->ptr_memory);
}

inline IFBEngineContextUpdate*
ifb_win32::context_get_engine_update(
    IFBVoid) {
        
    ifb_macro_assert(_ptr_context);
    return(_ptr_context->ptr_engine_update);
}

inline IFBWin32Args*
ifb_win32::context_get_args(
    IFBVoid) {

    IFBWin32Memory* ptr_memory = ifb_win32::context_get_memory();
    
    IFBWin32Args* ptr_args = (IFBWin32Args*)ifb_engine::arena_get_pointer(
        ptr_memory->arena_handle,
        ptr_memory->win32_handles.args);

    ifb_macro_assert(ptr_args);
    
    return(ptr_args);
}

inline IFBWin32Window*
ifb_win32::context_get_window(
    IFBVoid) {
        
    IFBWin32Memory* ptr_memory = ifb_win32::context_get_memory();

    IFBWin32Window* ptr_window = (IFBWin32Window*)ifb_engine::arena_get_pointer(
        ptr_memory->arena_handle,
        ptr_memory->win32_handles.window);

    ifb_macro_assert(ptr_window);

    return(ptr_window);
}