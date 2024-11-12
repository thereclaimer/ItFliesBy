#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineMemory { 
    ifb_u32 page_size;
    ifb_u32 page_count_total;
    ifb_u32 page_count_used;
};

struct IFBEngineMemoryPageCommit {
    ifb_u32 page_start;
    ifb_u32 page_count;
};

namespace ifb_engine {

    IFBEngineMemory*
    memory_create(
        const ifb_memory start,
        const ifb_u32    page_size,
        const ifb_u32    page_count);

    const ifb_memory
    memory_get_pointer(
        IFBEngineMemory* memory_ptr,
        const ifb_u32    page_number,
        const ifb_u32    page_offset);

    const ifb_memory
    memory_get_page_pointer(
              IFBEngineMemory* memory_ptr,
        const ifb_u32          page_number);

    const ifb_memory
    memory_get_current_page_pointer(
        IFBEngineMemory* memory_ptr);

    const ifb_size
    memory_size_page_aligned(
              IFBEngineMemory* memory_ptr,
        const ifb_size         memory_size);

    const ifb_u32
    memory_page_count_aligned(
              IFBEngineMemory* memory_ptr,
        const ifb_size         memory_size);

    const ifb_size
    memory_page_size(
              IFBEngineMemory* memory_ptr,
        const ifb_u32          page_count);

    const ifb_b8
    memory_commit_pages(
              IFBEngineMemory* in_memory_ptr,
        const ifb_u32          in_page_count,                
              ifb_u32&        out_page_start_ref);

    const ifb_b8
    memory_commit_size(
              IFBEngineMemory*            in_memory_ptr,
        const ifb_size                    in_memory_size,
              IFBEngineMemoryPageCommit& out_memory_page_commit);

    const ifb_memory
    memory_commit_immediate(
              IFBEngineMemory* memory_ptr,
        const ifb_size         memory_size);
};

#define ifb_engine_memory_commit_struct_immediate(                  \
    memory,                                                         \     
    type)                                                           \
                                                                    \
    (type*)ifb_engine::memory_commit_immediate(memory,sizeof(type)) \

/**********************************************************************************/
/* STACK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineMemoryStackAllocator {
    ifb_u32 page_start;
    ifb_u32 page_count;
    ifb_u32 stack_offset;
    ifb_u32 push_count;
};

namespace ifb_engine {

    const ifb_b8 
    memory_stack_allocator_create(
              IFBEngineMemory* memory_ptr, 
        const ifb_u32          stack_size_minimum);
    

    const ifb_b8
    memory_stack_allocator_push(
              IFBEngineMemoryStackAllocator& stack_allocator_ref,
        const ifb_u32                        stack_push_size);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineMemoryBlockAllocator {
    ifb_u32 page_start;
    ifb_u32 page_count;
    ifb_u32 block_size;
    ifb_u32 block_count;
};

struct IFBEngineMemoryBlock {
    ifb_u32 block_index;
};




#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP