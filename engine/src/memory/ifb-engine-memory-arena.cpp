#pragma once

#include "ifb-engine-internal-memory.hpp"

r_internal const IFBEngineMemoryArenaIndex
ifb_engine::memory_arena_create_batch(
          IFBEngineMemoryArenaTable&    arena_table_ref,
    const IFBEngineMemoryArenaPoolIndex arena_pool_index,
    const ifb_u32                       arena_count) {

    //get the starting arena index
    const IFBEngineMemoryArenaIndex starting_arena_index = arena_table_ref.arena_count_current;

    //if we can't fit this number of arenas, we're done
    const ifb_size arena_count_new = starting_arena_index + arena_count;
    if (arena_count_new > arena_table_ref.arena_count_max) {
        return(IFB_ENGINE_MEMORY_ARENA_INDEX_INVALID);
    }

    //initialize these arenas
    for (
        IFBEngineMemoryArenaIndex arena_index = starting_arena_index;
        arena_index < arena_count_new;
        ++arena_index) {
        
        arena_table_ref.columns.array_committed [arena_index] = false;
        arena_table_ref.columns.array_pool_index[arena_index] = arena_pool_index;
        arena_table_ref.columns.array_size_used [arena_index] = 0;
    }

    //update the table
    arena_table_ref.arena_count_current = arena_count_new;

    //we're done
    return(starting_arena_index);
}