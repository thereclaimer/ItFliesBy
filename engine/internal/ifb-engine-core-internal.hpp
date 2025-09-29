#pragma once

#include <sld-os.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr eng_cchar ENG_CORE_PLATFORM_WINDOW_TITLE[]           = "It Flies By";
    constexpr eng_u32   ENG_CORE_XML_MEMORY_SIZE                   = sld::size_megabytes(1); 
    constexpr eng_u32   ENG_CORE_PLATFORM_WINDOW_DEFAULT_WIDTH     = 1024;
    constexpr eng_u32   ENG_CORE_PLATFORM_WINDOW_DEFAULT_HEIGHT    = 768;
    constexpr eng_u32   ENG_CORE_PLATFORM_WINDOW_DEFAULT_SCREEN_X  = 0;
    constexpr eng_u32   ENG_CORE_PLATFORM_WINDOW_DEFAULT_SCREEN_Y  = 0;
    constexpr eng_u32   ENG_CORE_PLATFORM_MONITOR_COUNT_MAX        = 16;
    constexpr eng_u32   ENG_CORE_PLATFORM_MONITOR_NAME_BUFFER_SIZE = (ENG_CORE_PLATFORM_MONITOR_COUNT_MAX * sld::OS_MONITOR_NAME_WIDTH); 

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    typedef sld::os_monitor_handle_t eng_core_monitor_os_handle_t;

    struct eng_core_arenas_t;
    struct eng_core_platform_window_t;
    struct eng_core_platform_monitors_t;

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct eng_core_arenas_t {
        eng_mem_arena_t* xml;
        eng_mem_arena_t* platform;
    };

    struct eng_core_platform_window_t {
        sld::os_window_error_t    last_error;
        sld::os_window_handle_t   handle;
        sld::os_window_size_t     default_size;
        sld::os_window_position_t default_position;
        sld::os_window_update_t   update;
    };

    struct eng_core_platform_monitor_table_t {
        eng_core_monitor_os_handle_t active_monitor;         
        eng_u32                      count;
        eng_dims_size_t              virtual_size;
        struct {
            eng_u32*                      position_x;
            eng_u32*                      position_y;
            eng_u32*                      width;
            eng_u32*                      height;
            eng_cchar*                    name;
            eng_core_monitor_os_handle_t* os_handle;
        } array;
    };


    //-------------------------------------------------------------------
    // SINGLETONS
    //-------------------------------------------------------------------

    static eng_byte                          _eng_core_xml_memory[ENG_CORE_XML_MEMORY_SIZE]; 
    static eng_core_arenas_t                 _eng_core_arenas;
    static eng_core_platform_window_t        _eng_core_platform_window;
    static eng_core_platform_monitor_table_t _eng_core_platform_monitor_table;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    IFB_ENG_FUNC void eng_core_platform_window_open_and_show  (void);
    IFB_ENG_FUNC void eng_core_platform_window_process_events (void);
    IFB_ENG_FUNC void eng_core_platform_window_swap_buffers   (void);

    IFB_ENG_FUNC void eng_core_platform_monitor_table_init    (void);

};

#define eng_core_platform_arena_push_struct_array(count, type) eng_mem_arena_push_struct_array(_eng_core_arenas.platform, count, type)