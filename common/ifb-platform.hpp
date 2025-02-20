#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include "ifb-types.hpp"
#include "ifb-scopes.hpp"
#include "_ifb-graphics.hpp"

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

typedef const IFBU32
(*funcptr_ifb_platform_system_page_size)(
    IFBVoid);

typedef const IFBU32
(*funcptr_ifb_platform_system_allocation_granularity)(
    IFBVoid);

typedef const IFBTimems
(*funcptr_ifb_platform_system_time_ms)(
    IFBVoid);

typedef IFBVoid
(*funcptr_ifb_platform_system_sleep)(
    const IFBU32 ms);

struct IFBPlatformSystemApi {
    funcptr_ifb_platform_system_page_size              page_size;
    funcptr_ifb_platform_system_allocation_granularity allocation_granularity;
    funcptr_ifb_platform_system_time_ms                time_ms;
    funcptr_ifb_platform_system_sleep                  sleep;
};

namespace ifb_platform {

    extern funcptr_ifb_platform_system_page_size              system_page_size;
    extern funcptr_ifb_platform_system_allocation_granularity system_allocation_granularity;
    extern funcptr_ifb_platform_system_time_ms                system_time_ms;
    extern funcptr_ifb_platform_system_sleep                  system_sleep;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef const IFBPtr
(*funcptr_ifb_platform_memory_reserve)(
    const IFBU32 reservation_size);

typedef const IFBB8
(*funcptr_ifb_platform_memory_release)(
    const IFBPtr reservation_start,
    const IFBU32 reservation_size);

typedef const IFBPtr
(*funcptr_ifb_platform_memory_commit)(
    const IFBPtr commit_start,
    const IFBU32 commit_size);

typedef const IFBB8
(*funcptr_ifb_platform_memory_decommit)(
    const IFBPtr commit_start,
    const IFBU32 commit_size);

struct IFBPlatformMemoryApi {
    funcptr_ifb_platform_memory_reserve  reserve;
    funcptr_ifb_platform_memory_release  release;
    funcptr_ifb_platform_memory_commit   commit;
    funcptr_ifb_platform_memory_decommit decommit;
};

namespace ifb_platform {

    extern funcptr_ifb_platform_memory_reserve  memory_reserve;
    extern funcptr_ifb_platform_memory_release  memory_release;
    extern funcptr_ifb_platform_memory_commit   memory_commit;
    extern funcptr_ifb_platform_memory_decommit memory_decommit;
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const IFBB8
(*funcptr_ifb_platform_window_create) (
    const IFBCStr title,
    const IFBU32  width,
    const IFBU32  height,
    const IFBU32  position_x,
    const IFBU32  position_y);

typedef const IFBB8
(*funcptr_ifb_platform_window_opengl_init) (
    IFBVoid);

typedef ImGuiContext*
(*funcptr_ifb_platform_window_imgui_init) (
    IFBVoid);

typedef const IFBB8
(*funcptr_ifb_platform_window_show)(
    IFBVoid);

typedef const IFBB8
(*funcptr_ifb_platform_window_destroy)(
    IFBVoid);

typedef const IFBB8
(*funcptr_ifb_platform_window_frame_start)(
    IFBVoid);

typedef const IFBB8
(*funcptr_ifb_platform_window_frame_render)(
    IFBVoid);

struct IFBPlatformWindowApi {
    funcptr_ifb_platform_window_create       create;
    funcptr_ifb_platform_window_destroy      destroy;
    funcptr_ifb_platform_window_frame_start  frame_start;
    funcptr_ifb_platform_window_frame_render frame_render;
    funcptr_ifb_platform_window_show         show;
    funcptr_ifb_platform_window_opengl_init  opengl_init;
    funcptr_ifb_platform_window_imgui_init   imgui_init;
};

namespace ifb_platform {

    extern funcptr_ifb_platform_window_create       window_create;
    extern funcptr_ifb_platform_window_destroy      window_destroy;
    extern funcptr_ifb_platform_window_frame_start  window_frame_start;
    extern funcptr_ifb_platform_window_frame_render window_frame_render;
    extern funcptr_ifb_platform_window_show         window_show;
    extern funcptr_ifb_platform_window_opengl_init  window_opengl_init;
    extern funcptr_ifb_platform_window_imgui_init   window_imgui_init;
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

typedef const IFBU32
(*funcptr_ifb_platform_monitor_count) (
    IFBVoid);

typedef IFBVoid
(*funcptr_ifb_platform_monitor_info)(
    const IFBU32  monitor_array_count,
          IFBPtr* monitor_array_ptr);

struct IFBPlatformMonitorApi {
    funcptr_ifb_platform_monitor_count count;
    funcptr_ifb_platform_monitor_info  info;
};

namespace ifb_platform {

    extern funcptr_ifb_platform_monitor_count monitor_count;
    extern funcptr_ifb_platform_monitor_info  monitor_info;
};

/**********************************************************************************/
/* FILES                                                                          */                            
/**********************************************************************************/

typedef const IFBB8
(*funcptr_ifb_platform_file_open_read_only) (
    const IFBCStr    in_file_path,
          IFBIndex& out_file_index_ref);

typedef const IFBB8
(*funcptr_ifb_platform_file_open_read_write) (
    const IFBCStr    in_file_path,
          IFBIndex& out_file_index_ref);

typedef const IFBB8
(*funcptr_ifb_platform_file_open_read_write) (
    const IFBCStr    in_file_path,
          IFBIndex& out_file_index_ref);

typedef const IFBB8
(*funcptr_ifb_platform_file_close) (
    const IFBIndex file_index);

typedef const IFBSize
(*funcptr_ifb_platform_file_size) (
    const IFBIndex file_index);

typedef const IFBB8
(*funcptr_ifb_platform_file_read)(
    const IFBIndex  in_file_index,
    const IFBSize   in_file_read_start,
    const IFBSize   in_file_read_size,
          IFBByte* out_file_read_buffer);

typedef const IFBB8
(*funcptr_ifb_platform_file_write)(
    const IFBIndex file_index,
    const IFBSize  file_write_start,
    const IFBSize  file_write_size,
          IFBByte* file_write_buffer);

struct IFBPlatformFileApi {
    funcptr_ifb_platform_file_open_read_only  open_read_only;
    funcptr_ifb_platform_file_open_read_write open_read_write;
    funcptr_ifb_platform_file_close           close;
    funcptr_ifb_platform_file_size            size;
    funcptr_ifb_platform_file_read            read;
    funcptr_ifb_platform_file_write           write;
};

namespace ifb_platform {

    extern funcptr_ifb_platform_file_open_read_only  open_read_only;
    extern funcptr_ifb_platform_file_open_read_write open_read_write;
    extern funcptr_ifb_platform_file_close           close;
    extern funcptr_ifb_platform_file_size            size;
    extern funcptr_ifb_platform_file_read            read;
    extern funcptr_ifb_platform_file_write           write;
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

typedef const IFBB8
(*funcptr_ifb_platform_file_dialog_select_file) (
    const IFBCStr  in_file_dialog_starting_directory,
    const IFBSize  in_file_type_count,
    const IFBCStr* in_file_type_name_cstr_ptr,
    const IFBCStr* in_file_type_spec_cstr_ptr,
          IFBCStr out_file_selection_buffer);

struct IFBPlatformFileDialogApi {
    funcptr_ifb_platform_file_dialog_select_file select_file;
};

/**********************************************************************************/
/* PLATFORM API                                                                   */
/**********************************************************************************/

struct IFBPlatformApi {
    IFBPlatformSystemApi  system;
    IFBPlatformMemoryApi  memory;
    IFBPlatformWindowApi  window;
    IFBPlatformMonitorApi monitor;
};

namespace ifb_platform {

    const IFBB8 set_api(const IFBPlatformApi* ptr_platform_api);
};

inline const IFBB8
ifb_platform::set_api(
    const IFBPlatformApi* ptr_platform_api) {

    //sanity check
    if (!ptr_platform_api) return(false);

    //cache the api
    const IFBPlatformSystemApi&  ref_api_system  = ptr_platform_api->system;
    const IFBPlatformMemoryApi&  ref_api_memory  = ptr_platform_api->memory;
    const IFBPlatformWindowApi&  ref_api_window  = ptr_platform_api->window;
    const IFBPlatformMonitorApi& ref_api_monitor = ptr_platform_api->monitor;

    //system
    ifb_platform::system_page_size              = ref_api_system.page_size;
    ifb_platform::system_allocation_granularity = ref_api_system.allocation_granularity;
    ifb_platform::system_time_ms                = ref_api_system.time_ms;
    ifb_platform::system_sleep                  = ref_api_system.sleep;
    
    //memory
    ifb_platform::memory_reserve                = ref_api_memory.reserve;
    ifb_platform::memory_release                = ref_api_memory.release;
    ifb_platform::memory_commit                 = ref_api_memory.commit;
    ifb_platform::memory_decommit               = ref_api_memory.decommit;

    //window
    ifb_platform::window_create                 = ref_api_window.create;
    ifb_platform::window_destroy                = ref_api_window.destroy;
    ifb_platform::window_frame_start            = ref_api_window.frame_start;
    ifb_platform::window_frame_render           = ref_api_window.frame_render;
    ifb_platform::window_show                   = ref_api_window.show;
    ifb_platform::window_opengl_init            = ref_api_window.opengl_init;
    ifb_platform::window_imgui_init             = ref_api_window.imgui_init;

    //monitor
    ifb_platform::monitor_count                 = ref_api_monitor.count;
    ifb_platform::monitor_info                  = ref_api_monitor.info;

    //we're done
    return(true);
}

#endif //IFB_ENGINE_PLATFORM_HPP