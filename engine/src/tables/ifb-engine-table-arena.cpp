#pragma once

#include "ifb-engine-internal-tables.hpp"

inline ifb_void
ifb_engine::table_arena(
    IFBEngineTableArena& arena_table) {

    IFBEngineTableManager* table_manager_ptr = ifb_engine::table_manager_from_context();

    IFBEngineTable& table_ref = table_manager_ptr->tables.arena;

    const ifb_u32 column_handle_start = table_ref.column_handle_start;
    arena_table.column_handle_page_start = table_manager_ptr->columns.column_handles[column_handle_start]; 
    arena_table.column_handle_page_count = table_manager_ptr->columns.column_handles[column_handle_start + 1]; 
    arena_table.column_handle_tag_id     = table_manager_ptr->columns.column_handles[column_handle_start + 2];     
}

inline ifb_u32*
ifb_engine::table_arena_column_page_start(
    IFBEngineTableArena& arena_table) {

    ifb_u32* column_page_start_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(arena_table.column_handle_page_start); 

    return(column_page_start_ptr);
}

inline ifb_u32*
ifb_engine::table_arena_column_page_count(
    IFBEngineTableArena& arena_table) {

    ifb_u32* column_page_count_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(arena_table.column_handle_page_count); 

    return(column_page_count_ptr);
}

inline IFBEngineTagId*
ifb_engine::table_arena_column_tag_id(
    IFBEngineTableArena& arena_table) {

    IFBEngineTagId* column_tag_id_ptr = (IFBEngineTagId*)ifb_engine::memory_pointer_from_handle(arena_table.column_handle_tag_id); 

    return(column_tag_id_ptr);
}