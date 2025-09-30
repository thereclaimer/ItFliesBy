#pragma once

#include "ifb-engine-core-internal.hpp"
#include "ifb-engine-gui-internal.hpp"
namespace ifb {

    IFB_ENG_API eng_bool
    eng_core_startup(
        void) {

        // start managers
        eng_mem_mngr_startup  ();
        eng_file_mngr_startup ();

        // allocate core memory
        _eng_core_arenas.xml      = eng_mem_arena_commit_core();
        _eng_core_arenas.platform = eng_mem_arena_commit_core();
        eng_bool is_mem_ok = true;
        is_mem_ok &= (_eng_core_arenas.xml      != NULL);
        is_mem_ok &= (_eng_core_arenas.platform != NULL);
        
        // initialize xml
        sld::xml_parser_init((void*)_eng_core_xml_memory, ENG_CORE_XML_MEMORY_SIZE);
        
        // initialize platform
        eng_core_monitor_table_init ();
        eng_core_window_init        ();
        eng_core_window_center_to_primary_monitor();
        eng_core_window_open_and_show();

        return(true); 
    }

    IFB_ENG_API eng_bool
    eng_core_shutdown(
        void) {

        return(false);
    }

    IFB_ENG_API eng_bool
    eng_core_update(
        void) {

        eng_core_window_process_events();

        return(true);
    }

    IFB_ENG_API eng_bool
    eng_core_render(
        void) {

        eng_gui_render();
        eng_core_window_swap_buffers();

        return(true);
    }

};

