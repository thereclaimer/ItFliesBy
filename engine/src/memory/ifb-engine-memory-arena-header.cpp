#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* INLINE METHODS                                                                 */
/**********************************************************************************/

inline const ifb_b8 
ifb_engine::memory_arena_header_table_create(
    IFBEngineMemoryTableArenaHeader& arena_header_table_ref) {

    arena_header_table_ref = {0};
    arena_header_table_ref.header_count_max = IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX;

    return(true);
}

inline const IFBEngineMemoryTableIndexArenaHeader 
ifb_engine::memory_arena_header_create(
    const ifb_cstr                         arena_header_tag,
    const ifb_size                         arena_size,
    const ifb_size                         arena_count,
          IFBEngineMemoryReservation&      reservation_ref,
          IFBEngineMemoryTableArenaHeader& table_arena_header_ref) {

    //calculate sizes
    const ifb_size arena_page_count              = ifb_engine::memory_reservation_page_count_aligned(reservation_ref,arena_size);
    const ifb_size arena_header_page_count_total = arena_page_count * arena_count; 

    //add the pages
    ifb_size arena_header_page_start;
    ifb_b8 result = ifb_engine::memory_reservation_add_pages(
        reservation_ref,
        arena_header_page_count_total,
        arena_header_page_start);

    //sanity check
    if (!result) {
        return(IFB_ENGINE_MEMORY_ARENA_HEADER_INDEX_INVALID);
    }

    //get the new index and update the header count
    const IFBEngineMemoryTableIndexArenaHeader new_header_index = table_arena_header_ref.header_count_current;    
    ++table_arena_header_ref.header_count_current;

    //get the tag length
    const ifb_size tag_length = strnlen_s(arena_header_tag,IFB_ENGINE_MEMORY_ARENA_HEADER_TAG_LENGTH);

    //get the offset for the tag buffer
    const ifb_size tag_offset = 
        IFB_ENGINE_MEMORY_ARENA_HEADER_TAG_LENGTH * 
        new_header_index;

    //copy the tag
    const ifb_cstr tag = &table_arena_header_ref.tag_buffer[tag_offset]; 
    memmove(
        tag,
        arena_header_tag,
        tag_length);

    //update the table at the new index
    table_arena_header_ref.columns.page_start       [new_header_index] = arena_header_page_start;
    table_arena_header_ref.columns.arena_page_count [new_header_index] = arena_page_count;
    table_arena_header_ref.columns.arena_count      [new_header_index] = arena_count;

    //we're done
    return(new_header_index);
}

inline const ifb_u32 
ifb_engine::memory_arena_header_page_start(
          IFBEngineMemoryTableArenaHeader&     arena_table_header_ref,
    const IFBEngineMemoryTableIndexArenaHeader arena_header_index) {

    const ifb_u32 page_start = arena_table_header_ref.columns.page_start[arena_header_index];

    return(page_start);
}

inline const 
ifb_size ifb_engine::memory_arena_header_arena_page_count(
          IFBEngineMemoryTableArenaHeader&     arena_table_header_ref,
    const IFBEngineMemoryTableIndexArenaHeader arena_header_index) {

    const ifb_u32 arena_page_count = arena_table_header_ref.columns.arena_page_count[arena_header_index];

    return(arena_page_count);
}

inline const ifb_size 
ifb_engine::memory_arena_header_arena_count(
          IFBEngineMemoryTableArenaHeader&     arena_table_header_ref,
    const IFBEngineMemoryTableIndexArenaHeader arena_header_index) {

    const ifb_u32 arena_count = arena_table_header_ref.columns.arena_count[arena_header_index];

    return(arena_count);
}