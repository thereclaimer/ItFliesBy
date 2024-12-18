#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-context.hpp"

inline ifb_void 
ifb_engine::arena_manager_initialize(
          IFBEngineArenaManager* arena_manager_ptr,
          IFBEngineMemory*       memory_ptr,
    const ifb_u32                arena_minimum_size,
    const ifb_u32                arena_count_max) {

    //align the minimum arena size
    const ifb_u32 arena_minimum_size_aligned = ifb_engine::memory_align_size_to_page(memory_ptr,arena_minimum_size);
    const ifb_u32 arena_minimum_pages        = ifb_engine::memory_get_page_count(memory_ptr,arena_minimum_size_aligned); 
    
    //calculate the commit size
    const ifb_u32 size_commit_id_array = ifb_macro_size_array(IFBIDCommit, arena_count_max);
    const ifb_u32 size_tag_id_array    = ifb_macro_size_array(IFBIDTag,    arena_count_max);
    const ifb_u32 size_arena_start     = ifb_macro_size_array(ifb_address, arena_count_max);
    const ifb_u32 size_arena_size      = ifb_macro_size_array(ifb_u32,     arena_count_max); //lol
    const ifb_u32 commit_size          = size_commit_id_array + size_tag_id_array;

    //do the commit
    const IFBIDCommit commit_id    = ifb_engine::memory_commit(memory_ptr,commit_size);
    const ifb_address commit_start = ifb_engine::memory_get_commit_address(memory_ptr,commit_id); 

    //set the properties
    arena_manager_ptr->memory.start                  = commit_start;
    arena_manager_ptr->memory.offset_commit_id_array = 0;
    arena_manager_ptr->memory.offset_tag_id_array    = size_commit_id_array;
    arena_manager_ptr->memory.offset_arena_start     = size_arena_start;
    arena_manager_ptr->memory.offset_arena_size      = size_arena_size;
    arena_manager_ptr->memory.commit_id              = commit_id;
    arena_manager_ptr->arena_minimum_size            = arena_minimum_size_aligned;
    arena_manager_ptr->arena_minimum_pages           = arena_minimum_pages;
    arena_manager_ptr->arena_count_max               = arena_count_max;
    arena_manager_ptr->arena_count_committed         = 0;
}

inline const IFBIDArena 
ifb_engine::arena_manager_commit_arena(
          IFBEngineArenaManager* arena_manager_ptr,
          IFBEngineMemory*       memory_ptr,
    const IFBIDTag               arena_tag_id,
    const ifb_u32                arena_commit_size_minimum) {

    //make sure we can create the arena
    ifb_macro_assert(arena_manager_ptr->arena_count_committed != arena_manager_ptr->arena_count_max);

    //get the next arena index and update the committed count
    const ifb_index arena_index = arena_manager_ptr->arena_count_committed;
    ++arena_manager_ptr->arena_count_committed;

    //do the commit
    const IFBIDCommit arena_commit_id = ifb_engine::memory_commit(memory_ptr,arena_commit_size_minimum);

    //get the arrays
    IFBIDCommit* commit_id_array_ptr   = ifb_engine::arena_manager_get_pointer_commit_id_array   (arena_manager_ptr->memory);
    IFBIDTag*    tag_id_array_ptr      = ifb_engine::arena_manager_get_pointer_tag_id_array      (arena_manager_ptr->memory);
    ifb_address* arena_start_array_ptr = ifb_engine::arena_manager_get_pointer_arena_start_array (arena_manager_ptr->memory);
    ifb_u32*     arena_size_array_ptr  = ifb_engine::arena_manager_get_pointer_arena_size_array  (arena_manager_ptr->memory);

    //update the arrays
    commit_id_array_ptr   [arena_index] = arena_commit_id; 
    tag_id_array_ptr      [arena_index] = arena_tag_id;
    arena_start_array_ptr [arena_index] = ifb_engine::memory_get_commit_address(memory_ptr,arena_commit_id); 
    arena_size_array_ptr  [arena_index] = ifb_engine::memory_get_commit_size(memory_ptr,arena_commit_id);     

    //get the id
    IFBIDArena arena_id;
    arena_id.index = arena_index;

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
    const IFBIDArena&            arena_id) {

    //get the commit id array
    const IFBIDCommit* commit_id_array_ptr = ifb_engine::arena_manager_get_pointer_commit_id_array(
        arena_manager_ptr->memory);

    //get the commit id
    const IFBIDCommit commit_id = commit_id_array_ptr[arena_id.index];

    //we're done
    return(commit_id);
}

inline const IFBIDTag
ifb_engine::arena_manager_get_arena_tag_id(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBIDArena&            arena_id) {

    //get the tag id array
    const IFBIDTag* tag_id_array_ptr = ifb_engine::arena_manager_get_pointer_tag_id_array(
        arena_manager_ptr->memory);

    //get the tag id
    const IFBIDTag tag_id = tag_id_array_ptr[arena_id.index];

    //we're done
    return(tag_id);
}

inline const ifb_u32
ifb_engine::arena_manager_get_arena_size(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBIDArena&            arena_id) {

    const ifb_u32* arena_size_array_ptr = ifb_engine::arena_manager_get_pointer_arena_size_array(arena_manager_ptr->memory);
    const ifb_u32  arena_size           = arena_size_array_ptr[arena_id.index];

    //we're done
    return(arena_size);
}

inline const ifb_ptr
ifb_engine::arena_manager_get_arena_pointer(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBIDArena&            arena_id) {

    const ifb_address* arena_start_array_ptr = ifb_engine::arena_manager_get_pointer_arena_start_array (arena_manager_ptr->memory);
    const ifb_address  arena_start           = arena_start_array_ptr[arena_id.index]; 
    const ifb_ptr      arena_start_pointer   = (ifb_ptr)arena_start;

    //we're done
    return(arena_start_pointer);
}

inline const ifb_ptr
ifb_engine::arena_manager_get_arena_pointer(
    const IFBEngineArenaManager* arena_manager_ptr, 
    const IFBIDArena&            arena_id,
    const ifb_u32                offset) {

    const ifb_address* arena_start_array_ptr = ifb_engine::arena_manager_get_pointer_arena_start_array (arena_manager_ptr->memory);
    const ifb_address  arena_start           = arena_start_array_ptr[arena_id.index]; 
    const ifb_address  arena_offset          = arena_start + offset;
    const ifb_ptr      arena_start_pointer   = (ifb_ptr)arena_offset;

    //we're done
    return(arena_start_pointer);
}

inline IFBIDCommit*
ifb_engine::arena_manager_get_pointer_commit_id_array(
    const IFBEngineArenaManagerMemory& arena_manager_memory_ref){

    //get the array address
    const ifb_address memory_start          = arena_manager_memory_ref.start;
    const ifb_address commit_id_array_start = memory_start + arena_manager_memory_ref.offset_commit_id_array;

    //cast the address to a pointer
    IFBIDCommit* commit_id_array_ptr = (IFBIDCommit*)commit_id_array_start;

    //we're done
    return(commit_id_array_ptr);
}

inline IFBIDTag*
ifb_engine::arena_manager_get_pointer_tag_id_array(
    const IFBEngineArenaManagerMemory& arena_manager_memory_ref) {

    const ifb_address memory_start       = arena_manager_memory_ref.start;
    const ifb_address tag_id_array_start = memory_start + arena_manager_memory_ref.offset_tag_id_array;

    //cast the address to a pointer
    IFBIDTag* tag_id_array_ptr = (IFBIDTag*)tag_id_array_start;

    //we're done
    return(tag_id_array_ptr);
}

inline ifb_address* 
ifb_engine::arena_manager_get_pointer_arena_start_array(
    const IFBEngineArenaManagerMemory& arena_manager_memory_ref) {

    const ifb_address memory_start            = arena_manager_memory_ref.start;
    const ifb_address arena_start_array_start = memory_start + arena_manager_memory_ref.offset_arena_start; //lol

    //cast the address to a pointer
    ifb_address* arena_start_array_ptr = (ifb_address*)arena_start_array_start;

    //we're done
    return(arena_start_array_ptr);
}

inline ifb_u32*     
ifb_engine::arena_manager_get_pointer_arena_size_array(
    const IFBEngineArenaManagerMemory& arena_manager_memory_ref) {

    const ifb_address memory_start           = arena_manager_memory_ref.start;
    const ifb_address arena_size_array_start = memory_start + arena_manager_memory_ref.offset_arena_size;

    //cast the address to a pointer
    ifb_u32* arena_size_array_ptr = (ifb_u32*)arena_size_array_start;

    //we're done
    return(arena_size_array_ptr);
}
