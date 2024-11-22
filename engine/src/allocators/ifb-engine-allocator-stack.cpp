#pragma once

#include "ifb-engine-internal-allocators.hpp"
#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::stack_allocator_create(
    const ifb_cstr                    in_stack_allocator_tag,
    const ifb_u32                    in_stack_size_minimum,
          IFBEngineStackAllocatorId& out_stack_allocator_id_ref) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //find the next available stack
    if (!ifb_engine::stack_allocator_next_available(stack_allocator_table,out_stack_allocator_id_ref)) {
        out_stack_allocator_id_ref = {IFB_ENGINE_STACK_ALLOCATOR_INVALID};
        return(false);
    }

    //get an arena
    IFBEngineArenaId stack_arena_id;
    if (!ifb_engine::memory_arena_commit(in_stack_allocator_tag,in_stack_size_minimum,stack_arena_id)) {
        out_stack_allocator_id_ref = {IFB_ENGINE_STACK_ALLOCATOR_INVALID};
        return(false);
    }

    //update the table
    ifb_engine::stack_allocator_update_arena_id(stack_allocator_table, out_stack_allocator_id_ref, stack_arena_id);
    ifb_engine::stack_allocator_update_used    (stack_allocator_table, out_stack_allocator_id_ref, 0);

    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::stack_allocator_valid(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    return(stack_allocator_id.stack_allocator_table_index < IFB_ENGINE_STACK_ALLOCATOR_COUNT_MAX);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_size_total(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena
    const IFBEngineArenaId arena_id = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);

    //get the arena page count
    const ifb_u32 arena_page_count = ifb_engine::memory_arena_page_count(arena_id);

    //get the arena size
    const ifb_u32 arena_size = ifb_engine::memory_page_size(arena_page_count);

    //the arena size is also the stack size, we're done
    return(arena_size);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_size_used(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the used size
    const ifb_u32 used_size = ifb_engine::stack_allocator_get_used(stack_allocator_table,stack_allocator_id);
    
    //we're done
    return(used_size);
}

ifb_api const IFBEngineArenaId
ifb_engine::stack_allocator_arena_id(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena
    const IFBEngineArenaId arena_id = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);

    //we're done
    return(arena_id);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_arena_page_start(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena
    const IFBEngineArenaId arena_id = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);

    //get the page start
    const ifb_u32 arena_page_start = ifb_engine::memory_arena_page_start(arena_id);

    //we're done
    return(arena_page_start);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_arena_page_count(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena
    const IFBEngineArenaId arena_id = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);

    //get the page count
    const ifb_u32 arena_page_count = ifb_engine::memory_arena_page_count(arena_id);

    //we're done
    return(arena_page_count);
}

ifb_api const IFBEngineTagId
ifb_engine::stack_allocator_arena_tag_id(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena
    const IFBEngineArenaId arena_id = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);

    //get the tag id
    const IFBEngineTagId arena_tag_id = ifb_engine::memory_arena_tag_id(arena_id);

    //we're done
    return(arena_tag_id);
}

ifb_api const ifb_cstr
ifb_engine::stack_allocator_arena_tag_value(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena
    const IFBEngineArenaId arena_id = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);

    //get the tag value
    const ifb_cstr arena_tag_value = ifb_engine::memory_arena_tag_value(arena_id);

    //we're done
    return(arena_tag_value);
}

ifb_api const ifb_b8
ifb_engine::stack_allocator_reset(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //set the used to 0
    ifb_engine::stack_allocator_update_used(
        stack_allocator_table,
        stack_allocator_id,
        0);

    //we're done
    return(true);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_pointer_handle(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena index and used size
    const IFBEngineArenaId arena_id  = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);
    const ifb_u32          used_size = ifb_engine::stack_allocator_get_used    (stack_allocator_table,stack_allocator_id);

    //get the memory handle
    const ifb_u32 arena_handle = ifb_engine::memory_arena_handle(arena_id,used_size);

    //we're done
    return(arena_handle);
}

ifb_api const ifb_memory
ifb_engine::stack_allocator_pointer_memory(
    const IFBEngineStackAllocatorId stack_allocator_id) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena index and used size
    const IFBEngineArenaId arena_id  = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);
    const ifb_u32          used_size = ifb_engine::stack_allocator_get_used    (stack_allocator_table,stack_allocator_id);

    //get the memory handle
    const ifb_u32 arena_handle = ifb_engine::memory_arena_handle(arena_id,used_size);

    //get the pointer
    const ifb_memory arena_pointer = ifb_engine::memory_pointer_from_handle(arena_handle);

    //we're done
    return(arena_pointer);
}

ifb_api const ifb_u32
ifb_engine::stack_allocator_push_handle(
    const IFBEngineStackAllocatorId stack_allocator_id,
    const ifb_u32                   size) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena index and current/new used sizes
    const IFBEngineArenaId arena_id          = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);
    const ifb_u32          used_size_current = ifb_engine::stack_allocator_get_used    (stack_allocator_table,stack_allocator_id);
    const ifb_u32          used_size_new     = used_size_current + size; 

    //get the memory handle with the new used size
    const ifb_u32 arena_handle = ifb_engine::memory_arena_handle(arena_id,used_size_new);

    //if we can't fit the push, we're done
    if (arena_handle == IFB_ENGINE_MEMORY_HANDLE_INVALID) {
        return(IFB_ENGINE_MEMORY_HANDLE_INVALID);
    }

    //update the table
    ifb_engine::stack_allocator_update_used(
        stack_allocator_table,
        stack_allocator_id,
        used_size_new);

    //we're done
    return(arena_handle);
}

ifb_api const ifb_memory
ifb_engine::stack_allocator_push_memory(
    const IFBEngineStackAllocatorId stack_allocator_id,
    const ifb_u32                   size) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the arena index and current/new used sizes
    const IFBEngineArenaId arena_id          = ifb_engine::stack_allocator_get_arena_id(stack_allocator_table,stack_allocator_id);
    const ifb_u32          used_size_current = ifb_engine::stack_allocator_get_used    (stack_allocator_table,stack_allocator_id);
    const ifb_u32          used_size_new     = used_size_current + size; 

    //get the memory handle with the new used size
    const ifb_u32 arena_handle = ifb_engine::memory_arena_handle(arena_id,used_size_new);

    //if we can't fit the push, we're done
    if (arena_handle == IFB_ENGINE_MEMORY_HANDLE_INVALID) {
        return(IFB_ENGINE_MEMORY_HANDLE_INVALID);
    }

    //update the table
    ifb_engine::stack_allocator_update_used(
        stack_allocator_table,
        stack_allocator_id,
        used_size_new);

    //get the pointer
    const ifb_memory arena_memory = ifb_engine::memory_pointer_from_handle(arena_handle);

    //we're done
    return(arena_memory);
}

ifb_api const ifb_b8
ifb_engine::stack_allocator_pull(
    const IFBEngineStackAllocatorId stack_allocator_id,
    const ifb_u32                   size) {

    //get the table
    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    //get the current used size
    const ifb_u32 used_size_current = ifb_engine::stack_allocator_get_used(
        stack_allocator_table,
        stack_allocator_id);

    //make sure we can pull
    if (used_size_current < size) {
        
        //if not,we're done
        return(false);
    }

    //update the table with the new used size
    const ifb_b8 used_size_new = used_size_current - size;
    ifb_engine::stack_allocator_update_used(
        stack_allocator_table,
        stack_allocator_id,
        used_size_new);

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const ifb_b8 
ifb_engine::stack_allocator_table_initialize(
    IFBEngineTableStackAllocator& stack_allocator_table_ref) {

    //initialize the columns
    for (
        ifb_u32 stack_index = 0;
        stack_index < stack_allocator_table_ref.row_count;
        ++stack_index) {

        stack_allocator_table_ref.column_ptrs.arena_id[stack_index] = {IFB_ENGINE_MEMORY_ARENA_INVALID}; 
        stack_allocator_table_ref.column_ptrs.used    [stack_index] = 0; 
    }

    //we're done
    return(true);
}

inline const ifb_b8
ifb_engine::stack_allocator_next_available(
    IFBEngineTableStackAllocator& in_stack_allocator_table_ref,
    IFBEngineStackAllocatorId&   out_stack_allocator_id_ref) {

    for (
        ifb_u32 stack_allocator_index = 0;
                stack_allocator_index < in_stack_allocator_table_ref.row_count;
              ++stack_allocator_index) {

        //if the arena id is invalid, this stack is available
        const IFBEngineArenaId arena_id = in_stack_allocator_table_ref.column_ptrs.arena_id[stack_allocator_index];
        if (!ifb_engine::memory_arena_valid(arena_id)) {
            out_stack_allocator_id_ref.stack_allocator_table_index = stack_allocator_index; 
            return(true);
        } 
    }

    //we didn't find an available stack, return invalid
    return(false);
}

inline ifb_void 
ifb_engine::stack_allocator_update_arena_id(
          IFBEngineTableStackAllocator& stack_allocator_table_ref,
    const IFBEngineStackAllocatorId     stack_allocator_id,
    const IFBEngineArenaId              stack_allocator_arena_id) {

    stack_allocator_table_ref.column_ptrs.arena_id[stack_allocator_id.stack_allocator_table_index] = stack_allocator_arena_id; 
}

inline ifb_void 
ifb_engine::stack_allocator_update_used(
          IFBEngineTableStackAllocator& stack_allocator_table_ref,
    const IFBEngineStackAllocatorId     stack_allocator_id,
    const ifb_u32                      stack_allocator_used) {

    stack_allocator_table_ref.column_ptrs.used[stack_allocator_id.stack_allocator_table_index] = stack_allocator_used;
}

inline const IFBEngineArenaId 
ifb_engine::stack_allocator_get_arena_id(
          IFBEngineTableStackAllocator& stack_allocator_table_ref,
    const IFBEngineStackAllocatorId     stack_allocator_id) {

    const IFBEngineArenaId arena_id = stack_allocator_table_ref.column_ptrs.arena_id[stack_allocator_id.stack_allocator_table_index];
    
    return(arena_id);
}

inline const ifb_u32
ifb_engine::stack_allocator_get_used(
          IFBEngineTableStackAllocator& stack_allocator_table_ref,
    const IFBEngineStackAllocatorId     stack_allocator_id) {

    const ifb_u32 used = stack_allocator_table_ref.column_ptrs.used[stack_allocator_id.stack_allocator_table_index];

    return(used);
}