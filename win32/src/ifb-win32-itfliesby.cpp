#pragma once

#include <ifb-engine.hpp>
#include "ifb-win32.hpp"

#include "api/ifb-win32-api.cpp"

#define IFB_WIN32_GLBOAL_MEMORY_STACK_SIZE ifb_macro_size_megabytes(2)

namespace ifb_win32 {

    //global stack buffer
    ifb_global IFBU64  _global_stack_size = IFB_WIN32_GLBOAL_MEMORY_STACK_SIZE;
    ifb_global IFBByte _global_stack_buffer[IFB_WIN32_GLBOAL_MEMORY_STACK_SIZE];
};

int WINAPI 
wWinMain(
    HINSTANCE h_instance,
    HINSTANCE h_prev_instance,
    PWSTR     p_cmd_line,
    int       n_cmd_show) {

    //create the engine args
    IFBEngineContextArgs engine_args;
    engine_args.global_stack_memory.size  =          ifb_win32::_global_stack_size;
    engine_args.global_stack_memory.start = (IFBAddr)ifb_win32::_global_stack_buffer;
    engine_args.platform_api              = ifb_win32::platform_api();

    //initialize the engine
    const IFBENGContext engine_context = ifb_engine::context_create(engine_args);

    //engine lifetime
    ifb_engine::context_startup   (engine_context);
    ifb_engine::context_main_loop (engine_context);
    ifb_engine::context_shutdown  (engine_context);
    ifb_engine::context_destroy   (engine_context);
}