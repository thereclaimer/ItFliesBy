#ifndef IFB_ENGINE_INTERNAL_ALLOCATORS_HPP
#define IFB_ENGINE_INTERNAL_ALLOCATORS_HPP

/**********************************************************************************/
/* STACK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineStackAllocatorTable {
    ifb_u32 row_count;
    ifb_u32 column_handle_arena_index;
    ifb_u32 column_handle_stack_allocator_index;
    ifb_u32 column_handle_used;
};

namespace ifb_engine {

};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineBlockAllocatorTable {
    ifb_u32 row_count;
    ifb_u32 column_handle_arena_index;
    ifb_u32 column_handle_block_allocator_index;
    ifb_u32 column_handle_block_count;
    ifb_u32 column_handle_block_size;
};

/**********************************************************************************/
/* ALLOCATORS                                                                     */
/**********************************************************************************/

struct IFBEngineAllocators {

};

#endif //IFB_ENGINE_INTERNAL_ALLOCATORS_HPP