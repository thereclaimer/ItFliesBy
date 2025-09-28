#pragma once

#include "ifb-engine-core-internal.hpp"

namespace ifb {

    static eng_core_t _core;

    IFB_ENG_API eng_bool
    eng_core_startup(
        void) {

        // start managers
        eng_mem_mngr_startup  ();
        eng_file_mngr_startup ();

        // allocate core memory
        _core.arenas.xml = eng_mem_arena_commit_core();
        assert(_core.arenas.xml);

        // initialize xml
        const eng_u32   xml_parser_size   = sld::size_megabytes   (1);
        const eng_void* xml_parser_memory = sld::arena_push_bytes (_core.arenas.xml, xml_parser_size);
        sld::xml_parser_init(xml_parser_memory, xml_parser_size);

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
        return(false);
    }

    IFB_ENG_API eng_bool
    eng_core_render(
        void) {

        return(false);
    }


};

