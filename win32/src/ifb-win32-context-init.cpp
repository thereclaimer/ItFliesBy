#pragma once

#include "ifb-win32.hpp"

#define IFB_WIN32_CONTEXT_STACK_SIZE ifb_macro_size_kilobytes(512)

namespace ifb_win32 {

    IFBVoid context_init_step_0_validate_args                 (IFBWin32ContextInit& init_ref);
    IFBVoid context_init_step_1_create_memory_context         (IFBWin32ContextInit& init_ref);
    IFBVoid context_init_step_3_set_platform_api              (IFBWin32ContextInit& init_ref);
    IFBVoid context_init_step_4_create_engine_context         (IFBWin32ContextInit& init_ref);
};

inline IFBVoid 
ifb_win32::context_init_step_0_validate_args(
    IFBWin32ContextInit& init_ref) {
    
    if (init_ref.result) {

        init_ref.result &= (init_ref.win32_args != NULL);
    }
}


inline IFBVoid 
ifb_win32::context_init_step_1_create_memory_context(
    IFBWin32ContextInit& init_ref) {

    if (init_ref.result) {
        
        //static memory stack
        ifb_local const IFBU64  context_stack_size = IFB_WIN32_CONTEXT_STACK_SIZE;
        ifb_local const IFBByte context_stack_buffer[context_stack_size];

        //create the memory context
        init_ref.memory = ifb_memory::context_create(
            context_stack_buffer,
            context_stack_size);

        //make sure its valid
        init_ref.result &= (init_ref.memory != NULL);
    }
}

inline IFBVoid 
ifb_win32::context_init_step_2_stack_allocate_win32_context(
    IFBWin32ContextInit& init_ref) {

    if (init_ref.result) {

        //calculate size
        const IFBU32 size = ifb_macro_align_size_struct(IFBWin32Context);
        
        //allocate context
        init_ref.context = (IFBWin32Context*)ifb_memory::context_stack_commit_absolute(
            init_ref.memory,
            size);

        //make sure its valid
        init_ref.result &= (init_ref.context != NULL);
    }
}

inline IFBVoid
ifb_win32::context_init_step_3_set_platform_api(
    IFBWin32ContextInit& init_ref) {

    if (init_ref.result) {

        //system
        init_ref.platform.system.get_info_cpu    = ifb_win32::system_get_info_cpu;
        init_ref.platform.system.get_info_memory = ifb_win32::system_get_info_memory;
        init_ref.platform.system.time_ms         = ifb_win32::system_time_ms;
        init_ref.platform.system.sleep           = ifb_win32::system_sleep;

        //memory    
        init_ref.platform.memory.reserve         = ifb_win32::memory_reserve;
        init_ref.platform.memory.release         = ifb_win32::memory_release;
        init_ref.platform.memory.commit          = ifb_win32::memory_commit;

        //window    
        init_ref.platform.window.create          = ifb_win32::window_create;
        init_ref.platform.window.destroy         = ifb_win32::window_destroy;
        init_ref.platform.window.frame_start     = ifb_win32::window_frame_start;
        init_ref.platform.window.frame_render    = ifb_win32::window_frame_render;
        init_ref.platform.window.show            = ifb_win32::window_show;
        init_ref.platform.window.opengl_init     = ifb_win32::window_opengl_init;
        init_ref.platform.window.imgui_init      = ifb_win32::window_imgui_init;

        //monitor
        init_ref.platform.monitor.count          = ifb_win32::monitor_count;
        init_ref.platform.monitor.info           = ifb_win32::monitor_info;
    }
}


inline IFBVoid 
ifb_win32::context_init_step_4_create_engine_context(
    IFBWin32ContextInit& init_ref) {

    if (init_ref.result) {

        //set engine args
        init_ref.engine_args.memory_context = init_ref.memory;
        init_ref.engine_args.platform_api   = &init_ref.platform;

        //create the engine context
        init_ref.result &= ifb_engine::context_create(&init_ref.engine_args);
    }
}
