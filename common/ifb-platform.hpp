#ifndef IFB_PLATFORM_HPP
#define IFB_PLATFORM_HPP

#include "ifb-types.hpp"
#include "ifb-scopes.hpp"
#include "ifb-graphics.hpp"

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

typedef const ifb_u32
(*funcptr_ifb_platform_system_page_size)(
    ifb_void);

typedef const ifb_u32
(*funcptr_ifb_platform_system_allocation_granularity)(
    ifb_void);

typedef const ifb_timems
(*funcptr_ifb_platform_system_time_ms)(
    ifb_void);

typedef ifb_void
(*funcptr_ifb_platform_system_sleep)(
    const ifb_u32 ms);

struct IFBPlatformSystemApi {
    funcptr_ifb_platform_system_page_size              page_size;
    funcptr_ifb_platform_system_allocation_granularity allocation_granularity;
    funcptr_ifb_platform_system_time_ms                time_ms;
    funcptr_ifb_platform_system_sleep                  sleep;
};

namespace ifb_platform {

    ifb_global funcptr_ifb_platform_system_page_size              system_page_size;
    ifb_global funcptr_ifb_platform_system_allocation_granularity system_allocation_granularity;
    ifb_global funcptr_ifb_platform_system_time_ms                system_time_ms;
    ifb_global funcptr_ifb_platform_system_sleep                  system_sleep;

    inline const ifb_b8
    system_api_valid() {

        ifb_b8 result = true;
        
        result &= system_page_size              != NULL;
        result &= system_allocation_granularity != NULL;
        result &= system_time_ms                != NULL;
        result &= system_sleep                  != NULL;

        return(result);
    }
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef const ifb_ptr
(*funcptr_ifb_platform_memory_reserve)(
    const ifb_u32 reservation_size);

typedef const ifb_b8
(*funcptr_ifb_platform_memory_release)(
    const ifb_ptr reservation_start,
    const ifb_u32 reservation_size);

typedef const ifb_ptr
(*funcptr_ifb_platform_memory_commit)(
    const ifb_ptr commit_start,
    const ifb_u32 commit_size);

typedef const ifb_b8
(*funcptr_ifb_platform_memory_decommit)(
    const ifb_ptr commit_start,
    const ifb_u32 commit_size);

struct IFBPlatformMemoryApi {
    funcptr_ifb_platform_memory_reserve  reserve;
    funcptr_ifb_platform_memory_release  release;
    funcptr_ifb_platform_memory_commit   commit;
    funcptr_ifb_platform_memory_decommit decommit;
};

namespace ifb_platform {

    ifb_global funcptr_ifb_platform_memory_reserve  memory_reserve;
    ifb_global funcptr_ifb_platform_memory_release  memory_release;
    ifb_global funcptr_ifb_platform_memory_commit   memory_commit;
    ifb_global funcptr_ifb_platform_memory_decommit memory_decommit;

    inline const ifb_b8
    memory_api_valid() {

        ifb_b8 result = true;        

        result &= memory_reserve  != NULL;
        result &= memory_release  != NULL;
        result &= memory_commit   != NULL;
        // result &= memory_decommit != NULL;

        return(result);
    }
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

typedef const ifb_b8
(*funcptr_ifb_platform_window_create) (
    const ifb_cstr title,
    const ifb_u32  width,
    const ifb_u32  height,
    const ifb_u32  position_x,
    const ifb_u32  position_y);

typedef const ifb_b8
(*funcptr_ifb_platform_window_opengl_init) (
    ifb_void);

typedef ImGuiContext*
(*funcptr_ifb_platform_window_imgui_init) (
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_platform_window_show)(
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_platform_window_destroy)(
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_platform_window_frame_start)(
    ifb_void);

typedef const ifb_b8
(*funcptr_ifb_platform_window_frame_render)(
    ifb_void);

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
    
    ifb_global funcptr_ifb_platform_window_create       window_create;
    ifb_global funcptr_ifb_platform_window_destroy      window_destroy;
    ifb_global funcptr_ifb_platform_window_frame_start  window_frame_start;
    ifb_global funcptr_ifb_platform_window_frame_render window_frame_render;
    ifb_global funcptr_ifb_platform_window_show         window_show;
    ifb_global funcptr_ifb_platform_window_opengl_init  window_opengl_init;
    ifb_global funcptr_ifb_platform_window_imgui_init   window_imgui_init;

    inline const ifb_b8
    window_api_valid() {

        ifb_b8 result = true;

        result &= window_create       != NULL;
        result &= window_destroy      != NULL;
        result &= window_frame_start  != NULL;
        result &= window_frame_render != NULL;
        result &= window_show         != NULL;
        result &= window_opengl_init  != NULL;
        result &= window_imgui_init   != NULL;

        return(result);
    }
};

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

typedef const ifb_u32
(*funcptr_ifb_platform_monitor_count) (
    ifb_void);

typedef ifb_void
(*funcptr_ifb_platform_monitor_info)(
    const ifb_u32     monitor_array_count,
          IFBMonitor* monitor_array_ptr);

struct IFBPlatformMonitorApi {
    funcptr_ifb_platform_monitor_count count;
    funcptr_ifb_platform_monitor_info  info;
};

namespace ifb_platform {

    ifb_global funcptr_ifb_platform_monitor_count monitor_count;
    ifb_global funcptr_ifb_platform_monitor_info  monitor_info;

    inline const ifb_b8
    monitor_api_valid() {

        ifb_b8 result = true;

        result &= monitor_count != NULL;
        result &= monitor_info  != NULL;    

        return(result);        
    }
};

/**********************************************************************************/
/* FILES                                                                          */                            
/**********************************************************************************/

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_only) (
    const ifb_cstr    in_file_path,
          ifb_index& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_write) (
    const ifb_cstr    in_file_path,
          ifb_index& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_open_read_write) (
    const ifb_cstr    in_file_path,
          ifb_index& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_platform_file_close) (
    const ifb_index file_index);

typedef const ifb_size
(*funcptr_ifb_platform_file_size) (
    const ifb_index file_index);

typedef const ifb_b8
(*funcptr_ifb_platform_file_read)(
    const ifb_index  in_file_index,
    const ifb_size   in_file_read_start,
    const ifb_size   in_file_read_size,
          ifb_byte* out_file_read_buffer);

typedef const ifb_b8
(*funcptr_ifb_platform_file_write)(
    const ifb_index file_index,
    const ifb_size  file_write_start,
    const ifb_size  file_write_size,
          ifb_byte* file_write_buffer);

struct IFBPlatformFileApi {
    funcptr_ifb_platform_file_open_read_only  open_read_only;
    funcptr_ifb_platform_file_open_read_write open_read_write;
    funcptr_ifb_platform_file_close           close;
    funcptr_ifb_platform_file_size            size;
    funcptr_ifb_platform_file_read            read;
    funcptr_ifb_platform_file_write           write;
};

namespace ifb_platform {

    ifb_global funcptr_ifb_platform_file_open_read_only  file_open_read_only;
    ifb_global funcptr_ifb_platform_file_open_read_write file_open_read_write;
    ifb_global funcptr_ifb_platform_file_close           file_close;
    ifb_global funcptr_ifb_platform_file_size            file_size;
    ifb_global funcptr_ifb_platform_file_read            file_read;
    ifb_global funcptr_ifb_platform_file_write           file_write;
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

typedef const ifb_b8
(*funcptr_ifb_platform_file_dialog_select_file) (
    const ifb_cstr  in_file_dialog_starting_directory,
    const ifb_size  in_file_type_count,
    const ifb_cstr* in_file_type_name_cstr_ptr,
    const ifb_cstr* in_file_type_spec_cstr_ptr,
          ifb_cstr out_file_selection_buffer);

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

    ifb_global IFBPlatformApi* _ptr_platform_api;

    inline const IFBPlatformApi*
    get_api(ifb_void) {
        return(_ptr_platform_api);
    }

    inline ifb_void 
    set_api(
        const IFBPlatformApi* ptr_platform_api) {

        _ptr_platform_api = (IFBPlatformApi*)ptr_platform_api;

        //system
        ifb_platform::system_page_size              = ptr_platform_api->system.page_size;
        ifb_platform::system_allocation_granularity = ptr_platform_api->system.allocation_granularity;
        ifb_platform::system_time_ms                = ptr_platform_api->system.time_ms;
        ifb_platform::system_sleep                  = ptr_platform_api->system.sleep;

        //memory
        ifb_platform::memory_reserve                = ptr_platform_api->memory.reserve;
        ifb_platform::memory_release                = ptr_platform_api->memory.release;
        ifb_platform::memory_commit                 = ptr_platform_api->memory.commit;
        ifb_platform::memory_decommit               = ptr_platform_api->memory.decommit;

        //window
        ifb_platform::window_create                 = ptr_platform_api->window.create;
        ifb_platform::window_destroy                = ptr_platform_api->window.destroy;
        ifb_platform::window_frame_start            = ptr_platform_api->window.frame_start;
        ifb_platform::window_frame_render           = ptr_platform_api->window.frame_render;
        ifb_platform::window_show                   = ptr_platform_api->window.show;
        ifb_platform::window_opengl_init            = ptr_platform_api->window.opengl_init;
        ifb_platform::window_imgui_init             = ptr_platform_api->window.imgui_init;

        //monitory
        ifb_platform::monitor_count                 = ptr_platform_api->monitor.count; 
        ifb_platform::monitor_info                  = ptr_platform_api->monitor.info; 
    }
};

#endif //IFB_ENGINE_PLATFORM_HPP