#pragma once

#include "ifb-win32.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global IFBWin32Context* _ptr_context; 

namespace ifb_win32 {

    const IFBHNDArena context_create_engine (IFBVoid);

    IFBWin32Context*
    context_create_win32(
        const IFBHNDArena win32_arena,
        const HINSTANCE   h_instance,
        const HINSTANCE   h_prev_instance,
        const PWSTR       p_cmd_line,
        const int         n_cmd_show);
};

/**********************************************************************************/
/* WIN32 MAIN                                                                     */
/**********************************************************************************/

int WINAPI 
wWinMain(
    HINSTANCE h_instance,
    HINSTANCE h_prev_instance,
    PWSTR     p_cmd_line,
    int       n_cmd_show) {

    //create the engine context
    const IFBHNDArena win32_arena = ifb_win32::context_engine_create();

    //create the win32 context
    _ptr_context = ifb_win32::context_create_win32(win32_arena);



    running &= ifb_engine::context_startup();

    //if we're running, so far so good
    IFBB8 result = running;

    //main loop
    while(running) {

        //render the next frame
        running = ifb_engine::context_render_frame();
    }

    //shutdown and destroy the engine context
    result &= ifb_engine::context_shutdown();
    result &= ifb_engine::context_destroy();

    //done
    return(result ? S_OK : S_FALSE);
}

/**********************************************************************************/
/* WIN32 CONTEXT                                                                  */
/**********************************************************************************/

inline const IFBHNDArena
ifb_win32::context_create_engine(
    IFBVoid) {

    //initialize the platform api
    IFBPlatformApi& platform_api_ref = ifb_win32::context_get_platform_api();
    ifb_win32::context_initialize_platform_api(platform_api_ref);

    //engine memory
    const IFBU64      engine_memory_reserved_size = ifb_macro_size_gigabytes(4);
    const IFBU32      engine_memory_stack_size    = ifb_macro_size_kilobytes(512);
    ifb_local IFBByte engine_memory_stack_buffer[engine_memory_stack_size];

    //create the engine context
    const IFBHNDArena win32_arena = ifb_engine::context_create(
        &platform_api_ref,
        engine_memory_stack_buffer,
        engine_memory_stack_size,
        engine_memory_reserved_size);

    //sanity check
    ifb_macro_assert(ifb_memory_macro_handle_valid(win32_arena));

    //we're done
    return(win32_arena);
}

inline IFBWin32Context*
ifb_win32::context_create_win32(
    const IFBHNDArena win32_arena,
    const HINSTANCE   h_instance,
    const HINSTANCE   h_prev_instance,
    const PWSTR       p_cmd_line,
    const int         n_cmd_show) {
    
    //calculate sizes
    const IFBU32     win32_context_size = ifb_macro_align_size_struct(IFBWin32Context);
    const IFBU32     win32_handles_size = ifb_macro_align_size_struct(IFBWin32Handles);
    
    //commit context structures
    IFBWin32Context* win32_context_ptr  = (IFBWin32Context*)ifb_memory::arena_commit_bytes_absolute(win32_arena, win32_context_size);
    IFBWin32Handles* win32_handles_ptr  = (IFBWin32Handles*)ifb_memory::arena_commit_bytes_absolute(win32_arena, win32_handles_size);

    //intialize memory
    IFBWin32Memory& memory_ref = win32_context_ptr->memory;
    memory_ref.arena_handle = win32_arena;
    memory_ref.arena_start = ifb_memory::

    //sanity check
    ifb_macro_assert(win32_context_ptr);
    ifb_macro_assert(win32_handles_ptr);
    

    
    win32_context_ptr->ptr_handles = win32_handles_ptr;
}

inline IFBVoid 
ifb_win32::context_initialize_platform_api(
    IFBPlatformApi& platform_api_ref) {

    //system
    platform_api_ref.system.page_size              = ifb_win32::system_page_size;
    platform_api_ref.system.allocation_granularity = ifb_win32::system_allocation_granularity;
    platform_api_ref.system.time_ms                = ifb_win32::system_time_ms;
    platform_api_ref.system.sleep                  = ifb_win32::system_sleep;

    //memory    
    platform_api_ref.memory.reserve                = ifb_win32::memory_reserve;
    platform_api_ref.memory.release                = ifb_win32::memory_release;
    platform_api_ref.memory.commit                 = ifb_win32::memory_commit;

    //window    
    platform_api_ref.window.create                 = ifb_win32::window_create;
    platform_api_ref.window.destroy                = ifb_win32::window_destroy;
    platform_api_ref.window.frame_start            = ifb_win32::window_frame_start;
    platform_api_ref.window.frame_render           = ifb_win32::window_frame_render;
    platform_api_ref.window.show                   = ifb_win32::window_show;
    platform_api_ref.window.opengl_init            = ifb_win32::window_opengl_init;
    platform_api_ref.window.imgui_init             = ifb_win32::window_imgui_init;

    //monitor
    platform_api_ref.monitor.count                 = ifb_win32::monitor_count;
    // platform_api_ref.monitor.info                  = ifb_win32::monitor_info;
}