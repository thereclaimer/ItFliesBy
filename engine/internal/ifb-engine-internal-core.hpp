#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include "ifb-engine.hpp"

#include "ifb-engine-internal-managers.hpp"

namespace ifb_engine {

    ifb_void
    core_arena_commit(
        const ifb_cstr  arena_tag_cstr,
        const ifb_u32   arena_size_minimum,
              IFBArena* arena_ptr);

    ifb_void
    core_arena_get_info(
        IFBArena* arena_ptr);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP