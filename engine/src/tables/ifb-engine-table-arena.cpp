#pragma once

#include "ifb-engine-internal-tables.hpp"

inline const IFBEngineTableHandleArena
ifb_engine::table_arena_create(
    const IFBEngineTableAllocatorHandle table_allocator_handle) {

    IFBEngineTableHandleArena arena_table_handle = {0};

    return(arena_table_handle);
}

inline const ifb_u32
ifb_engine::table_arena_read_page_start(
          IFBEngineTableArena*      arena_table_ptr,
    const IFBEngineTableIndexArena  arena_index) {

    const ifb_u32 arena_page_start = arena_table_ptr->column_ptrs.page_start[arena_index.index.value];

    return(arena_page_start);
}

inline const ifb_u32
ifb_engine::table_arena_read_page_count(
          IFBEngineTableArena*      arena_table_ptr,
    const IFBEngineTableIndexArena  arena_index) {

    const ifb_u32 arena_page_count = arena_table_ptr->column_ptrs.page_count[arena_index.index.value];

    return(arena_page_count);
}

inline const IFBEngineTableIndexTag
ifb_engine::table_arena_read_tag_index(
          IFBEngineTableArena*      arena_table_ptr,
    const IFBEngineTableIndexArena  arena_index) {

    const IFBEngineTableIndexTag arena_tag_index = arena_table_ptr->column_ptrs.tag_index[arena_index.index.value];

    return(arena_tag_index);
}

inline const IFBEngineTableIndexArena
ifb_engine::table_arena_insert(
          IFBEngineTableArena*   arena_table_ptr,
    const ifb_u32                arena_page_start,
    const ifb_u32                arena_page_count,
    const IFBEngineTableIndexTag arena_tag_index) {

    //get the next index
    const ifb_index arena_index_value = arena_table_ptr->next_index;
    ++arena_table_ptr->next_index;    

    //sanity check
    ifb_macro_assert(arena_table_ptr->next_index < arena_table_ptr->row_count);

    //update the table
    arena_table_ptr->column_ptrs.page_start[arena_index_value] = arena_page_start; 
    arena_table_ptr->column_ptrs.page_count[arena_index_value] = arena_page_count; 
    arena_table_ptr->column_ptrs.tag_index [arena_index_value] = arena_tag_index; 

    IFBEngineTableIndexArena result_arena_index;
    result_arena_index.index.value = arena_index_value;

    return(result_arena_index);
}

inline IFBEngineTableArena* 
ifb_engine::table_arena(
    const IFBEngineTableHandleArena table_handle_arena) {

    IFBEngineTableArena* arena_table_ptr = (IFBEngineTableArena*)ifb_engine::memory_pointer_from_handle(table_handle_arena.memory_handle);

    return(arena_table_ptr);
}