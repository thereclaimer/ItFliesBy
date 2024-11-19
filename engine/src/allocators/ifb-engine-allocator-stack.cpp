#pragma once

#include "ifb-engine-internal-allocators.hpp"
#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_u32
ifb_engine::stack_allocator_create(
    const ifb_cstr stack_allocator_tag,
    const ifb_u32  stack_size_minimum) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //find the next available stack
    const ifb_u32 stack_index = ifb_engine::stack_allocator_table_next_available(stack_allocator_table);
    if (!ifb_engine::stack_allocator_valid(stack_index)) {
        return(IFB_ENGINE_STACK_ALLOCATOR_INVALID);
    }

    //get an arena
    const ifb_u32 arena_index = ifb_engine::memory_arena_commit(stack_allocator_tag,stack_size_minimum);
    if (!ifb_engine::memory_arena_valid(arena_index)) {
        return(IFB_ENGINE_STACK_ALLOCATOR_INVALID);
    }

    //update the table
    ifb_engine::stack_allocator_table_update_arena_index(stack_allocator_table, stack_index, arena_index);
    ifb_engine::stack_allocator_table_update_used       (stack_allocator_table, stack_index, 0);

    //we're done
    return(stack_index);
}

ifb_api const ifb_b8
ifb_engine::stack_allocator_valid(
    const ifb_u32 stack_allocator_index) {

    return(stack_allocator_index < IFB_ENGINE_STACK_ALLOCATOR_COUNT_MAX);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_size_total(
    const ifb_u32 stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena
    const ifb_u32 arena_index = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);

    //get the arena page count
    const ifb_u32 arena_page_count = ifb_engine::memory_arena_page_count(arena_index);

    //get the arena size
    const ifb_u32 arena_size = ifb_engine::memory_page_size(arena_page_count);

    //the arena size is also the stack size, we're done
    return(arena_size);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_size_used(
    const ifb_u32 stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the used size
    const ifb_u32 used_size = ifb_engine::stack_allocator_table_get_used(stack_allocator_table, stack_allocator_index);

    //we're done
    return(used_size);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_arena_index(
    const ifb_u32 stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena
    const ifb_u32 arena_index = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);

    //we're done
    return(arena_index);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_arena_page_start(
    const ifb_u32  stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena
    const ifb_u32 arena_index = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);

    //get the page start
    const ifb_u32 arena_page_start = ifb_engine::memory_arena_page_start(arena_index);

    //we're done
    return(arena_page_start);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_arena_page_count(
    const ifb_u32  stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena
    const ifb_u32 arena_index = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);

    //get the page count
    const ifb_u32 arena_page_count = ifb_engine::memory_arena_page_count(arena_index);

    //we're done
    return(arena_page_count);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_arena_tag_index(
    const ifb_u32  stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena
    const ifb_u32 arena_index = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);

    //get the tag index
    const ifb_u32 arena_tag_index = ifb_engine::memory_arena_tag_index(arena_index);

    //we're done
    return(arena_tag_index);
}

ifb_api const ifb_cstr
ifb_engine::stack_allocator_arena_tag_value(
    const ifb_u32  stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena
    const ifb_u32 arena_index = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);

    //get the tag value
    const ifb_cstr arena_tag_value = ifb_engine::memory_arena_tag_value(arena_index);

    //we're done
    return(arena_tag_value);
}

ifb_api const ifb_b8
ifb_engine::stack_allocator_reset(
    const ifb_u32  stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //set the used to 0
    ifb_engine::stack_allocator_table_update_used(stack_allocator_table,stack_allocator_index,0);

    //we're done
    return(true);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_pointer_handle(
    const ifb_u32 stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena index and used size
    const ifb_u32 arena_index = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);
    const ifb_u32 used_size   = ifb_engine::stack_allocator_table_get_used       (stack_allocator_table,stack_allocator_index);

    //get the memory handle
    const ifb_u32 arena_handle = ifb_engine::memory_arena_handle(arena_index,used_size);

    //we're done
    return(arena_handle);
}

ifb_api const ifb_memory
ifb_engine::stack_allocator_pointer_memory(
    const ifb_u32 stack_allocator_index) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena index and used size
    const ifb_u32 arena_index = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);
    const ifb_u32 used_size   = ifb_engine::stack_allocator_table_get_used       (stack_allocator_table,stack_allocator_index);

    //get the memory handle
    const ifb_u32 arena_handle = ifb_engine::memory_arena_handle(arena_index,used_size);

    //get the pointer
    const ifb_memory arena_pointer = ifb_engine::memory_pointer_from_handle(arena_handle);

    //we're done
    return(arena_pointer);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_push_handle(
    const ifb_u32 stack_allocator_index,
    const ifb_u32 size) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena index and current/new used sizes
    const ifb_u32 arena_index       = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);
    const ifb_u32 used_size_current = ifb_engine::stack_allocator_table_get_used       (stack_allocator_table,stack_allocator_index);
    const ifb_u32 used_size_new     = used_size_current + size; 

    //get the memory handle with the new used size
    const ifb_u32 arena_handle = ifb_engine::memory_arena_handle(arena_index,used_size_new);

    //if we can't fit the push, we're done
    if (arena_handle == IFB_ENGINE_MEMORY_HANDLE_INVALID) {
        return(IFB_ENGINE_MEMORY_HANDLE_INVALID);
    }

    //update the table
    ifb_engine::stack_allocator_table_update_used(stack_allocator_table,stack_allocator_index,used_size_new);

    //we're done
    return(arena_handle);
}

ifb_api const ifb_memory
ifb_engine::stack_allocator_push_memory(
    const ifb_u32 stack_allocator_index,
    const ifb_u32 size) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the arena index and current/new used sizes
    const ifb_u32 arena_index       = ifb_engine::stack_allocator_table_get_arena_index(stack_allocator_table,stack_allocator_index);
    const ifb_u32 used_size_current = ifb_engine::stack_allocator_table_get_used       (stack_allocator_table,stack_allocator_index);
    const ifb_u32 used_size_new     = used_size_current + size; 

    //get the memory handle with the new used size
    const ifb_u32 arena_handle = ifb_engine::memory_arena_handle(arena_index,used_size_new);

    //if we can't fit the push, we're done
    if (arena_handle == IFB_ENGINE_MEMORY_HANDLE_INVALID) {
        return(NULL);
    }

    //update the table
    ifb_engine::stack_allocator_table_update_used(stack_allocator_table,stack_allocator_index,used_size_new);

    //get the pointer
    const ifb_memory arena_memory = ifb_engine::memory_pointer_from_handle(arena_handle);

    //we're done
    return(arena_memory);
}

ifb_api const ifb_b8
ifb_engine::stack_allocator_pull(
    const ifb_u32 stack_allocator_index,
    const ifb_u32 size) {

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_context(stack_allocator_table);

    //get the current used size
    const ifb_u32 used_size_current = ifb_engine::stack_allocator_table_get_used(stack_allocator_table,stack_allocator_index);

    //make sure we can pull
    if (used_size_current < size) {
        
        //if not,we're done
        return(false);
    }

    //update the table with the new used size
    const ifb_b8 used_size_new = used_size_current - size;
    ifb_engine::stack_allocator_table_update_used(stack_allocator_table,stack_allocator_index,used_size_new);

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineStackAllocatorTableHeader* 
ifb_engine::stack_allocator_table_header_from_handle(
    const ifb_u32 stack_allocator_table_handle) {

    IFBEngineStackAllocatorTableHeader* table_header_ptr = (IFBEngineStackAllocatorTableHeader*)ifb_engine::memory_pointer_from_handle(stack_allocator_table_handle);

    return(table_header_ptr);
}

inline ifb_void 
ifb_engine::stack_allocator_table_from_handle(
    const ifb_u32                        in_stack_allocator_table_handle,
          IFBEngineStackAllocatorTable& out_stack_allocator_table_ref) {

    //get the table header
    IFBEngineStackAllocatorTableHeader* table_header_ptr = 
        (IFBEngineStackAllocatorTableHeader*)ifb_engine::memory_pointer_from_handle(in_stack_allocator_table_handle);

    //get the table columns
    ifb_u32* column_arena_index_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(table_header_ptr->column_handle_arena_index);
    ifb_u32* column_used_ptr        = (ifb_u32*)ifb_engine::memory_pointer_from_handle(table_header_ptr->column_handle_used);

    //initialize the struct
    out_stack_allocator_table_ref.handle                  = in_stack_allocator_table_handle;
    out_stack_allocator_table_ref.row_count               = table_header_ptr->row_count;
    out_stack_allocator_table_ref.column_ptrs.arena_index = column_arena_index_ptr;
    out_stack_allocator_table_ref.column_ptrs.used        = column_used_ptr;
}

inline ifb_void 
ifb_engine::stack_allocator_table_from_context(
    IFBEngineStackAllocatorTable& stack_allocator_table_ref) {

    //get the allocator manager
    IFBEngineAllocatorManager* allocator_manager_ptr = ifb_engine::allocator_manager_from_context();

    //get the table
    ifb_engine::stack_allocator_table_from_handle(
        allocator_manager_ptr->table_handle_stack_allocators,
        stack_allocator_table_ref);
}

inline const ifb_b8 
ifb_engine::stack_allocator_table_initialize(
    const ifb_u32 stack_allocator_table_handle) {

    //calculate sizes
    const ifb_u32 row_count         = IFB_ENGINE_STACK_ALLOCATOR_COUNT_MAX;
    const ifb_u32 column_size       = ifb_macro_size_array(ifb_u32,row_count);
    const ifb_u32 column_page_count = ifb_engine::memory_page_count(column_size);

    //commit pages
    const ifb_u32 page_number_arena_index = ifb_engine::memory_page_commit(column_page_count);
    const ifb_u32 page_number_used        = ifb_engine::memory_page_commit(column_page_count);
    const ifb_u32 page_offset             = 0;

    //get handles
    const ifb_u32 column_handle_arena_index = ifb_engine::memory_handle(page_number_arena_index, page_offset); 
    const ifb_u32 column_handle_used        = ifb_engine::memory_handle(page_number_used,        page_offset); 

    //initialize header
    IFBEngineStackAllocatorTableHeader* stack_allocator_table_header_ptr = ifb_engine::stack_allocator_table_header_from_handle(stack_allocator_table_handle);
    stack_allocator_table_header_ptr->row_count                 = row_count;
    stack_allocator_table_header_ptr->column_handle_arena_index = column_handle_arena_index;
    stack_allocator_table_header_ptr->column_handle_used        = column_handle_used;

    //get the table
    IFBEngineStackAllocatorTable stack_allocator_table;
    ifb_engine::stack_allocator_table_from_handle(
        stack_allocator_table_handle,
        stack_allocator_table);

    //initialize the columns
    for (
        ifb_u32 stack_index = 0;
        stack_index < row_count;
        ++stack_index) {

        stack_allocator_table.column_ptrs.arena_index [stack_index] = IFB_ENGINE_MEMORY_ARENA_INVALID; 
        stack_allocator_table.column_ptrs.used        [stack_index] = 0; 
    }

    //we're done
    return(true);
}

inline const ifb_u32 
ifb_engine::stack_allocator_table_next_available(
    IFBEngineStackAllocatorTable& stack_allocator_table_ref) {

    const ifb_u32* column_arena_ptr = stack_allocator_table_ref.column_ptrs.arena_index;

    for (
        ifb_u32 stack_allocator_index = 0;
                stack_allocator_index < stack_allocator_table_ref.row_count;
              ++stack_allocator_index) {

        //if the arena id is invalid, this stack is available
        const ifb_u32 arena_id = column_arena_ptr[stack_allocator_index];
        if (!ifb_engine::memory_arena_valid(arena_id)) {
            return(stack_allocator_index);
        } 
    }

    //we didn't find an available stack, return invalid
    return(IFB_ENGINE_STACK_ALLOCATOR_INVALID);
}

inline ifb_void 
ifb_engine::stack_allocator_table_update_arena_index(
          IFBEngineStackAllocatorTable& stack_allocator_table_ref,
    const ifb_u32                       stack_allocator_index,
    const ifb_u32                       stack_allocator_arena_index) {

    stack_allocator_table_ref.column_ptrs.arena_index[stack_allocator_index] = stack_allocator_arena_index; 
}

inline ifb_void 
ifb_engine::stack_allocator_table_update_used(
          IFBEngineStackAllocatorTable& stack_allocator_table_ref,
    const ifb_u32                       stack_allocator_index,
    const ifb_u32                       stack_allocator_used) {

    stack_allocator_table_ref.column_ptrs.used[stack_allocator_index] = stack_allocator_used; 
}


inline const ifb_u32 
ifb_engine::stack_allocator_table_get_arena_index(
          IFBEngineStackAllocatorTable& stack_allocator_table_ref,
    const ifb_u32                       stack_allocator_index) {

    const ifb_u32 arena_index = stack_allocator_table_ref.column_ptrs.arena_index[stack_allocator_index];
    
    return(arena_index);
}

inline const ifb_u32
ifb_engine::stack_allocator_table_get_used(
          IFBEngineStackAllocatorTable& stack_allocator_table_ref,
    const ifb_u32                       stack_allocator_index) {

    const ifb_u32 used = stack_allocator_table_ref.column_ptrs.used[stack_allocator_index];

    return(used);
}