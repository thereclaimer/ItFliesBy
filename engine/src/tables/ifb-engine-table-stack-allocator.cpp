#pragma once

#include "ifb-engine-internal-tables.hpp"

inline ifb_void               
ifb_engine::table_stack_allocator(
    IFBEngineTableStackAllocator& stack_allocator_table) {

    IFBEngineTableManager* table_manager_ptr = ifb_engine::table_manager_from_context();

    IFBEngineTable& table_ref = table_manager_ptr->tables.stack_allocator;

    const ifb_u32 column_handle_start = table_ref.column_handle_start;

    stack_allocator_table.row_count              = table_ref.row_count;
    stack_allocator_table.column_handle_arena_id = table_manager_ptr->columns.column_handles[column_handle_start];
    stack_allocator_table.column_handle_used     = table_manager_ptr->columns.column_handles[column_handle_start + 1];
}

inline IFBEngineArenaId*
ifb_engine::table_stack_allocator_column_arena_id(
    IFBEngineTableStackAllocator& stack_allocator_table) {

    IFBEngineArenaId* arena_index_ptr = (IFBEngineArenaId*)ifb_engine::memory_pointer_from_handle(stack_allocator_table.column_handle_arena_id);

    return(arena_index_ptr);
}

inline ifb_u32* 
ifb_engine::table_stack_allocator_column_used(
    IFBEngineTableStackAllocator& stack_allocator_table) {

    ifb_u32* used_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(stack_allocator_table.column_handle_used);

    return(used_ptr);
}