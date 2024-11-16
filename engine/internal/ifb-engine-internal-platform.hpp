#ifndef IFB_ENGINE_INTERNAL_PLATFORM_HPP
#define IFB_ENGINE_INTERNAL_PLATFORM_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

namespace ifb_engine {

    //system

    //window
    ifb_global funcptr_ifb_engine_platform_window_create           platform_window_create;
    ifb_global funcptr_ifb_engine_platform_window_destroy          platform_window_destroy;
    ifb_global funcptr_ifb_engine_platform_window_update           platform_window_update;
    ifb_global funcptr_ifb_engine_platform_window_show             platform_window_show;
    ifb_global funcptr_ifb_engine_platform_window_opengl_init      platform_window_opengl_init;
    ifb_global funcptr_ifb_engine_platform_window_imgui_init       platform_window_imgui_init;

    //monitor
    ifb_global funcptr_ifb_engine_platform_monitor_size            platform_monitor_size;
    ifb_global funcptr_ifb_engine_platform_monitor_refresh_hz      platform_monitor_refresh_hz;

    //memory
    ifb_global funcptr_ifb_engine_platform_memory_pages_commit     platform_memory_pages_commit;
    ifb_global funcptr_ifb_engine_platform_memory_pages_decommit   platform_memory_pages_decommit;

    //file
    ifb_global funcptr_ifb_engine_platform_file_open_read_only     platform_file_open_read_only;
    ifb_global funcptr_ifb_engine_platform_file_open_read_write    platform_file_open_read_write;
    ifb_global funcptr_ifb_engine_platform_file_close              platform_file_close;
    ifb_global funcptr_ifb_engine_platform_file_size               platform_file_size;
    ifb_global funcptr_ifb_engine_platform_file_read               platform_file_read;
    ifb_global funcptr_ifb_engine_platform_file_write              platform_file_write;

    //file dialog
    ifb_global funcptr_ifb_engine_platform_file_dialog_select_file platform_file_dialog_select_file;


    inline const ifb_b8 
    platform_api_validate(
        IFBEnginePlatformApi& platform_api_ref) {

        ifb_b8 result = true;

        //set the function pointers
        ifb_engine::platform_memory_pages_commit     = platform_api_ref.memory.pages_commit; 
        ifb_engine::platform_memory_pages_decommit   = platform_api_ref.memory.pages_decommit;         
        ifb_engine::platform_window_create           = platform_api_ref.window.create;
        ifb_engine::platform_window_destroy          = platform_api_ref.window.destroy;
        ifb_engine::platform_window_update           = platform_api_ref.window.update;
        ifb_engine::platform_window_show             = platform_api_ref.window.show;
        ifb_engine::platform_window_opengl_init      = platform_api_ref.window.opengl_init;
        ifb_engine::platform_window_imgui_init       = platform_api_ref.window.imgui_init;
        ifb_engine::platform_monitor_size            = platform_api_ref.monitor.size;
        ifb_engine::platform_monitor_refresh_hz      = platform_api_ref.monitor.refresh_hz;
        ifb_engine::platform_file_open_read_only     = platform_api_ref.file.open_read_only;
        ifb_engine::platform_file_open_read_write    = platform_api_ref.file.open_read_write;
        ifb_engine::platform_file_close              = platform_api_ref.file.close;
        ifb_engine::platform_file_size               = platform_api_ref.file.size;
        ifb_engine::platform_file_read               = platform_api_ref.file.read;
        ifb_engine::platform_file_write              = platform_api_ref.file.write;
        ifb_engine::platform_file_dialog_select_file = platform_api_ref.file_dialog.select_file;        

        //sanity check
        result &= (
            ifb_engine::platform_memory_pages_commit           && 
            ifb_engine::platform_memory_pages_decommit         //&& 
            // ifb_engine::platform_window_create                 &&
            // ifb_engine::platform_window_destroy                &&
            // ifb_engine::platform_window_update                 &&
            // ifb_engine::platform_window_show                   &&
            // ifb_engine::platform_window_opengl_context_create  &&
            // ifb_engine::platform_window_imgui_context_create   &&
            // ifb_engine::platform_file_open_read_only           &&
            // ifb_engine::platform_file_open_read_write          &&
            // ifb_engine::platform_file_close                    &&
            // ifb_engine::platform_file_size                     &&
            // ifb_engine::platform_file_read                     &&
            // ifb_engine::platform_file_write                    &&
            // ifb_engine::platform_file_dialog_select_file
            );

        //we're done
        return(result);
    }
};

#endif //IFB_ENGINE_INTERNAL_PLATFORM_HPP