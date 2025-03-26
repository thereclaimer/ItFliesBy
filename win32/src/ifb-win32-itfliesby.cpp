#pragma once

#include <ifb-memory.hpp>
#include "ifb-win32.hpp"

#include "api/ifb-win32-api.cpp"

#define IFB_WIN32_GLBOAL_MEMORY_STACK_SIZE ifb_macro_size_kilobytes(512)

namespace ifb_win32 {

    //global stack buffer
    ifb_global const IFBU64  _global_stack_size = IFB_WIN32_GLBOAL_MEMORY_STACK_SIZE;
    ifb_global const IFBByte _global_stack_buffer[IFB_WIN32_GLBOAL_MEMORY_STACK_SIZE];
    
    //internal methods
    const IFBMEM64Stack create_global_stack(IFBVoid);
};

int WINAPI 
wWinMain(
    HINSTANCE h_instance,
    HINSTANCE h_prev_instance,
    PWSTR     p_cmd_line,
    int       n_cmd_show) {

    //create the engine args
    IFBEngineArgs engine_args;
    engine_args.global_stack_handle = ifb_win32::create_global_stack();
    engine_args.platform_api        = ifb_win32::platform_api();
}

inline const IFBMEM64Stack
ifb_win32::create_global_stack(
    IFBVoid) {

    //initialize the stack args
    IFBMemory memory;
    memory.size  =          ifb_win32::_global_stack_size;
    memory.start = (IFBAddr)ifb_win32::_global_stack_buffer;

    //create the stack
    const IFBMEM64Stack global_stack = ifb_memory::stack_create(memory);    

    //make sure its valid
    ifb_macro_assert(global_stack.h64);

    //we're done
    return(global_stack);
}