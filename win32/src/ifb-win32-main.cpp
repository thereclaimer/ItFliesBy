#pragma once

#include "ifb-win32.hpp"

r_internal r_s32 
ifb_win32_main(
    RWin32MainArgs& args) {

    //initialize the platform api
    IFBEnginePlatformApi engine_platform_api;
    ifb_win32::system_api_initialize     (engine_platform_api.system);
    ifb_win32::memory_api_initialize     (engine_platform_api.memory);
    ifb_win32::file_api_initialize       (engine_platform_api.file);
    ifb_win32::file_dialog_api_initialize(engine_platform_api.file_dialog);

    r_b8 running = true;

    //get the memory reservation
    const r_size   memory_reservation_size  = IFB_ENGINE_MINIMUM_MEMORY_REQUIREMENT_4GB;
    const r_memory memory_reservation_start = r_win32::memory_reserve(NULL,memory_reservation_size);

    running &= memory_reservation_start;

    //start the engine
    IFBEngineContext* engine_context_ptr = ifb_engine::engine_startup(
        engine_platform_api,
        memory_reservation_start,                
        memory_reservation_size);

    running &= engine_context_ptr != NULL;

    //main window loop
    while(running) {

        running &= ifb_engine::engine_frame_start(engine_context_ptr);
        running &= ifb_engine::engine_frame_render(engine_context_ptr);
    }

    //release the memory
    r_win32::memory_release(memory_reservation_start,memory_reservation_size);

    //done
    return(S_OK);
}
