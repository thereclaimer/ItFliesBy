#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

inline const IFBArenaId
ifb_engine::core_arena_commit(
    const IFBEngineCore*   ptr_core,
    const IFBEngineMemory* ptr_memory,
    const ifb_u32          arena_size_minimum, 
    const ifb_cstr         arena_tag_c_str) {

    //get the managers
    IFBEngineArenaManager* ptr_arena_manager = ifb_engine::core_managers_get_pointer_arena_manager (ptr_core->manager_handles);
    IFBEngineTagManager*   ptr_tag_manager   = ifb_engine::core_managers_get_pointer_tag_manager   (ptr_core->manager_handles);

    //reserve the tag
    const IFBTagId arena_tag_id = ifb_engine::tag_manager_reserve_tag(
        ptr_tag_manager,
        ptr_memory,
        arena_tag_c_str);

    //commit the arena
    const IFBArenaId arena_id = ifb_engine::arena_manager_commit_arena(
        ptr_arena_manager,
        ptr_memory,
        arena_tag_id,
        arena_size_minimum);

    //we're done
    return(arena_id);
}

inline const ifb_u32 
ifb_engine::core_arena_get_size(
    const IFBEngineCore*   ptr_core, 
    const IFBEngineMemory* ptr_memory,
    const IFBArenaId       arena_id) {

    //get the managers
    IFBEngineArenaManager* ptr_arena_manager = ifb_engine::core_managers_get_pointer_arena_manager (ptr_core->manager_handles);

    //get the commit id
    const IFBMemoryCommitId arena_commit_id = ifb_engine::arena_manager_get_arena_commit_id(
        ptr_arena_manager,
        ptr_memory,
        arena_id);

    //get the commit size
    const ifb_u32 arena_commit_size = ifb_engine::memory_manager_get_commit_size(
        ptr_memory_manager,
        ptr_memory,
        arena_commit_id);

    //we're done
    return(arena_commit_size);
}

inline const ifb_cstr 
ifb_engine::core_arena_get_tag_c_str(
    const IFBEngineCore*   ptr_core, 
    const IFBEngineMemory* ptr_memory,
    const IFBArenaId       arena_id) {

    //get the managers
    IFBEngineArenaManager* ptr_arena_manager = ifb_engine::core_managers_get_pointer_tag_manager(ptr_core->manager_handles);

    //get the tag id
    const IFBTagId arena_tag_id = ifb_engine::arena_manager_get_arena_tag_id(
        ptr_arena_manager,
        ptr_memory,
        arena_id);

    //get the tag value
    const ifb_cstr tag_c_str = ifb_engine::tag_manager_get_tag_c_str(
        ptr_tag_manager,
        ptr_memory,
        tag_id);

    //we're done
    return(tag_c_str);
}

inline const ifb_ptr
ifb_engine::core_arena_get_pointer_start(
    const IFBEngineCore*   ptr_core, 
    const IFBEngineMemory* ptr_memory,
    const IFBArenaId       arena_id) {

    //get the managers
    IFBEngineArenaManager* ptr_arena_manager = ifb_engine::core_managers_get_pointer_tag_manager(ptr_core->manager_handles);

    //get the arena pointer
    const ifb_ptr arena_pointer = ifb_engine::arena_manager_get_arena_pointer(
        ptr_arena_manager,
        ptr_memory,
        arena_commit_id);

    //we're done
    return(arena_pointer);
}

inline const ifb_u32 
ifb_engine::core_arena_get_pointer_offset(
    const IFBEngineCore*   ptr_core, 
    const IFBEngineMemory* ptr_memory,
    const IFBArenaId       arena_id, 
    const ifb_u32          offset) {

    //get the managers
    IFBEngineArenaManager* ptr_arena_manager = ifb_engine::core_managers_get_pointer_tag_manager(ptr_core->manager_handles);

    //get the commit pointer
    const ifb_ptr arena_pointer = ifb_engine::arena_manager_get_arena_pointer(
        ptr_arena_manager,
        ptr_memory,
        arena_commit_id,
        offset);

    //we're done
    return(arena_pointer);
}