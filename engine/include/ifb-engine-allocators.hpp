#ifndef IFB_ENGINE_ALLOCATORS_HPP
#define IFB_ENGINE_ALLOCATORS_HPP

#include <ifb-common.hpp>

#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* STACK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineStackAllocator {
};

namespace ifb_engine {

    ifb_api const ifb_b8
    stack_allocator_create(
        const ifb_cstr                    in_stack_allocator_tag,
        const ifb_u32                     in_stack_size_minimum,
              IFBEngineStackAllocatorId& out_stack_allocator_id_ref);
    
    ifb_api const IFBEngineArenaId    stack_allocator_arena_id       (const IFBEngineStackAllocatorId stack_allocator_id);
    ifb_api const IFBEngineTagId      stack_allocator_arena_tag_id   (const IFBEngineStackAllocatorId stack_allocator_id);
    ifb_api const ifb_handle_memory   stack_allocator_pointer_handle (const IFBEngineStackAllocatorId stack_allocator_id);
    
    ifb_api const ifb_b8     stack_allocator_valid            (const IFBEngineStackAllocatorId stack_allocator_id);
    ifb_api const ifb_u32    stack_allocator_size_total       (const IFBEngineStackAllocatorId stack_allocator_id);
    ifb_api const ifb_u32    stack_allocator_size_used        (const IFBEngineStackAllocatorId stack_allocator_id);
    ifb_api const ifb_u32    stack_allocator_arena_page_start (const IFBEngineStackAllocatorId stack_allocator_id);
    ifb_api const ifb_u32    stack_allocator_arena_page_count (const IFBEngineStackAllocatorId stack_allocator_id);
    ifb_api const ifb_cstr   stack_allocator_arena_tag_value  (const IFBEngineStackAllocatorId stack_allocator_id);
    ifb_api const ifb_b8     stack_allocator_reset            (const IFBEngineStackAllocatorId stack_allocator_id);
    ifb_api const ifb_memory stack_allocator_pointer_memory   (const IFBEngineStackAllocatorId stack_allocator_id);

    ifb_api const ifb_u32    stack_allocator_push_handle (const IFBEngineStackAllocatorId stack_allocator_id, const ifb_u32 size);
    ifb_api const ifb_memory stack_allocator_push_memory (const IFBEngineStackAllocatorId stack_allocator_id, const ifb_u32 size);
    ifb_api const ifb_b8     stack_allocator_pull        (const IFBEngineStackAllocatorId stack_allocator_id, const ifb_u32 size);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineBlockAllocator {
    ifb_u32 block_allocator_index;
    ifb_u32 block_count;
    ifb_u32 block_size;
};

namespace ifb_engine {

    ifb_api const ifb_u32  block_allocator_create           (const ifb_cstr block_allocator_tag, const ifb_u32 block_size, const ifb_u32 block_count);;
    ifb_api const ifb_u32  block_allocator_block_count      (const ifb_u32  block_allocator_index);
    ifb_api const ifb_u32  block_allocator_block_size       (const ifb_u32  block_allocator_index);
    ifb_api const ifb_u32  block_allocator_arena_index      (const ifb_u32  block_allocator_index);
    ifb_api const ifb_u32  block_allocator_arena_page_start (const ifb_u32  block_allocator_index);
    ifb_api const ifb_u32  block_allocator_arena_page_count (const ifb_u32  block_allocator_index);
    ifb_api const ifb_u32  block_allocator_arena_tag_index  (const ifb_u32  block_allocator_index);
    ifb_api const ifb_cstr block_allocator_arena_tag_value  (const ifb_u32  block_allocator_index);
    ifb_api const ifb_b8   block_allocator_reset            (const ifb_u32  block_allocator_index);

    ifb_api const ifb_b8     block_allocator_reserve_block (const ifb_u32 in_block_allocator_index, ifb_u32& out_block_index_ref);
    ifb_api const ifb_b8     block_allocator_release_block (const ifb_u32 block_allocator_index,    ifb_u32  block_index);
    ifb_api const ifb_u32    block_allocator_handle        (const ifb_u32 block_allocator_index,    ifb_u32  block_index);
    ifb_api const ifb_memory block_allocator_memory        (const ifb_u32 block_allocator_index,    ifb_u32  block_index);
};

#endif //IFB_ENGINE_ALLOCATORS_HPP