#ifndef IFB_ENGINE_ALLOCATORS_HPP
#define IFB_ENGINE_ALLOCATORS_HPP

#include <ifb-common.hpp>

#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* LINEAR ALLOCATOR                                                               */
/**********************************************************************************/

namespace ifb_engine {

    ifb_api const IFBLinearAllocatorId  
    linear_allocator_create(
        const ifb_cstr linear_allocator_tag_cstr,
        const ifb_u32  linear_allocator_size_minimum);
    
    ifb_api const ifb_ptr linear_allocator_get_pointer         (const IFBLinearAllocatorId linear_allocator_id, const ifb_u32 position);
    ifb_api const ifb_b8  linear_allocator_reserve             (const IFBLinearAllocatorId linear_allocator_id, const ifb_u32 size, ifb_u32& ref_position);
    ifb_api const ifb_b8  linear_allocator_release             (const IFBLinearAllocatorId linear_allocator_id, const ifb_u32 size);
    ifb_api const ifb_b8  linear_allocator_save_point_set      (const IFBLinearAllocatorId linear_allocator_id);
    ifb_api const ifb_b8  linear_allocator_save_point_clear    (const IFBLinearAllocatorId linear_allocator_id);
    ifb_api const ifb_b8  linear_allocator_reset               (const IFBLinearAllocatorId linear_allocator_id);
    ifb_api const ifb_b8  linear_allocator_reset_to_save_point (const IFBLinearAllocatorId linear_allocator_id);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

namespace ifb_engine {

    ifb_api const IFBBlockAllocatorId 
    block_allocator_create(
        const ifb_cstr block_allocator_tag,
        const ifb_u32  block_size,
        const ifb_u32  block_count);

    ifb_api const ifb_b8  block_allocator_reserve     (const IFBBlockAllocatorId block_allocator_id, ifb_index& ref_block_index);
    ifb_api const ifb_b8  block_allocator_release     (const IFBBlockAllocatorId block_allocator_id, const ifb_index, block_index);
    ifb_api const ifb_ptr block_allocator_get_pointer (const IFBBlockAllocatorId block_allocator_id, const ifb_index, block_index);
    ifb_api const ifb_b8  block_allocator_reset       (const IFBBlockAllocatorId block_allocator_id);
};

#endif //IFB_ENGINE_ALLOCATORS_HPP