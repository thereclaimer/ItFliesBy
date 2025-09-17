#pragma once

#include "ifb-engine-core-internal.hpp"

namespace ifb {

    static eng_core_mem_t _core_mem;

    IFB_ENG_FUNC void
    eng_core_init(
        void) {

        _core_mem.xml_arena = eng_mem_mngr_arena_commit_core();
        assert(_core_mem.xml_arena);

        sld::xml_memory_init_from_arena(_core_mem.xml_arena);
    }

};

