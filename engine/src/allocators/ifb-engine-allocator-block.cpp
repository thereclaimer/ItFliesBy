#pragma once

#include "ifb-engine-allocators.hpp"

ifb_api const ifb_b8 
ifb_engine::block_allocator_create(
    const ifb_cstr                        in_block_allocator_tag,
    const ifb_u32                         in_block_size,
    const ifb_u32                         in_block_count,
          IFBEngineBlockAllocatorHandle& out_block_allocator_handle_ref) {

    return(false);
}

ifb_api const ifb_b8 
ifb_engine::block_allocator_reserve(
    const IFBEngineBlockAllocatorHandle in_block_allocator_handle, 
          IFBEngineBlockMemoryHandle&  out_block_ref) {
    
    return(false);
}

ifb_api const ifb_b8
ifb_engine::block_allocator_release(
    const IFBEngineBlockAllocatorHandle block_allocator_handle, 
          IFBEngineBlockMemoryHandle&   block_ref) {

    return(false);
}

ifb_api const ifb_b8
ifb_engine::block_allocator_reset(
    const IFBEngineBlockAllocatorHandle in_block_allocator_handle) {

    return(false);
}