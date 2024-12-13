#pragma once

#include "ifb-win32.hpp"

int WINAPI 
wWinMain(
    HINSTANCE h_instance,
    HINSTANCE h_prev_instance,
    PWSTR     p_cmd_line,
    int       n_cmd_show) {
 
    //set the args
    ifb_win32::context_args_set_values(
        h_instance,
        h_prev_instance,
        p_cmd_line,
        n_cmd_show);

    //initialize the platform api
    IFBPlatformApi engine_platform_api;
    ifb_win32::system_api_initialize (engine_platform_api.system);
    ifb_win32::memory_api_initialize (engine_platform_api.memory);
    ifb_win32::window_api_initialize (engine_platform_api.window);
    ifb_win32::monitor_api_initialize(engine_platform_api.monitor);

    //create the engine context
    if (!ifb_engine::context_create(engine_platform_api)) {
        return(S_FALSE);
    } 

    //done
    return(S_OK);
}