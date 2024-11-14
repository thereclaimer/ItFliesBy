#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineArenaTable* 
ifb_engine::arena_table_pointer_from_handle(
    const ifb_u32 arena_table_handle) {

    IFBEngineArenaTable* arena_table_ptr = (IFBEngineArenaTable*)ifb_engine::memory_pointer_from_handle(arena_table_handle);

    return(arena_table_ptr);
}


inline const ifb_b8 
ifb_engine::arena_table_initialize(
    const ifb_u32 arena_table_handle) {

    IFBEngineArenaTable* arena_table_ptr = ifb_engine::arena_table_pointer_from_handle(arena_table_handle);

    const ifb_u32 arena_count = IFB_ENGINE_MEMORY_ARENA_COUNT_MAX;

    arena_table_ptr->arena_count_total  = arena_count;
    arena_table_ptr->arena_count_used   = 0;
    arena_table_ptr->arena_size_minimum = IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM;

    const ifb_u32 column_size = ifb_engine_macro_size_array(ifb_u32,arena_count);
    const ifb_u32 column_page_count = ifb_engine::memory_page_count(column_size);

    arena_table_ptr->page_id_column_page_start = ifb_engine::memory_page_commit(column_page_count);
    arena_table_ptr->page_id_column_page_count = ifb_engine::memory_page_commit(column_page_count);

    const ifb_b8 result = (
        arena_table_ptr->page_id_column_page_start != 0 &&
        arena_table_ptr->page_id_column_page_count != 0);

    return(result);
}
