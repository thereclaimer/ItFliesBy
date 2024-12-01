#pragma once

#include "ifb-engine-allocators.hpp"
#include "ifb-engine-internal-controllers.hpp"

ifb_api const IFBEngineLinearAllocatorHandle 
ifb_engine::linear_allocator_create(
    const ifb_cstr linear_allocator_tag_cstr,
    const ifb_u32  linear_allocator_size_minimum) {

    //get the core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //commit memory for the allocator
    IFBEngineMemoryCommit memory = ifb_engine::memory_commit(sizeof(IFBEngineLinearAllocator));

    //create the arena
    IFBEngineArenaId arena_id = ifb_engine::controller_arena_commit(
        engine_core,
        linear_allocator_tag_cstr,
        linear_allocator_size_minimum);

    //initialize the allocator
    IFBEngineLinearAllocator* linear_allocator_ptr = (IFBEngineLinearAllocator*)memory.pointer;
    linear_allocator_ptr->arena_id   = arena_id;
    linear_allocator_ptr->position   = 0;
    linear_allocator_ptr->save_point = 0;

    //get the handle
    IFBEngineLinearAllocatorHandle linear_allocator_handle;
    linear_allocator_handle.memory = memory.handle; 

    //we're done
    return(linear_allocator_handle);
}

ifb_api const IFBEngineMemoryHandle
ifb_engine::linear_allocator_reserve(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle,
    const ifb_u32                        size) {

    //get the core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //get the allocator
    IFBEngineLinearAllocator* linear_allocator_ptr = ifb_engine::linear_allocator_from_handle(linear_allocator_handle);
    if (!linear_allocator_ptr) {
        return{0};
    }

    //get the arena info
    IFBEngineArena arena;
    arena.arena_id = linear_allocator_ptr->arena_id;
    ifb_engine::controller_arena(engine_core,arena);

    //get the handle of the current position
    const IFBEngineMemoryHandle memory_handle = ifb_engine::memory_handle(arena.page_start,linear_allocator_ptr->position);

    //calculate new position
    const ifb_u32 position_new = linear_allocator_ptr->position + size;

    //sanity check
    if (position_new > arena.memory_size) {
        IFBEngineMemoryHandle handle = {0};
        return(handle);
    }

    //update the position
    linear_allocator_ptr->position = position_new;

    //we're done
    return(memory_handle);
}

ifb_api const IFBEngineMemoryHandle
ifb_engine::linear_allocator_release(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle,
    const ifb_u32                        size) {

    IFBEngineMemoryHandle memory_handle = {0};

    //get the core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //get the allocator    
    IFBEngineLinearAllocator* linear_allocator_ptr = ifb_engine::linear_allocator_from_handle(linear_allocator_handle);

    //get the arena info
    IFBEngineArena arena;
    arena.arena_id = linear_allocator_ptr->arena_id;
    ifb_engine::controller_arena(engine_core,arena);

    //sanity check
    if (size > linear_allocator_ptr->position) {
        return(memory_handle);
    }

    //update the position
    linear_allocator_ptr->position -= size;

    //get the handle
    memory_handle = ifb_engine::memory_handle(
        arena.page_start,
        linear_allocator_ptr->position);

    //we're done
    return(memory_handle);
}

ifb_api const ifb_b8
ifb_engine::linear_allocator_save_point_set(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle) {

    //get the allocator
    IFBEngineLinearAllocator* linear_allocator_ptr = ifb_engine::linear_allocator_from_handle(linear_allocator_handle);
    if (!linear_allocator_ptr) {
        return(false);
    }

    //set the save point to the current position
    linear_allocator_ptr->save_point = linear_allocator_ptr->position; 

    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::linear_allocator_save_point_clear(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle) {

    //get the allocator
    IFBEngineLinearAllocator* linear_allocator_ptr = ifb_engine::linear_allocator_from_handle(linear_allocator_handle);
    if (!linear_allocator_ptr) {
        return(false);
    }

    //clear the save point
    linear_allocator_ptr->save_point = 0; 

    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::linear_allocator_reset(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle) {

    //get the allocator
    IFBEngineLinearAllocator* linear_allocator_ptr = ifb_engine::linear_allocator_from_handle(linear_allocator_handle);
    if (!linear_allocator_ptr) {
        return(false);
    }

    //reset position and save point
    linear_allocator_ptr->position   = 0;
    linear_allocator_ptr->save_point = 0;

    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::linear_allocator_reset_to_save_point(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle) {

    //get the allocator
    IFBEngineLinearAllocator* linear_allocator_ptr = ifb_engine::linear_allocator_from_handle(linear_allocator_handle);
    if (!linear_allocator_ptr) {
        return(false);
    }

    //set the position to the save point
    linear_allocator_ptr->save_point = linear_allocator_ptr->position;

    //we're done
    return(true);
}

inline IFBEngineLinearAllocator* 
ifb_engine::linear_allocator_from_handle(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle) {

    IFBEngineLinearAllocator* linear_allocator_ptr = (IFBEngineLinearAllocator*)ifb_engine::memory_pointer_from_handle(linear_allocator_handle.memory);

    return(linear_allocator_ptr);
}
