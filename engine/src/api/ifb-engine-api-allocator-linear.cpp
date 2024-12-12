#pragma once

#include "ifb-engine.hpp"

#include "ifb-engine-allocators.hpp"
#include "ifb-engine-internal-allocators.hpp"
#include "ifb-engine-internal-global.hpp"
#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-context.hpp"

inline IFBLinearAllocator* 
ifb_engine::linear_allocator_pointer(
    const IFBHNDLinearAllocator linear_allocator_handle) {

    IFBLinearAllocator* ptr_linear_allocator = (IFBLinearAllocator*)ifb_engine::context_get_pointer(linear_allocator_handle);

    return(ptr_linear_allocator);
}   

inline const IFBHNDLinearAllocator  
ifb_engine::linear_allocator_commit(
    const ifb_cstr linear_allocator_tag_cstr,
    const ifb_u32  linear_allocator_size_minimum) {

    //allocate a linear allocator
    IFBHNDLinearAllocator linear_allocator_handle;
    ifb_engine_context_push_struct(linear_allocator_handle,IFBLinearAllocator);

    //get the pointer
    IFBLinearAllocator* ptr_linear_allocator = ifb_engine::linear_allocator_pointer(linear_allocator_handle); 
    ifb_macro_assert(ptr_linear_allocator);

    //commit an arena
    IFBEngineArenaManager* arena_manager_ptr = ifb_engine::context_handles_get_arena_manager();
    const IFBIDArena arena_id = ifb_engine::arena_manager_commit_arena(
        arena_manager_ptr,
        linear_allocator_size_minimum,
        linear_allocator_tag_cstr);

    //get the arena info
    const ifb_u32 arena_size  = ifb_engine::arena_manager_get_arena_size (arena_manager_ptr, arena_id);
    const ifb_u32 arena_start = ifb_engine::arena_manager_get_arena_start(arena_manager_ptr, arena_id);

    //initialize the structure
    ptr_linear_allocator->arena_id   = arena_id;
    ptr_linear_allocator->start      = arena_start;
    ptr_linear_allocator->size       = arena_size;
    ptr_linear_allocator->position   = 0;
    ptr_linear_allocator->save_point = 0;

    //we're done
    return(linear_allocator_handle);
}

inline const ifb_u32
ifb_engine::linear_allocator_reserve(
    const IFBHNDLinearAllocator linear_allocator_handle, 
    const ifb_u32               size) {

    //get references
    IFBLinearAllocator* ptr_linear_allocator = ifb_engine::linear_allocator_pointer(linear_allocator_handle); 

    //make sure we can fit the reservation
    ref_position = ptr_linear_allocator->position;
    const ifb_u32 new_position = ref_position + size;
    if (new_position > ptr_linear_allocator->size) {
        return(0);
    }

    //update the position
    ptr_linear_allocator->position = new_position;

    //calculate the offset
    const ifb_u32 offset = ptr_linear_allocator->start + new_position;

    //we're done
    return(offset);
}

inline const ifb_ptr
ifb_engine::linear_allocator_get_pointer(
    const IFBHNDLinearAllocator linear_allocator_handle) {
 
    //get references
    IFBEngineMemory*    ptr_memory           = ifb_engine::context_get_core_pointer_memory();
    IFBLinearAllocator* ptr_linear_allocator = ifb_engine::linear_allocator_pointer(linear_allocator_handle); 

    //calculate the offset
    const ifb_u32 offset = ptr_linear_allocator->start + ptr_linear_allocator->position;  

    //get the pointer
    const ifb_ptr pointer = ifb_engine::memory_get_pointer(
        ptr_memory,
        offset);

    //we're done
    return(pointer);
}

inline const ifb_b8
ifb_engine::linear_allocator_release(
    const IFBHNDLinearAllocator linear_allocator_handle,
    const ifb_u32               size) {

    
}

inline const ifb_b8
ifb_engine::linear_allocator_save_point_set(
    const IFBHNDLinearAllocator linear_allocator_handle) {

}

inline const ifb_b8
ifb_engine::linear_allocator_save_point_clear(
    const IFBHNDLinearAllocator linear_allocator_handle) {

}

inline const ifb_b8
ifb_engine::linear_allocator_reset(
    const IFBHNDLinearAllocator linear_allocator_handle) {

}

inline const ifb_b8
ifb_engine::linear_allocator_reset_to_save_point(
    const IFBHNDLinearAllocator linear_allocator_handle) {

}