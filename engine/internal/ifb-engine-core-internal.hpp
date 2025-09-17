#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    struct eng_core_mem_t {
        eng_mem_arena_t* xml_arena;
    };

    void eng_core_init(void);
};