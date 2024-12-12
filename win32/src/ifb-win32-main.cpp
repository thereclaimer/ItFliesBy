#pragma once

#include "ifb-win32.hpp"

int WINAPI 
wWinMain(
    HINSTANCE h_instance,
    HINSTANCE h_prev_instance,
    PWSTR     p_cmd_line,
    int       n_cmd_show) {
 
    //initialize the platform api
    IFBPlatformApi engine_platform_api;
    ifb_win32::memory_api_initialize (engine_platform_api.memory);

    //create the engine context
    if (!ifb_engine::context_create(engine_platform_api)) {
        return(S_FALSE);
    }

    //done
    return(S_OK);
}
