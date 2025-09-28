#pragma once

#include <sld-os.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // CONSTANTS
    //-------------------------------------------------------------------

    constexpr eng_cchar ENG_CORE_PLATFORM_WINDOW_TITLE[]          = "It Flies By";
    constexpr eng_u32   ENG_CORE_XML_MEMORY_SIZE                  = sld::size_megabytes(1); 
    constexpr eng_u32   ENG_CORE_PLATFORM_WINDOW_DEFAULT_WIDTH    = 1024;
    constexpr eng_u32   ENG_CORE_PLATFORM_WINDOW_DEFAULT_HEIGHT   = 768;
    constexpr eng_u32   ENG_CORE_PLATFORM_WINDOW_DEFAULT_SCREEN_X = 0;
    constexpr eng_u32   ENG_CORE_PLATFORM_WINDOW_DEFAULT_SCREEN_Y = 0;

    //-------------------------------------------------------------------
    // TYPES
    //-------------------------------------------------------------------

    struct eng_core_arenas_t;
    struct eng_core_platform_window_t;

    //-------------------------------------------------------------------
    // DEFINITIONS
    //-------------------------------------------------------------------

    struct eng_core_arenas_t {
        eng_mem_arena_t* xml_arena;
    };

    struct eng_core_platform_window_t {
        sld::os_window_error_t    last_error;
        sld::os_window_handle_t   handle;
        sld::os_window_size_t     default_size;
        sld::os_window_position_t default_position;
    };

    //-------------------------------------------------------------------
    // SINGLETONS
    //-------------------------------------------------------------------

    static eng_byte                     _eng_core_xml_memory[ENG_CORE_XML_MEMORY_SIZE]; 
    static eng_core_arenas_t            _eng_core_arenas;
    static eng_core_platform_window_t   _eng_core_platform_window;

    //-------------------------------------------------------------------
    // METHODS
    //-------------------------------------------------------------------

    void eng_core_platform_window_open_and_show (void);
};