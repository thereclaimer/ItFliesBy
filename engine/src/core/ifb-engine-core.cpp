#pragma once

#include "ifb-engine-core-internal.hpp"

namespace ifb {


    IFB_ENG_API eng_bool
    eng_core_startup(
        void) {

        // start managers
        eng_mem_mngr_startup  ();
        eng_file_mngr_startup ();

        // allocate core memory
        _eng_core_arenas.xml_arena = eng_mem_arena_commit_core();
        assert(_eng_core_arenas.xml_arena);
        
        // initialize xml
        sld::xml_parser_init((void*)_eng_core_xml_memory, ENG_CORE_XML_MEMORY_SIZE);

        // open and show the window
        eng_core_platform_window_open_and_show();

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

        return(false);
    }

    IFB_ENG_API eng_bool
    eng_core_render(
        void) {

        return(false);
    }

};

