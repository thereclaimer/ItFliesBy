#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* INLINE METHODS                                                                 */
/**********************************************************************************/

inline const IFBEngineMemoryTableIndexArenaDetail
ifb_engine::memory_arena_detail_table_insert(
    const IFBEngineMemoryTableIndexArenaHeader arena_header_index,
    const ifb_u32                              arena_count,
          IFBEngineMemoryArenaDetailTable&     arena_detail_table_ref) {

    //get the starting arena index
    const IFBEngineMemoryTableIndexArenaDetail starting_arena_index = arena_detail_table_ref.arena_count_current;

    //if we can't fit this number of arenas, we're done
    const ifb_size arena_count_new = starting_arena_index + arena_count;
    if (arena_count_new > arena_detail_table_ref.arena_count_max) {
        return(IFB_ENGINE_MEMORY_ARENA_DETAIL_INDEX_INVALID);
    }

    //initialize these arenas
    for (
        IFBEngineMemoryTableIndexArenaDetail arena_index = starting_arena_index;
        arena_index < arena_count_new;
        ++arena_index) {
        
        arena_detail_table_ref.columns.array_committed   [arena_index] = false;
        arena_detail_table_ref.columns.array_header_index[arena_index] = arena_header_index;
        arena_detail_table_ref.columns.array_size_used   [arena_index] = 0;
        arena_detail_table_ref.columns.array_pool_index  [arena_index] = arena_index - starting_arena_index;
    }

    //update the table
    arena_detail_table_ref.arena_count_current = arena_count_new;

    //we're done
    return(starting_arena_index);
}

inline const IFBEngineMemoryTableIndexArenaDetail 
ifb_engine::memory_arena_detail_next_available_index(
          IFBEngineMemoryArenaDetailTable& arena_detail_table_ref,
    const IFBEngineMemoryTableIndexArenaDetail  arena_detail_index_start,
    const IFBEngineMemoryTableIndexArenaHeader  arena_header_index) {

    if (arena_detail_index_start >= arena_detail_table_ref.arena_count_current) {
        return(IFB_ENGINE_MEMORY_ARENA_DETAIL_INDEX_INVALID);
    }

    //set the out index
    IFBEngineMemoryTableIndexArenaDetail arena_detail_index_available = IFB_ENGINE_MEMORY_ARENA_DETAIL_INDEX_INVALID;

    for (
        IFBEngineMemoryTableIndexArenaDetail arena_detail_index = arena_detail_index_start;
        arena_detail_index < arena_detail_table_ref.arena_count_current;
        ++arena_detail_index) {

        const ifb_b8                          detail_committed    = ifb_engine::memory_arena_detail_committed(arena_detail_table_ref, arena_detail_index);
        const IFBEngineMemoryTableIndexArenaHeader detail_header_index = ifb_engine::memory_arena_detail_header_index(arena_detail_table_ref, arena_detail_index);

        //if the header indexes don't match, we're in a different arena group
        if (detail_header_index != arena_header_index) {
            break;
        }

        //if this arena isn't committed and has a matching header, its available
        if (!detail_committed) {
            arena_detail_index_available = arena_detail_index;            
        }
    }

    //we're done
    return(arena_detail_index_available != IFB_ENGINE_MEMORY_ARENA_DETAIL_INDEX_INVALID);
}

inline const ifb_b8
ifb_engine::memory_arena_detail_committed(
          IFBEngineMemoryArenaDetailTable& arena_table_detail_ref,
    const IFBEngineMemoryTableIndexArenaDetail  arena_detail_index) {

    const ifb_b8 committed = arena_table_detail_ref.columns.array_committed[arena_detail_index];

    return(committed);
}

inline const IFBEngineMemoryTableIndexArenaHeader
ifb_engine::memory_arena_detail_header_index(
          IFBEngineMemoryArenaDetailTable& arena_table_detail_ref,
    const IFBEngineMemoryTableIndexArenaDetail  arena_detail_index) {

    const IFBEngineMemoryTableIndexArenaHeader header_index = arena_table_detail_ref.columns.array_header_index[arena_detail_index];

    return(header_index);
}

inline const ifb_u32
ifb_engine::memory_arena_detail_size_used(
          IFBEngineMemoryArenaDetailTable& arena_table_detail_ref,
    const IFBEngineMemoryTableIndexArenaDetail  arena_detail_index) {

    const ifb_b8 size_used = arena_table_detail_ref.columns.array_size_used[arena_detail_index];

    return(size_used);
}

inline const ifb_index
ifb_engine::memory_arena_detail_pool_index(
          IFBEngineMemoryArenaDetailTable& arena_table_detail_ref,
    const IFBEngineMemoryTableIndexArenaDetail  arena_detail_index) {

    const ifb_index pool_index = arena_table_detail_ref.columns.array_pool_index[arena_detail_index];

    return(pool_index);
}

inline const ifb_void 
ifb_engine::memory_arena_detail_committed_set_true(
          IFBEngineMemoryArenaDetailTable& arena_table_detail_ref,
    const IFBEngineMemoryTableIndexArenaDetail  arena_detail_index) {

    arena_table_detail_ref.columns.array_committed[arena_detail_index] = true;
}

inline const ifb_void 
ifb_engine::memory_arena_detail_committed_set_false(
          IFBEngineMemoryArenaDetailTable& arena_table_detail_ref,
    const IFBEngineMemoryTableIndexArenaDetail  arena_detail_index) {

    arena_table_detail_ref.columns.array_committed[arena_detail_index] = false;
}


inline const ifb_void 
ifb_engine::memory_arena_detail_used_size_update(
          IFBEngineMemoryArenaDetailTable& arena_table_detail_ref, 
    const IFBEngineMemoryTableIndexArenaDetail  arena_detail_index,
    const ifb_size                         arena_used_size) {

    arena_table_detail_ref.columns.array_size_used[arena_detail_index] = arena_used_size;
}