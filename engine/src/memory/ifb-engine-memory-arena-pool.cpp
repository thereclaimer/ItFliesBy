#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

ifb_internal const ifb_b8 
ifb_engine::memory_arena_pool_table_create(
    IFBEngineMemoryArenaPoolTable& arena_pool_table_ref) {

    arena_pool_table_ref = {0};
    arena_pool_table_ref.pool_count_max = IFB_ENGINE_MEMORY_ARENA_POOL_COUNT_MAX;

    return(true);
}

ifb_external const ifb_b8 
ifb_engine::memory_arena_pool_create(
    IFBEngineMemoryArenaPool& arena_pool_ref) {

    //get the memory manager
    IFBEngineMemoryManager&        memory_manager_ref   = ifb_engine::memory_manager_ref();
    IFBEngineMemoryReservation&    reservation_ref      = memory_manager_ref.reservation; 
    IFBEngineMemoryArenaPoolTable& arena_pool_table_ref = memory_manager_ref.tables.arena_pool; 
    IFBEngineMemoryArenaTable&     arena_table_ref      = memory_manager_ref.tables.arena;

    //calculate sizes
    const ifb_size arena_size_aligned = ifb_engine_memory_align_to_arena(arena_pool_ref.arena_size);
    const ifb_size arena_pool_size    = arena_size_aligned * arena_pool_ref.arena_count; 
    const ifb_size arena_pool_offset  = (ifb_address)reservation_ref.start - reservation_ref.size_used; 
    const ifb_size new_size_used      = reservation_ref.size_used + arena_pool_size; 

    //sanity check
    if (
        arena_pool_ref.tag         == NULL         ||                                     // tag is not null
        arena_pool_ref.arena_count == 0            ||                                     // at least one arena
        new_size_used > reservation_ref.size_total ||                                     // the pool isn't too big
        arena_pool_table_ref.pool_count_current == arena_pool_table_ref.pool_count_max) { // we have a slot in the table

        arena_pool_ref.index = IFB_ENGINE_MEMORY_ARENA_POOL_INDEX_INVALID;  
        return(false);
    }

    //get the new index and update the pool count
    arena_pool_ref.index = arena_pool_table_ref.pool_count_current;    
    ++arena_pool_table_ref.pool_count_current;

    //create the batch of arenas
    const IFBEngineMemoryArenaIndex starting_arena_index = ifb_engine::memory_arena_create_batch(
        arena_table_ref,
        new_arena_pool_index,
        arena_pool_ref.arena_count);

    //get the tag length
    const ifb_size tag_length = strnlen_s(arena_pool_ref.tag,IFB_ENGINE_MEMORY_ARENA_POOL_TAG_LENGTH);

    //get the offset for the tag buffer
    const ifb_size tag_offset = 
        IFB_ENGINE_MEMORY_ARENA_POOL_TAG_LENGTH * 
        new_arena_pool_index;

    //copy the tag
    memmove(
        &arena_pool_table_ref.tag_buffer[tag_offset],
        arena_pool_ref.tag,
        tag_length);

    //update the table at the new index
    arena_pool_table_ref.columns.array_arena_size [new_arena_pool_index] = arena_size_aligned;
    arena_pool_table_ref.columns.array_arena_count[new_arena_pool_index] = arena_pool_ref.arena_count;
    arena_pool_table_ref.columns.array_offset     [new_arena_pool_index] = arena_pool_offset;

    //we're done
    return(true);
}