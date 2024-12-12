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

    ifb_void core_arena_get_info(IFBArena* arena_ptr);

    const ifb_u32  core_arena_get_page_start     (const IFBIDArena& arena_id_ref);
    const ifb_cstr core_arena_get_tag_cstr       (const IFBIDArena& arena_id_ref);
    const ifb_ptr  core_arena_get_pointer_start  (const IFBIDArena& arena_id_ref);
    const ifb_ptr  core_arena_get_pointer_offset (const IFBIDArena& arena_id_ref, const ifb_u32 offset);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP