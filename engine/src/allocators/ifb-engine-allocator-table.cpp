#pragma once

#include "ifb-engine-internal-allocators.hpp"
#include "ifb-engine-internal-controllers.hpp"

ifb_api const IFBEngineTableAllocatorHandle
ifb_engine::table_allocator_create(
    const ifb_cstr table_allocator_tag_cstr,
    const ifb_u32  table_allocator_size_minimum) {
    
    IFBEngineArenaId arena_id;
    ifb_b8 result = true;

    //commit memory for the allocator
    IFBEngineMemoryCommit memory = ifb_engine::memory_commit(sizeof(IFBEngineTableAllocator));

    //get the handle and pointer
    IFBEngineTableAllocatorHandle table_allocator_handle;
    table_allocator_handle.memory = memory.handle;

    IFBEngineTableAllocator* table_allocator_ptr = (IFBEngineTableAllocator*)memory.pointer;

    //create the arena
    const IFBEngineArenaId arena_id = ifb_engine::controller_arena_commit(
        table_allocator_tag_cstr,
        table_allocator_size_minimum);

    //initialize the allocator
    table_allocator_ptr->arena_id = arena_id;
    table_allocator_ptr->position = 0;

    //sanity check
    ifb_macro_assert(result);

    //we're done
    return(table_allocator_handle);
}

ifb_api const IFBEngineTableMemoryHandle*
ifb_engine::table_allocator_reserve(
    const IFBEngineTableAllocatorHandle table_allocator_handle,
    const ifb_u32                       table_count_rows,
    const ifb_u32                       table_count_columns,
    const ifb_u32                       table_size_header,
    const ifb_u32*                      table_size_columns_ptr) {

    //get the allocator
    IFBEngineTableAllocator* table_allocator_ptr = ifb_engine::table_allocator_from_handle(table_allocator_handle);
    if (!table_allocator_ptr) {
        return(false);
    }

    //get the arena
    IFBEngineArena arena;
    arena.arena_id = table_allocator_ptr->arena_id;
    ifb_engine::controller_arena(arena);

    //todo
    ifb_macro_panic();

    return(false);
}

ifb_api const ifb_b8
ifb_engine::table_allocator_reset(
    const IFBEngineTableAllocatorHandle table_allocator_handle) {
    ifb_macro_panic();

    return(false);
}

inline IFBEngineTableAllocator*
ifb_engine::table_allocator_from_handle(
    const IFBEngineTableAllocatorHandle table_allocator_handle) {

    IFBEngineTableAllocator* table_allocator_ptr = ifb_engine::memory_pointer_from_handle(table_allocator_handle);
    ifb_macro_panic();

    return(table_allocator_ptr);
}
