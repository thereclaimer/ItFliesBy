#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

namespace ifb_engine {

    inline const IFBEngineMemoryArenaDetailIndex 
    memory_arena_detail_table_insert(
    const IFBEngineMemoryArenaHeaderIndex  arena_header_index,
    const ifb_u32                          arena_count,
          IFBEngineMemoryArenaDetailTable& arena_detail_table_ref);
};


ifb_internal const ifb_b8 
ifb_engine::memory_arena_header_table_create(
    IFBEngineMemoryArenaHeaderTable& arena_header_table_ref) {

    arena_header_table_ref = {0};
    arena_header_table_ref.header_count_max = IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX;

    return(true);
}

ifb_internal const IFBEngineMemoryArenaHeaderIndex 
ifb_engine::memory_arena_header_create(
    const ifb_cstr                   in_arena_header_tag,
    const ifb_size                   in_arena_size,
    const ifb_size                   in_arena_count,
    IFBEngineMemoryReservation&      in_memory_reservation_ref,
    IFBEngineMemoryArenaHeaderTable& in_arena_table_header_ref) {

    //calculate sizes
    const ifb_size arena_size_aligned  = ifb_engine::memory_arena_align(in_arena_size); 
    const ifb_size arena_header_size   = arena_size_aligned * in_arena_count; 
    const ifb_size arena_header_offset = ifb_engine::memory_reservation_offset(in_memory_reservation_ref); 
    const ifb_size new_size_used       = in_memory_reservation_ref.size_used + arena_header_size; 

    //sanity check
    if (
        in_arena_header_tag == NULL                ||                                     // tag is not null
        in_arena_count == 0                        ||                                     // at least one arena
        new_size_used > in_memory_reservation_ref.size_total ||                                     // the pool isn't too big
        in_arena_table_header_ref.header_count_current == in_arena_table_header_ref.header_count_max) { // we have a slot in the table

        return(IFB_ENGINE_MEMORY_ARENA_HEADER_INDEX_INVALID);
    }

    //get the new index and update the header count
    const IFBEngineMemoryArenaHeaderIndex new_header_index = in_arena_table_header_ref.header_count_current;    
    ++in_arena_table_header_ref.header_count_current;



    //get the tag length
    const ifb_size tag_length = strnlen_s(in_arena_header_tag,IFB_ENGINE_MEMORY_ARENA_HEADER_TAG_LENGTH);

    //get the offset for the tag buffer
    const ifb_size tag_offset = 
        IFB_ENGINE_MEMORY_ARENA_HEADER_TAG_LENGTH * 
        new_header_index;

    //copy the tag
    const ifb_cstr tag = &in_arena_table_header_ref.tag_buffer[tag_offset]; 
    memmove(
        tag,
        in_arena_header_tag,
        tag_length);

    //update the table at the new index
    in_arena_table_header_ref.columns.array_arena_size [new_header_index] = arena_size_aligned;
    in_arena_table_header_ref.columns.array_arena_count[new_header_index] = in_arena_count;
    in_arena_table_header_ref.columns.array_offset     [new_header_index] = arena_header_offset;

    //we're done
    return(new_header_index);
}

inline const IFBEngineMemoryArenaDetailIndex
ifb_engine::memory_arena_detail_table_insert(
    const IFBEngineMemoryArenaHeaderIndex  arena_header_index,
    const ifb_u32                          arena_count,
          IFBEngineMemoryArenaDetailTable& arena_detail_table_ref) {

    //get the starting arena index
    const IFBEngineMemoryArenaDetailIndex starting_arena_index = arena_detail_table_ref.arena_count_current;

    //if we can't fit this number of arenas, we're done
    const ifb_size arena_count_new = starting_arena_index + arena_count;
    if (arena_count_new > arena_detail_table_ref.arena_count_max) {
        return(IFB_ENGINE_MEMORY_ARENA_DETAIL_INDEX_INVALID);
    }

    //initialize these arenas
    for (
        IFBEngineMemoryArenaDetailIndex arena_index = starting_arena_index;
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


/**********************************************************************************/
/* INLINE METHODS                                                                 */
/**********************************************************************************/

inline const ifb_size 
ifb_engine::memory_arena_header_arena_size(
          IFBEngineMemoryArenaHeaderTable& arena_table_header_ref,
    const IFBEngineMemoryArenaHeaderIndex  arena_header_index) {

    const ifb_size arena_size = arena_table_header_ref.columns.array_arena_size[arena_header_index];

    return(arena_size);
}

inline const 
ifb_size ifb_engine::memory_arena_header_arena_count(
          IFBEngineMemoryArenaHeaderTable& arena_table_header_ref,
    const IFBEngineMemoryArenaHeaderIndex  arena_header_index) {

    const ifb_size arena_count = arena_table_header_ref.columns.array_arena_count[arena_header_index];

    return(arena_count);
}

inline const ifb_size 
ifb_engine::memory_arena_header_offset(
          IFBEngineMemoryArenaHeaderTable& arena_table_header_ref,
    const IFBEngineMemoryArenaHeaderIndex  arena_header_index) {

    const ifb_size offset = arena_table_header_ref.columns.array_offset[arena_header_index];

    return(offset);
}