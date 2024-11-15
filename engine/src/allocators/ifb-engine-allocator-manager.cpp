#pragma once

#include "ifb-engine-internal-allocators.hpp"
#include "ifb-engine-internal.hpp"

#include "ifb-engine-allocator-stack.cpp"

inline const ifb_u32 
ifb_engine::allocator_manager_start_up(
    ifb_void) {

    //get the sizes
    const ifb_u32 size_allocator_manager     = ifb_engine_macro_align_size_struct(IFBEngineAllocatorManager);
    const ifb_u32 size_stack_allocator_table = ifb_engine_macro_align_size_struct(IFBEngineStackAllocatorTable);
    const ifb_u32 size_block_allocator_table = ifb_engine_macro_align_size_struct(IFBEngineBlockAllocatorTable);

    //get the total size
    const ifb_u32 total_size = 
        size_allocator_manager     +
        size_stack_allocator_table +
        size_block_allocator_table;

    //commit pages
    const ifb_u32 page_count = ifb_engine::memory_page_count(total_size);
    const ifb_u32 page_start = ifb_engine::memory_page_commit(page_count);

    //if that didn't work, return 0
    if (page_start == 0) {
        return(0);
    }

    //calculate offsets
    const ifb_u32 page_offset_allocator_manager     = 0; 
    const ifb_u32 page_offset_stack_allocator_table = size_allocator_manager;
    const ifb_u32 page_offset_block_allocator_table = page_offset_stack_allocator_table + size_stack_allocator_table;   

    //create handles
    const ifb_u32 handle_allocator_manager     = ifb_engine::memory_handle(page_start, page_offset_allocator_manager); 
    const ifb_u32 handle_stack_allocator_table = ifb_engine::memory_handle(page_start, page_offset_stack_allocator_table);
    const ifb_u32 handle_block_allocator_table = ifb_engine::memory_handle(page_start, page_offset_block_allocator_table);

    //initialize the struct
    IFBEngineAllocatorManager* allocator_manager_ptr = ifb_engine::allocator_manager_from_handle(handle_allocator_manager);
    allocator_manager_ptr->table_handle_stack_allocators = handle_stack_allocator_table; 
    allocator_manager_ptr->table_handle_block_allocators = handle_block_allocator_table; 
    
    //initialize allocator tables
    ifb_engine::stack_allocator_table_initialize(handle_stack_allocator_table);

    //we're done
    return(handle_allocator_manager);
}

inline IFBEngineAllocatorManager* 
ifb_engine::allocator_manager_from_handle(
    const ifb_u32 allocator_manager_handle) {

    //get the pointer
    IFBEngineAllocatorManager* allocator_manager_ptr = (IFBEngineAllocatorManager*)ifb_engine::memory_pointer_from_handle(allocator_manager_handle);

    //we're done
    return(allocator_manager_ptr);
}

inline IFBEngineAllocatorManager* 
ifb_engine::allocator_manager_from_context(
    ifb_void) {

    //get the handle
    const ifb_u32 allocator_manager_handle = ifb_engine::context_core_handle_allocator_manager();

    //get the pointer
    IFBEngineAllocatorManager* allocator_manager_ptr = (IFBEngineAllocatorManager*)ifb_engine::memory_pointer_from_handle(allocator_manager_handle);

    //we're done
    return(allocator_manager_ptr);
}
