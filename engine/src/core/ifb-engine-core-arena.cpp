#pragma once

#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-context.hpp"

inline ifb_void
ifb_engine::core_arena_commit(
    const ifb_cstr  arena_tag_cstr,
    const ifb_u32   arena_size_minimum,
          IFBArena* arena_ptr) {

    //get the pointers
    IFBEngineMemory*          memory_ptr        = ifb_engine::context_get_memory();
    IFBEngineContextManagers* managers_ptr      = ifb_engine::context_get_managers(); 
    IFBEngineTagManager*      tag_manager_ptr   = ifb_engine::context_managers_get_tag_manager(managers_ptr);
    IFBEngineArenaManager*    arena_manager_ptr = ifb_engine::context_managers_get_arena_manager(managers_ptr);

    //sanity check
    ifb_macro_assert(memory_ptr);
    ifb_macro_assert(arena_manager_ptr);
    ifb_macro_assert(tag_manager_ptr);

    //reserve a tag
    const IFBIDTag arena_tag_id = ifb_engine::tag_manager_reserve_tag(
        tag_manager_ptr,
        arena_tag_cstr);

    //commit the arena
    const IFBIDArena arena_id = ifb_engine::arena_manager_commit_arena(
        arena_manager_ptr,
        memory_ptr,
        arena_tag_id,
        arena_size_minimum);

    //read the data
    arena_ptr->id        = arena_id;
    arena_ptr->size      = ifb_engine::arena_manager_get_arena_size (arena_manager_ptr, arena_id);
    arena_ptr->start     = ifb_engine::arena_manager_get_arena_start(arena_manager_ptr, arena_id);
    arena_ptr->tag_c_str = ifb_engine::tag_manager_get_tag_c_str    (tag_manager_ptr,   arena_tag_id);

    //sanity check
    ifb_macro_assert(arena_ptr->size  > 0);
    ifb_macro_assert(arena_ptr->start > 0);
}

inline ifb_void
ifb_engine::core_arena_get_info(
    IFBArena* arena_ptr) {

    //get the pointers
    IFBEngineContextManagers* managers_ptr      = ifb_engine::context_get_managers(); 
    IFBEngineTagManager*      tag_manager_ptr   = ifb_engine::context_managers_get_tag_manager(managers_ptr);
    IFBEngineArenaManager*    arena_manager_ptr = ifb_engine::context_managers_get_arena_manager(managers_ptr);

    //sanity check
    ifb_macro_assert(arena_manager_ptr);
    ifb_macro_assert(tag_manager_ptr);

    //get the tag id
    const IFBIDTag arena_tag_id = ifb_engine::arena_manager_get_arena_tag_id(arena_manager_ptr, arena_ptr->id);
    
    //read the data
    arena_ptr->size      = ifb_engine::arena_manager_get_arena_size (arena_manager_ptr, arena_ptr->id);
    arena_ptr->start     = ifb_engine::arena_manager_get_arena_start(arena_manager_ptr, arena_ptr->id);
    arena_ptr->tag_c_str = ifb_engine::tag_manager_get_tag_c_str    (tag_manager_ptr,   arena_tag_id);
}

inline const ifb_u32
ifb_engine::core_arena_get_page_start(
    const IFBIDArena& arena_id_ref) {

    //get the pointers
    IFBEngineContextManagers* managers_ptr      = ifb_engine::context_get_managers(); 
    IFBEngineArenaManager*    arena_manager_ptr = ifb_engine::context_managers_get_arena_manager(managers_ptr);

    const ifb_u32 arena_page_start = ifb_engine::arena_manager_get_arena_start(
        arena_manager_ptr,
        arena_id_ref);

    return(arena_page_start);
}


inline const ifb_cstr
ifb_engine::core_arena_get_tag_cstr(
    const IFBIDArena& arena_id_ref) {

    //get the pointers
    IFBEngineContextManagers* managers_ptr      = ifb_engine::context_get_managers(); 
    IFBEngineArenaManager*    arena_manager_ptr = ifb_engine::context_managers_get_arena_manager(managers_ptr);
    IFBEngineTagManager*      tag_manager_ptr   = ifb_engine::context_managers_get_tag_manager(managers_ptr);

    //get the tag id
    const IFBIDTag arena_tag_id = ifb_engine::arena_manager_get_arena_tag_id(arena_manager_ptr,arena_id_ref);

    //get the tag string
    const ifb_cstr arena_tag_cstr = ifb_engine::tag_manager_get_tag_c_str(
        tag_manager_ptr,
        arena_tag_id);
    
    return(arena_tag_cstr);
}

inline const ifb_ptr
ifb_engine::core_arena_get_pointer_start(
    const IFBIDArena& arena_id_ref) {

    //get the pointers
    IFBEngineContextManagers* managers_ptr      = ifb_engine::context_get_managers(); 
    IFBEngineArenaManager*    arena_manager_ptr = ifb_engine::context_managers_get_arena_manager(managers_ptr);

    const ifb_ptr pointer = ifb_engine::arena_manager_get_arena_pointer(
        arena_manager_ptr,
        arena_id_ref);

    return(pointer);
}

inline const ifb_ptr
ifb_engine::core_arena_get_pointer_offset(
    const IFBIDArena& arena_id_ref,
    const ifb_u32     offset) {

    //get the pointers
    IFBEngineContextManagers* managers_ptr      = ifb_engine::context_get_managers(); 
    IFBEngineArenaManager*    arena_manager_ptr = ifb_engine::context_managers_get_arena_manager(managers_ptr);

    const ifb_ptr pointer = ifb_engine::arena_manager_get_arena_pointer(
        arena_manager_ptr,
        arena_id_ref,
        offset);

    return(pointer);
}