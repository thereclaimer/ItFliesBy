#pragma once

#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-context.hpp"

inline ifb_void
ifb_engine::core_arena_commit(
    const ifb_cstr  arena_tag_cstr,
    const ifb_u32   arena_size_minimum,
          IFBArena* arena_ptr) {

    //get the pointers
    IFBEngineArenaManager* arena_manager_ptr = ifb_engine::context_handles_get_arena_manager();
    IFBEngineTagManager*   tag_manager_ptr   = ifb_engine::context_handles_get_tag_manager();

    //sanity check
    ifb_macro_assert(arena_manager_ptr);
    ifb_macro_assert(tag_manager_ptr);

    //reserve a tag
    const IFBIDTag arena_tag_id = ifb_engine::tag_manager_reserve_tag(
        tag_manager_ptr,
        arena_tag_cstr);

    //commit the arena
    const IFBIDArena arena_id = ifb_engine::arena_manager_commit_arena(
        arena_manager_ptr,
        arena_tag_id,
        arena_size_minimum);

    //read the data
    arena_ptr->id        = arena_id;
    arena_ptr->size      = ifb_engine::arena_manager_get_arena_size (arena_manager_ptr,arena_id);
    arena_ptr->start     = ifb_engine::arena_manager_get_arena_start(arena_manager_ptr,arena_id);
    arena_ptr->tag_c_str = ifb_engine::tag_manager_get_tag_c_str    (arena_manager_ptr,arena_id);

    //sanity check
    ifb_macro_assert(arena_ref.size  > 0);
    ifb_macro_assert(arena_ref.start > 0);
}


inline ifb_void
ifb_engine::core_arena_get_info(
    IFBArena* arena_ptr) {

    //get the pointers
    IFBEngineArenaManager* arena_manager_ptr = ifb_engine::context_handles_get_arena_manager();
    IFBEngineTagManager*   tag_manager_ptr   = ifb_engine::context_handles_get_tag_manager();

    //sanity check
    ifb_macro_assert(arena_manager_ptr);
    ifb_macro_assert(tag_manager_ptr);

    //read the data
    arena_ptr->size      = ifb_engine::arena_manager_get_arena_size (arena_manager_ptr,arena_ptr->id);
    arena_ptr->start     = ifb_engine::arena_manager_get_arena_start(arena_manager_ptr,arena_ptr->id);
    arena_ptr->tag_c_str = ifb_engine::tag_manager_get_tag_c_str    (arena_manager_ptr,arena_ptr->id);
}