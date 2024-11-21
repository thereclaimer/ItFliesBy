#ifndef IFB_ENGINE_INTERNAL_ALLOCATORS_HPP
#define IFB_ENGINE_INTERNAL_ALLOCATORS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* STACK ALLOCATOR                                                                */
/**********************************************************************************/

#define IFB_ENGINE_STACK_ALLOCATOR_COUNT_MAX 1024
#define IFB_ENGINE_STACK_ALLOCATOR_INVALID   1024

namespace ifb_engine {

    const ifb_b8  stack_allocator_table_initialize (IFBEngineTableStackAllocator& stack_allocator_table);
    const ifb_u32 stack_allocator_next_available   (IFBEngineTableStackAllocator& stack_allocator_table_ref);

    ifb_void 
    stack_allocator_update_arena_index(
              IFBEngineTableStackAllocator& stack_allocator_table_ref,
        const ifb_u32                       stack_allocator_index,
        const ifb_u32                       stack_allocator_arena_index);

    ifb_void 
    stack_allocator_update_used(
              IFBEngineTableStackAllocator& stack_allocator_table_ref,
        const ifb_u32                       stack_allocator_index,
        const ifb_u32                       stack_allocator_used);

    const ifb_u32 
    stack_allocator_get_arena_index(
              IFBEngineTableStackAllocator& stack_allocator_table_ref,
        const ifb_u32                       stack_allocator_index);

    const ifb_u32
    stack_allocator_get_used(
              IFBEngineTableStackAllocator& stack_allocator_table_ref,
        const ifb_u32                       stack_allocator_index);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

#define IFB_ENGINE_BLOCK_ALLOCATOR_COUNT_MAX 128

struct IFBEngineBlockAllocatorTable {
    ifb_u32 row_count;
    ifb_u32 column_handle_arena_index;
    ifb_u32 column_handle_block_count;
    ifb_u32 column_handle_block_size;
};

struct IFBEngineBlockAllocatorTableColumnMemory {
    ifb_u32* arena_index_ptr;
    ifb_u32* block_count_ptr;
    ifb_u32* block_size_ptr;
};

/**********************************************************************************/
/* ALLOCATORS                                                                     */
/**********************************************************************************/

namespace ifb_engine {

    ifb_void allocator_tables_initialize(ifb_void); 
};



#endif //IFB_ENGINE_INTERNAL_ALLOCATORS_HPP