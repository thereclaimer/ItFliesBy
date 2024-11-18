#pragma once

#include "ifb-win32.hpp"

int WINAPI 
wWinMain(
    HINSTANCE h_instance,
    HINSTANCE h_prev_instance,
    PWSTR     p_cmd_line,
    int       n_cmd_show) {

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
    ifb_win32::window_api_initialize(engine_platform_api.window);

    //create the engine context
    if (!ifb_engine::engine_create_context(
            engine_platform_info,
            engine_platform_api)) {

        return(S_FALSE);
    }

    //allocate win32 struct
    const ifb_u32 win32_size_aligned = ifb_engine_macro_align_size_struct(IFBWin32Context);
    _ifb_win32_context_ptr = (IFBWin32Context*)ifb_engine::engine_platform_alloc(win32_size_aligned);
    
    //set the arguments
    IFBWin32Args& args_ref = _ifb_win32_context_ptr->args; 
    args_ref.h_instance      = h_instance; 
    args_ref.h_prev_instance = h_prev_instance; 
    args_ref.p_cmd_line      = p_cmd_line; 
    args_ref.n_cmd_show      = n_cmd_show; 

    //start the engine
    ifb_b8 running = ifb_engine::engine_startup();

    while(running) {

        //execute the next frame
        running &= ifb_engine::engine_frame_execute();
    };

    //release the memory
    if (!ifb_win32::memory_release(
            engine_platform_info.reservation_start,
            engine_platform_info.reservation_size)) {

        return(S_FALSE);
    }



    //done
    return(S_OK);
}
