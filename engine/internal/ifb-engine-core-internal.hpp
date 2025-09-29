#pragma once

#include <sld-os.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr eng_cchar ENG_CORE_WINDOW_TITLE[]           = "It Flies By";
    constexpr eng_u32   ENG_CORE_XML_MEMORY_SIZE          = sld::size_megabytes(1); 
    constexpr eng_u32   ENG_CORE_WINDOW_DEFAULT_WIDTH     = 1024;
    constexpr eng_u32   ENG_CORE_WINDOW_DEFAULT_HEIGHT    = 768;
    constexpr eng_u32   ENG_CORE_WINDOW_DEFAULT_SCREEN_X  = 0;
    constexpr eng_u32   ENG_CORE_WINDOW_DEFAULT_SCREEN_Y  = 0;
    constexpr eng_u32   ENG_CORE_MONITOR_COUNT_MAX        = 16;
    constexpr eng_u32   ENG_CORE_MONITOR_NAME_BUFFER_SIZE = (ENG_CORE_MONITOR_COUNT_MAX * sld::OS_MONITOR_NAME_WIDTH); 

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    typedef sld::os_monitor_handle_t eng_core_monitor_handle_t;
    typedef sld::os_window_handle_t  eng_core_window_handle_t;
    typedef sld::os_window_update_t  eng_core_window_update_t;
    typedef sld::os_window_error_t   eng_core_window_error_t;

    struct eng_core_arenas_t;
    struct ENG_CORE_WINDOW_t;
    struct eng_core_platform_monitors_t;

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct eng_core_arenas_t {
        eng_mem_arena_t* xml;
        eng_mem_arena_t* platform;
    };

    struct eng_core_window_t {
        eng_core_window_error_t  last_error;
        eng_core_window_handle_t handle;
        eng_dims_u32_size_t      size;
        eng_dims_u32_pos_t       position;
        eng_core_window_update_t update;
    };

    struct eng_core_monitor_table_t {
        eng_core_monitor_handle_t primary;         
        eng_core_monitor_handle_t active;         
        eng_u32                   count;
        eng_dims_u32_size_t       virtual_size;
        eng_pad32                 padding;
        struct {
            eng_u32*                   position_x;
            eng_u32*                   position_y;
            eng_u32*                   width;
            eng_u32*                   height;
            eng_cchar*                 name;
            eng_core_monitor_handle_t* handle;
        } array;
    };

    struct eng_core_monitor_name_t {
        eng_cchar cstr[sld::OS_MONITOR_NAME_WIDTH];
    };
    struct eng_core_monitor_info_t {
        eng_core_monitor_handle_t os_handle;
        eng_dims_u32_size_t       size;
        eng_dims_u32_pos_t        pos;
        eng_core_monitor_name_t   name;
    };

    //-------------------------------------------------------------------
    // SINGLETONS
    //-------------------------------------------------------------------

    static eng_byte                 _eng_core_xml_memory[ENG_CORE_XML_MEMORY_SIZE]; 
    static eng_core_arenas_t        _eng_core_arenas;
    static eng_core_window_t        _eng_core_window;
    static eng_core_monitor_table_t _eng_core_monitor_table;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_FUNC void     eng_core_window_init                      (void);
    IFB_ENG_FUNC void     eng_core_window_open_and_show             (void);
    IFB_ENG_FUNC void     eng_core_window_process_events            (void);
    IFB_ENG_FUNC void     eng_core_window_swap_buffers              (void);
    IFB_ENG_FUNC void     eng_core_window_center_to_monitor         (const eng_core_monitor_handle_t monitor);
    IFB_ENG_FUNC void     eng_core_window_center_to_primary_monitor (void);

    IFB_ENG_FUNC eng_bool eng_core_monitor_table_validate           (void);
    IFB_ENG_FUNC void     eng_core_monitor_table_init               (void);
    IFB_ENG_FUNC void     eng_core_monitor_table_refresh            (void);
    IFB_ENG_FUNC eng_u32  eng_core_monitor_table_search             (const eng_core_monitor_handle_t monitor);
    IFB_ENG_FUNC void     eng_core_monitor_get_size                 (const eng_core_monitor_handle_t monitor, eng_dims_u32_size_t&     size);
    IFB_ENG_FUNC void     eng_core_monitor_get_position             (const eng_core_monitor_handle_t monitor, eng_dims_u32_pos_t&      pos);
    IFB_ENG_FUNC void     eng_core_monitor_get_name                 (const eng_core_monitor_handle_t monitor, eng_core_monitor_name_t& name);
    IFB_ENG_FUNC void     eng_core_monitor_get_info                 (const eng_core_monitor_handle_t monitor, eng_core_monitor_info_t& info);

};

#define eng_core_platform_arena_push_struct_array(count, type) eng_mem_arena_push_struct_array(_eng_core_arenas.platform, count, type)