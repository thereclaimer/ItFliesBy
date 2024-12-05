#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

inline const IFBArenaId
ifb_engine::core_arena_commit(
          IFBEngineCore* ptr_core, 
    const ifb_u32        arena_size_minimum, 
    const ifb_cstr       arena_tag_c_str) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_core->manager_handles); 
    IFBEngineArenaManager*  ptr_arena_manager  = ifb_engine::core_managers_get_pointer_arena_manager (ptr_core->manager_handles);
    IFBEngineTagManager*    ptr_tag_manager    = ifb_engine::core_managers_get_pointer_tag_manager   (ptr_core->manager_handles);

    //create the tag
    const IFBTagId arena_tag_id = ifb_engine::tag_manager_reserve_tag(
        ptr_tag_manager,
        arena_tag_c_str);

    //align the size to the arena
    const ifb_u32 arena_size_aligned = ifb_engine::arena_manager_align_size_to_arena(
        ptr_arena_manager,
        arena_size_minimum);

    //do the commit
    const IFBMemoryCommitId arena_commit_id = ifb_engine::memory_manager_commit(
        ptr_memory_manager,
        arena_size_aligned);

    //create the arena
    const IFBArenaId arena_id = ifb_engine::arena_manager_create_arena(
        ptr_arena_manager,
        arena_commit_id,
        arena_tag_id);

    //we're done
    return(arena_id);
}

inline const ifb_u32 
ifb_engine::core_arena_get_size(
          IFBEngineCore* ptr_core, 
    const IFBArenaId     arena_id) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_core->manager_handles); 
    IFBEngineArenaManager*  ptr_arena_manager  = ifb_engine::core_managers_get_pointer_arena_manager (ptr_core->manager_handles);

    //get the commit id
    const IFBMemoryCommitId arena_commit_id = ifb_engine::arena_manager_get_arena_commit_id(
        ptr_arena_manager,
        arena_id);

    //get the commit size
    const ifb_u32 arena_commit_size = ifb_engine::memory_manager_get_commit_size(
        ptr_memory_manager,
        arena_commit_id);

    //we're done
    return(arena_commit_size);
}

inline const ifb_cstr 
ifb_engine::core_arena_get_tag_c_str(
          IFBEngineCore* ptr_core, 
    const IFBArenaId     arena_id) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_core->manager_handles); 
    IFBEngineArenaManager*  ptr_arena_manager  = ifb_engine::core_managers_get_pointer_tag_manager   (ptr_core->manager_handles);

    //get the tag id
    const IFBTagId arena_tag_id = ifb_engine::arena_manager_get_arena_tag_id(
        ptr_arena_manager,
        arena_id);

    //get the tag value
    const ifb_cstr tag_c_str = ifb_engine::tag_manager_get_tag_c_str(
        ptr_tag_manager,
        tag_id);

    //we're done
    return(tag_c_str);
}

inline const ifb_ptr
ifb_engine::core_arena_get_pointer_start(
          IFBEngineCore* ptr_core, 
    const IFBArenaId     arena_id) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_core->manager_handles); 
    IFBEngineArenaManager*  ptr_arena_manager  = ifb_engine::core_managers_get_pointer_tag_manager   (ptr_core->manager_handles);

    //get the commit id
    const IFBMemoryCommitId arena_commit_id = ifb_engine::arena_manager_get_arena_commit_id(
        ptr_arena_manager,
        arena_id);

    //get the commit start
    ifb_ptr arena_commit_start = ifb_engine::memory_manager_get_commit_pointer(
        ptr_memory_manager,
        arena_commit_id);

    //we're done
    return(arena_commit_id);
}

inline const ifb_u32 
ifb_engine::core_arena_get_pointer_offset(
          IFBEngineCore* ptr_core, 
    const IFBArenaId     arena_id, 
    const ifb_u32        offset) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_core->manager_handles); 
    IFBEngineArenaManager*  ptr_arena_manager  = ifb_engine::core_managers_get_pointer_tag_manager   (ptr_core->manager_handles);

    //get the commit id
    const IFBMemoryCommitId arena_commit_id = ifb_engine::arena_manager_get_arena_commit_id(
        ptr_arena_manager,
        arena_id);

    //get the commit offset
    ifb_ptr arena_commit_offset = ifb_engine::memory_manager_get_commit_pointer(
        ptr_memory_manager,
        arena_commit_id,
        offset);

    //we're done
    return(arena_commit_offset);
}