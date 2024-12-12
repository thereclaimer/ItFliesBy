#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-context.hpp"

inline ifb_void 
ifb_engine::arena_manager_initialize(
          IFBEngineArenaManager* arena_manager_ptr,
    const ifb_u32                arena_minimum_size,
    const ifb_u32                arena_count_max) {

    //calculate the commit size
    const ifb_u32 size_commit_id_array = ifb_macro_size_array(IFBIDCommit, arena_count_max);
    const ifb_u32 size_tag_id_array    = ifb_macro_size_array(IFBIDTag,    arena_count_max);
    const ifb_u32 commit_size          = size_commit_id_array + size_tag_id_array;

    //do the commit
    IFBEngineMemory*  engine_memory_ptr          = ifb_engine::context_handles_get_memory();
    const ifb_u32     arena_minimum_size_aligned = ifb_engine::memory_align_size_to_page(engine_memory_ptr,arena_minimum_size);
    const ifb_u32     arena_minimum_pages        = arena_minimum_size_aligned / engine_memory_ptr->system_page_size; 
    const IFBIDCommit commit_id                  = ifb_engine::memory_commit(engine_memory_ptr,commit_size);
    const ifb_address commit_start               = ifb_engine::memory_get_commit_address(engine_memory_ptr,commit_id); 

    //calculate the commit sizes for the arrays
    arena_manager_ptr->arena_minimum_size            = arena_minimum_size_aligned;
    arena_manager_ptr->arena_minimum_pages           = arena_minimum_pages;
    arena_manager_ptr->arena_count_max               = arena_count_max;
    arena_manager_ptr->arena_count_committed         = 0;
    arena_manager_ptr->commit.id                     = commit_id;
    arena_manager_ptr->commit.offset_commit_id_array = 0;
    arena_manager_ptr->commit.offset_tag_id_array    = size_commit_id_array;
    arena_manager_ptr->commit.start                  = commit_start;
}

inline const IFBIDArena 
ifb_engine::arena_manager_commit_arena(
          IFBEngineArenaManager* arena_manager_ptr,
    const IFBIDTag               arena_tag_id,
    const ifb_u32                arena_commit_size_minimum) {

    //make sure we can create the arena
    ifb_macro_assert(arena_manager_ptr->arena_count_committed != arena_manager_ptr->arena_count_max);

    //get the next arena index and update the committed count
    const ifb_index arena_index = arena_manager_ptr->arena_count_committed;
    ++arena_manager_ptr->arena_count_committed;

    //do the commit
    IFBEngineMemory* memory_ptr       = ifb_engine::context_handles_get_memory();
    const IFBIDCommit arena_commit_id = ifb_engine::memory_commit(memory_ptr,arena_commit_size_minimum);

    //get the arrays
    IFBIDCommit* commit_id_array_ptr = arena_manager_get_pointer_commit_id_array (arena_manager_ptr,memory_ptr);
    IFBIDTag*    tag_id_array_ptr    = arena_manager_get_pointer_tag_id_array    (arena_manager_ptr,memory_ptr);

    //update the arrays
    commit_id_array_ptr[arena_index] = arena_commit_id; 
    tag_id_array_ptr   [arena_index] = arena_tag_id;

    //get the id
    IFBIDArena arena_id;
    arena_id.index     = arena_index;
    arena_id.commit_id = arena_commit_id;
    arena_id.tag_id    = arena_tag_id;

    //we're done
    return(arena_id);
}

inline const ifb_u32
ifb_engine::arena_manager_align_size_to_arena(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const ifb_u32                size) {

    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(
        size,
        arena_manager_ptr->arena_minimum_size);

    return(size_aligned);
}

inline const IFBIDCommit
ifb_engine::arena_manager_get_arena_commit_id(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBIDArena             arena_id) {

    //get the memory
    const IFBEngineMemory* engine_memory_ptr = ifb_engine::context_handles_get_memory();

    //get the commit id array
    const IFBIDCommit* commit_id_array_ptr = ifb_engine::arena_manager_get_pointer_commit_id_array(
        arena_manager_ptr,
        engine_memory_ptr);

    //get the commit id
    const IFBIDCommit commit_id = commit_id_array_ptr[arena_id.index];

    //we're done
    return(commit_id);
}

inline const IFBIDTag
ifb_engine::arena_manager_get_arena_tag_id(
          const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBIDArena             arena_id) {

    //get the memory
    const IFBEngineMemory* engine_memory_ptr = ifb_engine::context_handles_get_memory();

    //get the tag id array
    const IFBIDTag* tag_id_array_ptr = ifb_engine::arena_manager_get_pointer_tag_id_array(
        arena_manager_ptr,
        engine_memory_ptr);

    //get the tag id
    const IFBIDTag tag_id = tag_id_array_ptr[arena_id.index];

    //we're done
    return(tag_id);
}

inline const ifb_u32
ifb_engine::arena_manager_get_arena_size(
          const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBIDArena             arena_id) {

    //get the memory
    const IFBEngineMemory* engine_memory_ptr = ifb_engine::context_handles_get_memory();

    //get the commit id
    const IFBIDCommit arena_commit_id = ifb_engine::arena_manager_get_arena_commit_id(
        arena_manager_ptr,
        arena_id);

    //get the commit size
    const ifb_u32 arena_commit_size = ifb_engine::memory_get_commit_size(
        engine_memory_ptr,
        arena_commit_id);

    //we're done
    return(arena_commit_size);
}

inline const ifb_ptr
ifb_engine::arena_manager_get_arena_pointer(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBIDArena             arena_id) {

    //get the commit id
    const IFBIDCommit arena_commit_id = ifb_engine::arena_manager_get_arena_commit_id(
        arena_manager_ptr,
        arena_id);

    //get the memory
    const IFBEngineMemory* engine_memory_ptr = ifb_engine::context_handles_get_memory();

    //get the commit pointer
    const ifb_ptr arena_ptr = ifb_engine::memory_get_commit_pointer(
        engine_memory_ptr,
        arena_commit_id);

    //we're done
    return(arena_ptr);
}

inline const ifb_ptr
ifb_engine::arena_manager_get_arena_pointer(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBIDArena             arena_id,
    const ifb_u32                offset) {

    //get the memory
    const IFBEngineMemory* engine_memory_ptr = ifb_engine::context_handles_get_memory();

    //get the commit id
    const IFBIDCommit arena_commit_id = ifb_engine::arena_manager_get_arena_commit_id(
        arena_manager_ptr,
        arena_id);

    //get the commit pointer
    const ifb_ptr arena_ptr = ifb_engine::memory_get_commit_pointer(
        engine_memory_ptr,
        arena_commit_id,
        offset);

    //we're done
    return(arena_ptr);
}

inline IFBIDCommit*
ifb_engine::arena_manager_get_pointer_commit_id_array(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBEngineMemory*       engine_memory_ptr) {

    IFBIDCommit* commit_id_array_ptr = (IFBIDCommit*)ifb_engine::memory_get_commit_pointer(
        engine_memory_ptr,
        arena_manager_ptr->commit.id,
        arena_manager_ptr->commit.offset_commit_id_array);

    return(commit_id_array_ptr);
}

inline IFBIDTag*
ifb_engine::arena_manager_get_pointer_tag_id_array(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBEngineMemory*       engine_memory_ptr) {

    IFBIDTag* tag_id_array_ptr = (IFBIDTag*)ifb_engine::memory_get_commit_pointer(
        engine_memory_ptr,
        arena_manager_ptr->commit.id,
        arena_manager_ptr->commit.offset_tag_id_array);

    return(tag_id_array_ptr);
}