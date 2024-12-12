#ifndef IFB_ENGINE_INTERNAL_ALLOCATORS_HPP
#define IFB_ENGINE_INTERNAL_ALLOCATORS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-managers.hpp"

/**********************************************************************************/
/* LINEAR ALLOCATOR                                                               */
/**********************************************************************************/

namespace ifb_engine {

    IFBLinearAllocator* linear_allocator_pointer(const IFBHNDLinearAllocator linear_allocator_handle);

    const IFBHNDLinearAllocator  
    linear_allocator_commit(
        const ifb_cstr linear_allocator_tag_cstr,
        const ifb_u32  linear_allocator_size_minimum);
    
    const ifb_u32 linear_allocator_reserve             (const IFBHNDLinearAllocator linear_allocator_handle, const ifb_u32 size);
    const ifb_u32 linear_allocator_release             (const IFBHNDLinearAllocator linear_allocator_handle, const ifb_u32 size);
    const ifb_ptr linear_allocator_get_pointer         (const IFBHNDLinearAllocator linear_allocator_handle);
    const ifb_b8  linear_allocator_save_point_set      (const IFBHNDLinearAllocator linear_allocator_handle);
    const ifb_b8  linear_allocator_save_point_clear    (const IFBHNDLinearAllocator linear_allocator_handle);
    const ifb_b8  linear_allocator_reset               (const IFBHNDLinearAllocator linear_allocator_handle);
    const ifb_b8  linear_allocator_reset_to_save_point (const IFBHNDLinearAllocator linear_allocator_handle);

};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

namespace ifb_engine {

    const IFBHNDBlockAllocator 
    block_allocator_commit(
        const ifb_cstr block_allocator_tag_cstr,
        const ifb_u32  block_size,
        const ifb_u32  block_count);

    const ifb_b8  block_allocator_reserve     (const IFBHNDBlockAllocator block_allocator_handle, ifb_index& ref_block_index);
    const ifb_b8  block_allocator_release     (const IFBHNDBlockAllocator block_allocator_handle, const ifb_index block_index);
    const ifb_ptr block_allocator_get_pointer (const IFBHNDBlockAllocator block_allocator_handle, const ifb_index block_index);
    const ifb_b8  block_allocator_reset       (const IFBHNDBlockAllocator block_allocator_handle);
};

#endif //IFB_ENGINE_INTERNAL_ALLOCATORS_HPP