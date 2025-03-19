#pragma once

#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_platform {

    ifb_platform_funcptr_system_get_info          system_get_info;
    ifb_platform_funcptr_system_time_ms           system_time_ms;
    ifb_platform_funcptr_system_sleep             system_sleep;

    ifb_platform_funcptr_memory_reserve           memory_reserve;
    ifb_platform_funcptr_memory_release           memory_release;
    ifb_platform_funcptr_memory_commit            memory_commit;
    ifb_platform_funcptr_memory_decommit          memory_decommit;

    ifb_platform_funcptr_window_create            window_create;
    ifb_platform_funcptr_window_destroy           window_destroy;
    ifb_platform_funcptr_window_frame_start       window_frame_start;
    ifb_platform_funcptr_window_frame_render      window_frame_render;
    ifb_platform_funcptr_window_show              window_show;
    ifb_platform_funcptr_window_opengl_init       window_opengl_init;
    ifb_platform_funcptr_window_imgui_init        window_imgui_init;

    ifb_platform_funcptr_monitor_count            monitor_count;
    ifb_platform_funcptr_monitor_info             monitor_info;

    ifb_platform_func_ptr_file_ro_context_size    file_ro_context_size;
    ifb_platform_func_ptr_file_ro_open            file_ro_open;
    ifb_platform_func_ptr_file_ro_close           file_ro_close;
    ifb_platform_func_ptr_file_ro_read_immediate  file_ro_read_immediate;
    ifb_platform_func_ptr_file_ro_read_async      file_ro_read_async;
    ifb_platform_func_ptr_file_rw_context_size    file_rw_context_size;
    ifb_platform_func_ptr_file_rw_open            file_rw_open;
    ifb_platform_func_ptr_file_rw_close           file_rw_close;
    ifb_platform_func_ptr_file_rw_read_immediate  file_rw_read_immediate;
    ifb_platform_func_ptr_file_rw_read_async      file_rw_read_async;
    ifb_platform_func_ptr_file_rw_write_immediate file_rw_write_immediate;
    ifb_platform_func_ptr_file_rw_write_async     file_rw_write_async;

};

/**********************************************************************************/
/* PLATFORM                                                                       */
/**********************************************************************************/

const IFBB8
ifb_engine::platform_api_initialize(
    const IFBPlatformApi* ptr_platform_api) {

    if (!ptr_platform_api) return(false);
    
    //cache the api
    const IFBPlatformSystemApi&  ref_api_system  = ptr_platform_api->system;
    const IFBPlatformMemoryApi&  ref_api_memory  = ptr_platform_api->memory;
    const IFBPlatformWindowApi&  ref_api_window  = ptr_platform_api->window;
    const IFBPlatformMonitorApi& ref_api_monitor = ptr_platform_api->monitor;

    //system
    ifb_platform::system_get_info     = ref_api_system.get_info;
    ifb_platform::system_time_ms      = ref_api_system.time_ms;
    ifb_platform::system_sleep        = ref_api_system.sleep;
    
    //memory
    ifb_platform::memory_reserve      = ref_api_memory.reserve;
    ifb_platform::memory_release      = ref_api_memory.release;
    ifb_platform::memory_commit       = ref_api_memory.commit;
    ifb_platform::memory_decommit     = ref_api_memory.decommit;

    //window
    ifb_platform::window_create       = ref_api_window.create;
    ifb_platform::window_destroy      = ref_api_window.destroy;
    ifb_platform::window_frame_start  = ref_api_window.frame_start;
    ifb_platform::window_frame_render = ref_api_window.frame_render;
    ifb_platform::window_show         = ref_api_window.show;
    ifb_platform::window_opengl_init  = ref_api_window.opengl_init;
    ifb_platform::window_imgui_init   = ref_api_window.imgui_init;

    //monitor
    ifb_platform::monitor_count       = ref_api_monitor.count;
    ifb_platform::monitor_info        = ref_api_monitor.info;

    return(true);
}
