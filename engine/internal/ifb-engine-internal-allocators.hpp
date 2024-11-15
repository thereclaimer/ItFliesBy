#ifndef IFB_ENGINE_INTERNAL_ALLOCATORS_HPP
#define IFB_ENGINE_INTERNAL_ALLOCATORS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* STACK ALLOCATOR                                                                */
/**********************************************************************************/

#define IFB_ENGINE_STACK_ALLOCATOR_COUNT_MAX 128

struct IFBEngineStackAllocatorTable {
    ifb_u32 row_count;
    ifb_u32 column_handle_arena_index;
    ifb_u32 column_handle_used;
};

struct IFBEngineStackAllocatorTableColumnMemory {
    ifb_u32* arena_index_ptr;
    ifb_u32* used_ptr;
};

namespace ifb_engine {

    IFBEngineStackAllocatorTable* stack_allocator_table_from_handle (const ifb_u32 stack_allocator_table_handle);

    const ifb_b8 stack_allocator_table_initialize(const ifb_u32 stack_allocator_table_handle);
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

struct IFBEngineAllocatorManager {
    ifb_u32 table_handle_stack_allocators;
    ifb_u32 table_handle_block_allocators;
};

namespace ifb_engine {

    const ifb_u32 allocator_manager_start_up(ifb_void);

    IFBEngineAllocatorManager* allocator_manager_from_handle  (const ifb_u32 allocator_manager_handle);
    IFBEngineAllocatorManager* allocator_manager_from_context (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_ALLOCATORS_HPP