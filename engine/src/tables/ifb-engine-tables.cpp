#pragma once

#include "ifb-engine-table-manager.cpp"

inline ifb_void
ifb_engine::table_arena(
    IFBEngineTableArena& arena_table) {

    IFBEngineTableManager* table_manager_ptr = ifb_engine::table_manager_from_context();

    IFBEngineTable& table_ref = table_manager_ptr->tables.arena;

    const ifb_u32 column_handle_start         = table_ref.column_handle_start;
    const ifb_handle_memory handle_page_start = table_manager_ptr->columns.column_handles[column_handle_start]; 
    const ifb_handle_memory handle_page_count = table_manager_ptr->columns.column_handles[column_handle_start + 1]; 
    const ifb_handle_memory handle_tag_id     = table_manager_ptr->columns.column_handles[column_handle_start + 2];     

    arena_table.row_count              = table_ref.row_count;
    arena_table.column_ptrs.page_start =         (ifb_u32*)ifb_engine::memory_pointer_from_handle(handle_page_start);
    arena_table.column_ptrs.page_count =         (ifb_u32*)ifb_engine::memory_pointer_from_handle(handle_page_count);
    arena_table.column_ptrs.tag_id     =  (IFBEngineTagId*)ifb_engine::memory_pointer_from_handle(handle_tag_id);
}

inline ifb_void               
ifb_engine::table_stack_allocator(
    IFBEngineTableStackAllocator& stack_allocator_table) {

    IFBEngineTableManager* table_manager_ptr = ifb_engine::table_manager_from_context();

    IFBEngineTable& table_ref = table_manager_ptr->tables.stack_allocator;

    const ifb_u32           column_handle_start = table_ref.column_handle_start;
    const ifb_handle_memory handle_arena_id     = table_manager_ptr->columns.column_handles[column_handle_start];
    const ifb_handle_memory handle_used         = table_manager_ptr->columns.column_handles[column_handle_start + 1];

    stack_allocator_table.row_count            = table_ref.row_count;
    stack_allocator_table.column_ptrs.arena_id = (IFBEngineArenaId*)ifb_engine::memory_pointer_from_handle(handle_arena_id);
    stack_allocator_table.column_ptrs.used     =          (ifb_u32*)ifb_engine::memory_pointer_from_handle(handle_used);
}

inline ifb_void
ifb_engine::table_tag(
    IFBEngineTableTag& tag_table) {

    IFBEngineTableManager* table_manager_ptr = ifb_engine::table_manager_from_context();

    IFBEngineTable& table_ref = table_manager_ptr->tables.tag;

    const ifb_u32           column_handle_start = table_ref.column_handle_start;
    const ifb_handle_memory handle_tag_buffer   = table_manager_ptr->columns.column_handles[column_handle_start];
    const ifb_handle_memory handle_hash_value   = table_manager_ptr->columns.column_handles[column_handle_start + 1];

    tag_table.row_count              = table_ref.row_count;
    tag_table.column_ptrs.tag_buffer =     (ifb_char*)ifb_engine::memory_pointer_from_handle(handle_tag_buffer);
    tag_table.column_ptrs.hash_value = (IFBHashValue*)ifb_engine::memory_pointer_from_handle(handle_hash_value);
}
