#pragma once

#include "ifb-win32.hpp"

#include "ifb-win32-context-init.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global IFBWin32Context* _ptr_context; 

/**********************************************************************************/
/* WIN32 CONTEXT                                                                  */
/**********************************************************************************/

inline const IFBB8
ifb_win32::context_create(
    const IFBWin32Args* win32_args) {

    //context init struct
    IFBWin32ContextInit win32_init;
    win32_init.result     = true;
    win32_init.win32_args = (IFBWin32Args*)win32_args;
    win32_init.context    = NULL;
    win32_init.platform   = {0};
    win32_init.memory     = NULL;

    //create and initialize the context
    ifb_win32::context_init_step_0_validate_args                (win32_init);
    ifb_win32::context_init_step_1_create_memory_context        (win32_init);
    ifb_win32::context_init_step_2_stack_allocate_win32_context (win32_init);
    ifb_win32::context_init_step_3_set_platform_api             (win32_init);
    ifb_win32::context_init_step_4_create_engine_context        (win32_init);

    //check the result
    const IFBB8 result = win32_init.result ? true : false;

    //we're done
    return(result);
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

inline IFBEngineContextUpdate*
ifb_win32::context_get_engine_update(
    IFBVoid) {
        
    ifb_macro_assert(_ptr_context);
    return(_ptr_context->ptr_engine_update);
}

inline IFBWin32Args*
ifb_win32::context_get_args(
    IFBVoid) {

    ifb_macro_assert(_ptr_context);

    IFBWin32Args* args = _ptr_context->ptr_win32_args;
    ifb_macro_assert(args);

    return(args);
}

inline IFBWin32Window*
ifb_win32::context_get_window(
    IFBVoid) {

    ifb_macro_assert(_ptr_context);

    IFBWin32Window* ptr_window = _ptr_context->ptr_win32_window; 
    ifb_macro_assert(ptr_window);

    return(ptr_window);
}