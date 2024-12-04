#ifndef IFB_ENGINE_INTERNAL_PLATFORM_HPP
#define IFB_ENGINE_INTERNAL_PLATFORM_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"

struct IFBEnginePlatform {
    struct {
        ifb_handle system;
        ifb_handle memory;
        ifb_handle window;
        ifb_handle monitor;
    } global_handles;
};

namespace ifb_engine {

    inline IFBEnginePlatform*  platform_global_pointer         (const ifb_handle handle) { return(ifb_engine_memory_global_pointer_type(handle,IFBEnginePlatform));}
    inline IFBPlatformSystem*  platform_global_pointer_system  (const ifb_handle handle) { return(ifb_engine_memory_global_pointer_type(handle,IFBPlatformSystem));}
    inline IFBPlatformMemory*  platform_global_pointer_memory  (const ifb_handle handle) { return(ifb_engine_memory_global_pointer_type(handle,IFBPlatformMemory));}
    inline IFBPlatformWindow*  platform_global_pointer_window  (const ifb_handle handle) { return(ifb_engine_memory_global_pointer_type(handle,IFBPlatformWindow));}
    inline IFBPlatformMonitor* platform_global_pointer_monitor (const ifb_handle handle) { return(ifb_engine_memory_global_pointer_type(handle,IFBPlatformMonitor));}
};

//api
namespace ifb_engine {

    //system
    ifb_global funcptr_ifb_platform_system_info             platform_system_info;

    //window
    ifb_global funcptr_ifb_platform_window_create           platform_window_create;
    ifb_global funcptr_ifb_platform_window_destroy          platform_window_destroy;
    ifb_global funcptr_ifb_platform_window_frame_start      platform_window_frame_start;
    ifb_global funcptr_ifb_platform_window_frame_render     platform_window_frame_render;
    ifb_global funcptr_ifb_platform_window_show             platform_window_show;
    ifb_global funcptr_ifb_platform_window_opengl_init      platform_window_opengl_init;
    ifb_global funcptr_ifb_platform_window_imgui_init       platform_window_imgui_init;

    //monitor
    ifb_global funcptr_ifb_platform_monitor_info            platform_monitor_info;

    //memory
    ifb_global funcptr_ifb_platform_memory_reserve          platform_memory_reserve;
    ifb_global funcptr_ifb_platform_memory_release          platform_memory_release;
    ifb_global funcptr_ifb_platform_memory_commit           platform_memory_commit;
};


namespace ifb_engine {

    const ifb_handle platform_initialize(IFBPlatformApi& platform_api_ref);


};

#endif //IFB_ENGINE_INTERNAL_PLATFORM_HPP