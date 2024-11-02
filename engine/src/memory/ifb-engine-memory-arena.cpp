#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

ifb_external const ifb_b8
ifb_engine::memory_arena_create_pool(
    const ifb_cstr                     in_arena_tag,
    const ifb_size                     in_arena_size,
    const ifb_size                     in_arena_count,
          IFBEngineMemoryArena&       out_arena_start_ref) {

    ifb_b8 result = true;
    
    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //create the header
    const IFBEngineMemoryTableIndexArenaHeader arena_header_index = ifb_engine::memory_arena_header_create(
        in_arena_tag,
        in_arena_size,
        in_arena_count,
        memory_manager_ref.reservation,
        memory_manager_ref.arena_tables.header);

    //create the batch of arenas
    const IFBEngineMemoryTableIndexArenaDetail starting_arena_detail_index = 
    ifb_engine::memory_arena_detail_table_insert(
        in_arena_count,
        arena_header_index,
        memory_manager_ref.arena_tables.detail);

    //initialize the struct
    out_arena_start_ref.header_index = arena_header_index;
    out_arena_start_ref.detail_index = starting_arena_detail_index;

    //we're done
    return(true);
}

ifb_external const ifb_memory
ifb_engine::memory_arena_commit(
    IFBEngineMemoryArena&  in_arena_start,
    IFBEngineMemoryArena& out_arena_committed) {

    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //start the committed arena as invalid
    out_arena_committed.detail_index = IFB_ENGINE_MEMORY_ARENA_DETAIL_INDEX_INVALID;
    out_arena_committed.header_index = IFB_ENGINE_MEMORY_ARENA_HEADER_INDEX_INVALID;

    //validate the arena
    const ifb_b8 arena_valid = ifb_engine::memory_arena_validate(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        in_arena_start);

    //if its invalid, we're done
    if (!arena_valid) {
        return(NULL);
    }

    //the arena is valid, so we're going to set the committed arena header
    out_arena_committed.header_index = in_arena_start.header_index;

    //get the next available arena index
    out_arena_committed.detail_index = ifb_engine::memory_arena_detail_next_available_index(
        memory_manager_ref.arena_tables.detail,
        in_arena_start.detail_index,
        in_arena_start.header_index);

    //if no arena is available, we're done
    if (!ifb_engine::memory_arena_detail_valid(out_arena_committed)) {
        return(NULL);
    }

    //get the arena size offset
    IFBEngineMemoryArenaSizeAndOffset arena_size_offset;
    ifb_engine::memory_arena_size_and_offset(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        out_arena_committed,
        arena_size_offset);

    //commit the arena_memory
    const ifb_memory arena_memory = ifb_engine::memory_manager_page_commit(
        memory_manager_ref,
        arena_size_offset.size,
        arena_size_offset.offset);

    //if that worked, set this arena as committed
    ifb_engine::memory_arena_detail_committed_set_true(
        memory_manager_ref.arena_tables.detail,
        out_arena_committed.detail_index);

    //we're done
    return(arena_memory);
}

ifb_external const ifb_b8 
ifb_engine::memory_arena_decommit(
    IFBEngineMemoryArena& arena_ref) {

    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //validate the pre-committed arena
    IFBEngineMemoryArenaSizeAndOffset arena_size_and_offset;
    const ifb_b8 arena_valid = ifb_engine::memory_arena_validate_commit(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        arena_ref,
        arena_size_and_offset);

    if (!arena_valid) {
        return(false);
    }

    //decommit the memory
    const ifb_b8 result = ifb_engine::memory_manager_page_decommit(
        memory_manager_ref,
        arena_size_and_offset.size,
        arena_size_and_offset.offset);

    //if that worked, update the arena detail
    if (result) {

        ifb_engine::memory_arena_detail_committed_set_false(
            memory_manager_ref.arena_tables.detail,
            arena_ref.detail_index);
    }

    //we're done
    return(result);
}

ifb_external const ifb_memory 
ifb_engine::memory_arena_push(
          IFBEngineMemoryArena& arena_ref, 
    const ifb_size              size) {

    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //validate the pre-committed arena
    IFBEngineMemoryArenaSizeAndOffset arena_size_and_offset;
    const ifb_b8 arena_valid = ifb_engine::memory_arena_validate_commit(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        arena_ref,
        arena_size_and_offset);

    //get the current used size
    const ifb_size arena_used_size_current = ifb_engine::memory_arena_detail_size_used(
        memory_manager_ref.arena_tables.detail,
        arena_ref.detail_index);

    //make sure that the arena can fit this push
    const ifb_size arena_used_size_new = arena_used_size_current + size;
    if (arena_used_size_new > arena_size_and_offset.size) {
        
        //if we can't, we're done    
        return(NULL);
    }

    // add the current used size and arena offset to the reservation 
    // to get the pointer at the start of this push
    const ifb_size   arena_push_offset = arena_size_and_offset.offset + arena_used_size_new;   
    const ifb_memory arena_push_memory = ifb_engine::memory_reservation_get_pointer(
        memory_manager_ref.reservation,
        arena_push_offset);

    //add the push size to the detail table
    ifb_engine::memory_arena_detail_used_size_update(
        memory_manager_ref.arena_tables.detail,
        arena_ref.detail_index,
        arena_used_size_new);

    //we're done
    return(arena_push_memory);
}

ifb_external const ifb_memory 
ifb_engine::memory_arena_pull(
          IFBEngineMemoryArena& arena_ref, 
    const ifb_size              size) {
    return(NULL);

    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //validate the pre-committed arena
    IFBEngineMemoryArenaSizeAndOffset arena_size_and_offset;
    const ifb_b8 arena_valid = ifb_engine::memory_arena_validate_commit(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        arena_ref,
        arena_size_and_offset);

    //if the arena is not valid or committed, we're done
    if (!arena_valid) {
        return(NULL);
    }
    
    //get the current used size
    const ifb_size arena_used_size_current = ifb_engine::memory_arena_detail_size_used(
        memory_manager_ref.arena_tables.detail,
        arena_ref.detail_index);

    //make sure we can do this pull
    if (arena_used_size_current < size) {
        return(NULL);
    }

    //calculate the new used size
    const ifb_size arena_used_size_new = arena_used_size_current - size;

    //subtract the pull size from the page start to get the pointer to the memory after the pull
    const ifb_size   arena_pull_offset = arena_size_and_offset.offset + arena_used_size_new;   
    const ifb_memory arena_pull_memory = ifb_engine::memory_reservation_get_pointer(
        memory_manager_ref.reservation,
        arena_pull_offset);

    //update the arena detail table
    ifb_engine::memory_arena_detail_used_size_update(
        memory_manager_ref.arena_tables.detail,
        arena_ref.detail_index,
        arena_used_size_new);

    //we're done
    return(arena_pull_memory);
}

ifb_external const ifb_memory 
ifb_engine::memory_arena_push_aligned(
          IFBEngineMemoryArena& arena_ref, 
    const ifb_size              size, 
    const ifb_size              alignment) {
    
    //calculate the aligned push size
    const ifb_size push_size_aligned = ifb_engine_macro_align_a_to_b(size,alignment);

    //do the push 
    const ifb_memory arena_memory_push = ifb_engine::memory_arena_push(arena_ref,push_size_aligned);

    //we're done
    return(arena_memory_push);
}

ifb_external const ifb_memory 
ifb_engine::memory_arena_pull_aligned(
          IFBEngineMemoryArena& arena_ref, 
    const ifb_size              size, 
    const ifb_size              alignment) {
    
    //calculate the aligned pull size
    const ifb_size pull_size_aligned = ifb_engine_macro_align_a_to_b(size,alignment);

    //do the pull
    const ifb_memory arena_memory_pull = ifb_engine::memory_arena_pull(arena_ref,pull_size_aligned);

    //we're done
    return(arena_memory_pull);
}

/**********************************************************************************/
/* INLINE METHODS                                                                 */
/**********************************************************************************/

inline const ifb_b8
ifb_engine::memory_arena_validate(
    IFBEngineMemoryTableArenaHeader& arena_table_header_ref,
    IFBEngineMemoryArenaDetailTable& arena_table_detail_ref,
    IFBEngineMemoryArena&            arena_ref) {

    ifb_b8 arena_valid = true;

    //valid indexes
    arena_valid &= ifb_engine::memory_arena_header_valid(arena_ref);
    arena_valid &= ifb_engine::memory_arena_detail_valid(arena_ref);
    
    //indexes fit in table
    arena_valid &= arena_ref.header_index <= arena_table_header_ref.header_count_current;
    arena_valid &= arena_ref.detail_index <= arena_table_detail_ref.arena_count_current;
    
    //the arena header and detail match what's in the detail table
    const IFBEngineMemoryTableIndexArenaHeader arena_detail_header_index =
        ifb_engine::memory_arena_detail_header_index(
            arena_table_detail_ref,
            arena_ref.detail_index);

    arena_valid &=  arena_detail_header_index == arena_ref.header_index;

    //we're done
    return(arena_valid);
}

inline const ifb_b8
ifb_engine::memory_arena_validate_commit(
    IFBEngineMemoryTableArenaHeader&    in_arena_table_header_ref,
    IFBEngineMemoryArenaDetailTable&    in_arena_table_detail_ref,
    IFBEngineMemoryArena&               in_arena_ref,
    IFBEngineMemoryArenaSizeAndOffset& out_arena_size_and_offset_ref) {

    //base validation
    ifb_b8 result = ifb_engine::memory_arena_validate(
        in_arena_table_header_ref,
        in_arena_table_detail_ref,
        in_arena_ref);
    
    //make sure the arena is committed
    result &= ifb_engine::memory_arena_detail_committed(
        in_arena_table_detail_ref,
        in_arena_ref.detail_index);
    
    //get the size and offset
    ifb_engine::memory_arena_size_and_offset(
        in_arena_table_header_ref,
        in_arena_table_detail_ref,
        in_arena_ref,
        out_arena_size_and_offset_ref);

    //we're done
    return(result);
}

inline const ifb_void
ifb_engine::memory_arena_size_and_offset(
    IFBEngineMemoryTableArenaHeader&    in_arena_table_header_ref,
    IFBEngineMemoryArenaDetailTable&    in_arena_table_detail_ref,        
    IFBEngineMemoryArena&               in_arena_ref,
    IFBEngineMemoryArenaSizeAndOffset& out_arena_size_offset_ref) {

    const ifb_size  arena_header_offset = ifb_engine::memory_arena_header_offset(in_arena_table_header_ref,in_arena_ref.header_index);
    const ifb_index arena_pool_index    = ifb_engine::memory_arena_detail_pool_index(in_arena_table_detail_ref,in_arena_ref.detail_index); 

    out_arena_size_offset_ref.size   = ifb_engine::memory_arena_header_arena_size(in_arena_table_header_ref,in_arena_ref.header_index);
    out_arena_size_offset_ref.offset = arena_header_offset + (out_arena_size_offset_ref.size * arena_pool_index);
}
