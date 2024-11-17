#ifndef IFB_ENGINE_ALLOCATORS_HPP
#define IFB_ENGINE_ALLOCATORS_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"
#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* STACK ALLOCATOR                                                                */
/**********************************************************************************/

typedef ifb_index ifb_index_stack_t;

struct IFBEngineStackAllocator {
    ifb_index_stack_t stack_allocator_index;
    ifb_index_arena_t arena_index;
    ifb_u32           used;
};

namespace ifb_engine {

    ifb_api const ifb_index_stack_t    stack_allocator_create           (const ifb_cstr stack_allocator_tag, const ifb_u32 stack_size_minimum);
    
    ifb_api const ifb_index_arena_t    stack_allocator_arena_index      (const ifb_index_stack_t stack_allocator_index);
    ifb_api const ifb_index_tag_t      stack_allocator_arena_tag_index  (const ifb_index_stack_t stack_allocator_index);
    ifb_api const ifb_handle_memory_t  stack_allocator_pointer_handle   (const ifb_index_stack_t stack_allocator_index);
    
    ifb_api const ifb_b8     stack_allocator_valid            (const ifb_index_stack_t stack_allocator_index);
    ifb_api const ifb_u32    stack_allocator_size_total       (const ifb_index_stack_t stack_allocator_index);
    ifb_api const ifb_u32    stack_allocator_size_used        (const ifb_index_stack_t stack_allocator_index);
    ifb_api const ifb_u32    stack_allocator_arena_page_start (const ifb_index_stack_t stack_allocator_index);
    ifb_api const ifb_u32    stack_allocator_arena_page_count (const ifb_index_stack_t stack_allocator_index);
    ifb_api const ifb_cstr   stack_allocator_arena_tag_value  (const ifb_index_stack_t stack_allocator_index);
    ifb_api const ifb_b8     stack_allocator_reset            (const ifb_index_stack_t stack_allocator_index);
    ifb_api const ifb_memory stack_allocator_pointer_memory   (const ifb_index_stack_t stack_allocator_index);

    ifb_api const ifb_u32    stack_allocator_push_handle (const ifb_index_stack_t stack_allocator_index, const ifb_u32 size);
    ifb_api const ifb_memory stack_allocator_push_memory (const ifb_index_stack_t stack_allocator_index, const ifb_u32 size);
    ifb_api const ifb_b8     stack_allocator_pull        (const ifb_index_stack_t stack_allocator_index, const ifb_u32 size);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

typedef ifb_index ifb_index_block_allocator_t;

struct IFBEngineBlockAllocator {
    ifb_index_arena_t           arena_index;
    ifb_index_block_allocator_t block_allocator_index;
    ifb_u32                     block_count;
    ifb_u32                     block_size;
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