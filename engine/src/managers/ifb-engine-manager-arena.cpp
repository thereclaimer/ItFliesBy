#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-context.hpp"

inline const IFBIDArena 
ifb_engine::arena_manager_commit_arena(
          IFBEngineManagerArena* arena_manager_ptr,
          IFBEngineMemory*       memory_ptr,
    const IFBIDTag               arena_tag_id,
    const ifb_u32                arena_commit_size_minimum) {

    //make sure we can create the arena
    ifb_macro_assert(arena_manager_ptr->arena_count_committed != arena_manager_ptr->arena_count_max);

    //get the data
    IFBEngineManagerArenaData arena_data;
    arena_data.query = (
        IFBEngineManagerArenaQuery_CommitId   |
        IFBEngineManagerArenaQuery_TagId      |
        IFBEngineManagerArenaQuery_ArenaStart |
        IFBEngineManagerArenaQuery_ArenaSize); 

    ifb_engine::arena_manager_data_query(arena_manager_ptr,arena_data);

    //get the next arena index and update the committed count
    const ifb_index arena_index = arena_manager_ptr->arena_count_committed;
    ++arena_manager_ptr->arena_count_committed;

    //get the id
    IFBIDArena arena_id;
    arena_id.index = arena_index;

    //do the commit and get the size and address
    const IFBIDCommit arena_commit_id    = ifb_engine::memory_commit(memory_ptr,arena_commit_size_minimum);
    const ifb_address arena_commit_start = ifb_engine::memory_get_commit_address(memory_ptr,arena_commit_id);
    const ifb_u32     arena_commit_size  = ifb_engine::memory_get_commit_size(memory_ptr,arena_commit_id);
    
    //update the data
    ifb_engine::arena_manager_data_set_commit_id  (arena_data, arena_id, arena_commit_id);
    ifb_engine::arena_manager_data_set_tag_id     (arena_data, arena_id, arena_tag_id);
    ifb_engine::arena_manager_data_set_arena_start(arena_data, arena_id, arena_commit_start);
    ifb_engine::arena_manager_data_set_arena_size (arena_data, arena_id, arena_commit_size);

    //we're done
    return(arena_id);
}

inline const ifb_u32
ifb_engine::arena_manager_align_size_to_arena(
    const IFBEngineManagerArena* arena_manager_ptr, 
    const ifb_u32                size) {

    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(
        size,
        arena_manager_ptr->arena_minimum_size);

    return(size_aligned);
}

inline const IFBIDCommit
ifb_engine::arena_manager_get_arena_commit_id(
    const IFBEngineManagerArena* arena_manager_ptr, 
    const IFBIDArena             arena_id) {

    //get the commit id array
    IFBEngineManagerArenaData arena_data;
    arena_data.query = IFBEngineManagerArenaQuery_CommitId;
    ifb_engine::arena_manager_data_query(arena_manager_ptr,arena_data);

    //get the commit id
    const IFBIDCommit commit_id = ifb_engine::arena_manager_data_get_commit_id(arena_data,arena_id);

    //we're done
    return(commit_id);
}

inline const IFBIDTag
ifb_engine::arena_manager_get_arena_tag_id(
    const IFBEngineManagerArena* arena_manager_ptr, 
    const IFBIDArena             arena_id) {

    //get the tag id array
    IFBEngineManagerArenaData arena_data;
    arena_data.query = IFBEngineManagerArenaQuery_TagId;
    ifb_engine::arena_manager_data_query(arena_manager_ptr,arena_data);

    //get the tag id
    const IFBIDTag tag_id = ifb_engine::arena_manager_data_get_tag_id(arena_data,arena_id);

    //we're done
    return(tag_id);
}

inline const ifb_u32
ifb_engine::arena_manager_get_arena_size(
    const IFBEngineManagerArena* arena_manager_ptr, 
    const IFBIDArena             arena_id) {
    
    //get the arena size array
    IFBEngineManagerArenaData arena_data;
    arena_data.query = IFBEngineManagerArenaQuery_ArenaSize;
    ifb_engine::arena_manager_data_query(arena_manager_ptr,arena_data);

    //get the arena size
    const ifb_u32 arena_size = ifb_engine::arena_manager_data_get_arena_size(arena_data,arena_id);

    //we're done
    return(arena_size);
}

inline const ifb_address
ifb_engine::arena_manager_get_arena_start(
    const IFBEngineManagerArena* arena_manager_ptr,
    const IFBIDArena             arena_id) {
    
    //get the arena start array
    IFBEngineManagerArenaData arena_data;
    arena_data.query = IFBEngineManagerArenaQuery_ArenaStart;
    ifb_engine::arena_manager_data_query(arena_manager_ptr,arena_data);

    //get the arena start
    const ifb_address arena_start = ifb_engine::arena_manager_data_get_arena_start(arena_data,arena_id);

    //we're done
    return(arena_start);
}

inline const ifb_ptr
ifb_engine::arena_manager_get_arena_pointer(
    const IFBEngineManagerArena* arena_manager_ptr, 
    const IFBIDArena             arena_id) {

    //get the starting address
    const ifb_address arena_start = ifb_engine::arena_manager_get_arena_start(
        arena_manager_ptr,
        arena_id);

    //cast the address to a pointer
    const ifb_ptr arena_pointer = (ifb_ptr)arena_start;

    //we're done
    return(arena_start_pointer);
}

inline const ifb_ptr
ifb_engine::arena_manager_get_arena_pointer(
    const IFBEngineManagerArena* arena_manager_ptr, 
    const IFBIDArena             arena_id,
    const ifb_u32                offset) {

    //get the starting address
    const ifb_address arena_start = ifb_engine::arena_manager_get_arena_start(
        arena_manager_ptr,
        arena_id);

    //add the offset to the address
    const ifb_address arena_offset = arena_start + offset; 

    //cast the address to a pointer
    const ifb_ptr arena_pointer = (ifb_ptr)arena_offset;

    //we're done
    return(arena_pointer);
}

inline ifb_void 
ifb_engine::arena_manager_data_query(
    const IFBEngineManagerArena*     arena_manager_ptr,
          IFBEngineManagerArenaData& arena_manager_data_ref) {

    //get the data starting address
    const IFBEngineManagerArenaQuery query = arena_manager_data_ref.query;
    const ifb_address arena_data_start = arena_manager_ptr->start; 

    //get the addresses of our requested data
    const ifb_address address_commit_id_array = (query & IFBEngineManagerArenaQuery_CommitId)   ? arena_data_start + arena_manager_ptr->offset_commit_id_array : 0; 
    const ifb_address address_tag_id_array    = (query & IFBEngineManagerArenaQuery_TagId)      ? arena_data_start + arena_manager_ptr->offset_tag_id_array    : 0;
    const ifb_address address_arena_start     = (query & IFBEngineManagerArenaQuery_ArenaStart) ? arena_data_start + arena_manager_ptr->offset_arena_start     : 0;
    const ifb_address address_arena_size      = (query & IFBEngineManagerArenaQuery_ArenaSize)  ? arena_data_start + arena_manager_ptr->offset_arena_size      : 0;

    //cast the pointers
    arena_manager_data_ref.array_commit_id = (IFBIDCommit*)address_commit_id_array;
    arena_manager_data_ref.array_tag_id    =    (IFBIDTag*)address_tag_id_array;
    arena_manager_data_ref.array_start     = (ifb_address*)address_arena_start;
    arena_manager_data_ref.array_size      =     (ifb_u32*)address_arena_size;
}


inline const IFBIDCommit
ifb_engine::arena_manager_data_get_commit_id(
    const IFBEngineManagerArenaData& arena_manager_data_ref,
    const IFBIDArena                 arena_id) {

    return(arena_manager_data_ref.array_commit_id[arena_id.index]);
}

inline const IFBIDTag
ifb_engine::arena_manager_data_get_tag_id(
    const IFBEngineManagerArenaData& arena_manager_data_ref,
    const IFBIDArena                 arena_id) {

    return(arena_manager_data_ref.array_tag_id[arena_id.index]);
}

inline const ifb_address
ifb_engine::arena_manager_data_get_arena_start(
    const IFBEngineManagerArenaData& arena_manager_data_ref,
    const IFBIDArena                 arena_id) {

    return(arena_manager_data_ref.array_start[arena_id.index]);
}

inline const ifb_u32
ifb_engine::arena_manager_data_get_arena_size(
    const IFBEngineManagerArenaData& arena_manager_data_ref,
    const IFBIDArena                 arena_id) {

    return(arena_manager_data_ref.array_size[arena_id.index]);
}   

ifb_void arena_manager_data_set_commit_id   (IFBEngineManagerArenaData& arena_manager_data_ref, const IFBIDArena arena_id, const IFBIDCommit commit_id);
ifb_void arena_manager_data_set_tag_id      (IFBEngineManagerArenaData& arena_manager_data_ref, const IFBIDArena arena_id, const IFBIDTag    tag_id);
ifb_void arena_manager_data_set_arena_start (IFBEngineManagerArenaData& arena_manager_data_ref, const IFBIDArena arena_id, const ifb_address start);
ifb_void arena_manager_data_set_arena_size  (IFBEngineManagerArenaData& arena_manager_data_ref, const IFBIDArena arena_id, const ifb_u32     arena_size);   