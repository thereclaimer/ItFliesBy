#pragma once

#include "ifb-engine-internal-tables.hpp"

inline ifb_void               
ifb_engine::table_stack_allocator(
    IFBEngineTableStackAllocator& stack_allocator_table) {

    IFBEngineTableManager* table_manager_ptr = ifb_engine::table_manager_from_context();

    IFBEngineTable& table_ref = table_manager_ptr->tables.stack_allocator;

    const ifb_u32 column_handle_start = table_ref.column_handle_start;

    stack_allocator_table.row_count                 = table_ref.row_count;
    stack_allocator_table.column_handle_arena_index = table_manager_ptr->columns.column_handles[column_handle_start];
    stack_allocator_table.column_handle_used        = table_manager_ptr->columns.column_handles[column_handle_start + 1];
}

inline ifb_table_index_arena* 
ifb_engine::table_stack_allocator_column_memory_table_index_arena(
    IFBEngineTableStackAllocator& stack_allocator_table) {

    ifb_table_index_arena* arena_index_ptr = (ifb_table_index_arena*)ifb_engine::memory_pointer_from_handle(stack_allocator_table.column_handle_arena_index);

    return(arena_index_ptr);
}

inline ifb_u32* 
ifb_engine::table_stack_allocator_column_memory_used(
    IFBEngineTableStackAllocator& stack_allocator_table) {

    ifb_u32* used_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(stack_allocator_table.column_handle_used);

    return(used_ptr);
}