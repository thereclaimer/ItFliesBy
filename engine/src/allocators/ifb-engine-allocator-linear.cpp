#pragma once

#include "ifb-engine-allocators.hpp"
#include "ifb-engine-internal-controllers.hpp"

ifb_api ifb_b8  
ifb_engine::linear_allocator_create(
    const ifb_cstr                         in_linear_allocator_tag_cstr,
    const ifb_u32                          in_linear_allocator_size_minimum,
          IFBEngineLinearAllocatorHandle& out_linear_allocator_handle) {

    IFBEngineTagId   tag_id;
    IFBEngineArenaId arena_id;
    ifb_b8 result = true;

    //commit memory for the allocator
    const ifb_u32 page_start = ifb_engine::memory_page_commit(sizeof(IFBEngineLinearAllocator));
    result &= page_start != 0;

    //create the tag and arena
    result &= ifb_engine::controller_tag_create(in_linear_allocator_tag_cstr,tag_id);
    result &= ifb_engine::controller_memory_arena_create(arena_id,in_linear_allocator_size_minimum,arena_id);

    //initialize the allocator
    IFBEngineLinearAllocator* linear_allocator_ptr = (IFBEngineLinearAllocator*)ifb_engine::memory_pointer_from_page(page_start);
    linear_allocator_ptr->arena_id   = arena_id;
    linear_allocator_ptr->position   = 0;
    linear_allocator_ptr->save_point = 0;

    //sanity check
    ifb_macro_assert(result);

    //we're done
    return(true);
}

ifb_api const IFBEngineMemoryHandle
ifb_engine::linear_allocator_reserve(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle,
    const ifb_u32                        size) {

    return({0});
}

ifb_api const IFBEngineMemoryHandle
ifb_engine::linear_allocator_release(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle,
    const ifb_u32                        size) {

    return({0});
}

ifb_api const ifb_b8
ifb_engine::linear_allocator_save_point_set(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle) {
    
    return({0});
}

ifb_api const ifb_b8
ifb_engine::linear_allocator_save_point_clear(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle) {

    return({0});
}

ifb_api const ifb_b8
ifb_engine::linear_allocator_reset(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle) {

    return({0});
}

ifb_api const ifb_b8
ifb_engine::linear_allocator_reset_to_save_point(
    const IFBEngineLinearAllocatorHandle linear_allocator_handle) {

    return({0});
}
