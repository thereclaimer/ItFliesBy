#pragma once

#include "ifb-win32.hpp"

int WINAPI 
wWinMain(
    HINSTANCE h_instance,
    HINSTANCE h_prev_instance,
    PWSTR     p_cmd_line,
    int       n_cmd_show) {
 
    //reset the win32 context
    ifb_win32::context_reset();

    //set the args
    IFBWin32Args& args_ref = ifb_win32::context_get_args();
    args_ref.h_instance      = h_instance; 
    args_ref.h_prev_instance = h_prev_instance; 
    args_ref.p_cmd_line      = p_cmd_line; 
    args_ref.n_cmd_show      = n_cmd_show; 

    //initialize the platform api
    IFBPlatformApi& platform_api_ref = ifb_win32::context_get_platform_api();
    ifb_win32::context_initialize_platform_api(platform_api_ref);

    //create the engine context and startup
    ifb_b8 running = true;
    running &= ifb_engine::context_create(platform_api_ref);
    running &= ifb_engine::context_startup();

    //if we're running, so far so good
    ifb_b8 result = running;

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

inline ifb_void 
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
    platform_api_ref.monitor.info                  = ifb_win32::monitor_info;
}