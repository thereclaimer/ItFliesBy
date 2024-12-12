#pragma once

#include "ifb-engine.hpp"

#include "ifb-engine-internal-allocators.hpp"
#include "ifb-engine-internal-context.hpp"
#include "ifb-engine-internal-core.hpp"

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
    IFBLinearAllocator* linear_allocator_ptr = ifb_engine::linear_allocator_pointer(linear_allocator_handle); 
    ifb_macro_assert(linear_allocator_ptr);
    
    //commit an arena
    IFBArena linear_allocator_arena;
    ifb_engine::core_arena_commit(
        linear_allocator_tag_cstr,
        linear_allocator_size_minimum,
        &linear_allocator_arena);

    //initialize the structure
    linear_allocator_ptr->arena_id   = linear_allocator_arena.id;
    linear_allocator_ptr->start      = linear_allocator_arena.start;
    linear_allocator_ptr->size       = linear_allocator_arena.size;
    linear_allocator_ptr->position   = 0;
    linear_allocator_ptr->save_point = 0;

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
    const ifb_u32 position     = ptr_linear_allocator->position;
    const ifb_u32 new_position = position + size;
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
    IFBEngineMemory*    ptr_memory           = ifb_engine::context_get_memory();
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

inline const ifb_u32
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