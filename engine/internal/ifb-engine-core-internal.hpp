#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    struct eng_core_t {
        struct {
            eng_mem_arena_t* xml;
        } arenas;
    };

};