#pragma once

#include "ifb-win32.hpp"

r_internal r_s32 
ifb_win32_main(
    RWin32MainArgs& args) {

    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);

    //initialize the platform info
    IFBEnginePlatformInfo engine_platform_info;

    //get the memory reservation
    engine_platform_info.reservation_size  = ifb_engine::math_size_gigabytes(4);
    engine_platform_info.reservation_start = ifb_win32::memory_reserve(engine_platform_info.reservation_size);
    engine_platform_info.page_size         = system_info.dwPageSize; 
 
    //initialize the platform api
    IFBEnginePlatformApi engine_platform_api;
    ifb_win32::memory_api_initialize(engine_platform_api.memory);

    //create the engine context
    if (!ifb_engine::engine_create_context(
        engine_platform_info,
        engine_platform_api)) {

        return(S_FALSE);
    }

    ifb_engine::engine_startup();

    // //main window loop
    // while(running) {

    // }

    //release the memory
    r_win32::memory_release(
        engine_platform_info.reservation_start,
        engine_platform_info.reservation_size);

    //done
    return(S_OK);
}
