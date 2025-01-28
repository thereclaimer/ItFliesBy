#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryManager;
struct IFBMemoryArena;
struct IFBMemoryStackAllocator;
struct IFBMemoryBlockAllocator;

struct IFBMemoryHandle {
    ifb_u32 stack_offset;
};

/**********************************************************************************/
/* GLOBAL STACK                                                                   */
/**********************************************************************************/

namespace ifb_memory {

    const IFBMemoryHandle stack_push         (IFBMemoryManager* memory_manager_ptr, const ifb_u32 size);
    const IFBMemoryHandle stack_push_aligned (IFBMemoryManager* memory_manager_ptr, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr         stack_get_pointer  (IFBMemoryManager* memory_manager_ptr, const IFBMemoryHandle memory_handle);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                    */
/**********************************************************************************/

namespace ifb_memory {

    const IFBMemoryManager*
    manager_create(
        ifb_byte* stack_memory,
        ifb_u32   stack_size);
    
    const ifb_b8
    manager_destroy(
        IFBMemoryManager* memory_manager_ptr);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

namespace ifb_memory {

    const ifb_b8
    reserve(
              IFBMemoryManager* memory_manager_ptr,
        const ifb_u64           size,
        const ifb_u32           page_size,
        const ifb_u32           allocation_granularity);
    
    const ifb_b8 release(IFBMemoryManager* memory_manager_ptr);

    const ifb_address reservation_get_start_address   (const IFBMemoryManager* memory_manager_ptr);
    const ifb_ptr     reservation_get_start_pointer   (const IFBMemoryManager* memory_manager_ptr);
    const ifb_u32     reservation_get_page_size       (const IFBMemoryManager* memory_manager_ptr);
    const ifb_u32     reservation_get_pages_total     (const IFBMemoryManager* memory_manager_ptr);
    const ifb_u32     reservation_get_pages_committed (const IFBMemoryManager* memory_manager_ptr);
    const ifb_u64     reservation_get_size_total      (const IFBMemoryManager* memory_manager_ptr);
    const ifb_u64     reservation_get_size_committed  (const IFBMemoryManager* memory_manager_ptr);

};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

namespace ifb_memory {

    const IFBMemoryArena*
    arena_commit(
              IFBMemoryManager* memory_manager_ptr,
        const ifb_u32           arena_size_minimum);

    const ifb_u32     arena_get_page_count    (const IFBMemoryArena* arena_ptr);
    const ifb_u32     arena_get_page_number   (const IFBMemoryArena* arena_ptr);    
    const ifb_u32     arena_get_size          (const IFBMemoryArena* arena_ptr);    
    const ifb_ptr     arena_get_start_pointer (const IFBMemoryArena* arena_ptr);
    const ifb_address arena_get_start_address (const IFBMemoryArena* arena_ptr);
    const ifb_ptr     arena_get_pointer       (const IFBMemoryArena* arena_ptr, const ifb_u32 offset);
    const ifb_address arena_get_address       (const IFBMemoryArena* arena_ptr, const ifb_u32 offset);
};

/**********************************************************************************/
/* STACK ALLOCATOR                                                                */
/**********************************************************************************/

namespace ifb_memory {

    IFBMemoryStackAllocator* 
    stack_allocator_create(
        const IFBMemoryArena* arena,
        const ifb_u32         size);

    const ifb_ptr stack_allocator_reset        (IFBMemoryStackAllocator* stack_allocator);
    const ifb_ptr stack_allocator_push         (IFBMemoryStackAllocator* stack_allocator, const ifb_u32 size);
    const ifb_ptr stack_allocator_pull         (IFBMemoryStackAllocator* stack_allocator, const ifb_u32 size);
    const ifb_ptr stack_allocator_push_aligned (IFBMemoryStackAllocator* stack_allocator, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr stack_allocator_pull_aligned (IFBMemoryStackAllocator* stack_allocator, const ifb_u32 size, const ifb_u32 alignment);

    const ifb_u32 stack_allocator_get_size_total (const IFBMemoryStackAllocator* stack_allocator);
    const ifb_u32 stack_allocator_get_size_used  (const IFBMemoryStackAllocator* stack_allocator);
    const ifb_u32 stack_allocator_get_size_free  (const IFBMemoryStackAllocator* stack_allocator);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

namespace ifb_memory {

    IFBMemoryBlockAllocator*
    block_allocator_create(
        const IFBMemoryArena* arena,
        const ifb_u32         block_size,
        const ifb_u32         block_count);

    const ifb_ptr block_allocator_reserve_block (IFBMemoryBlockAllocator* block_allocator);
    const ifb_ptr block_allocator_release_block (IFBMemoryBlockAllocator* block_allocator);

    const ifb_u32 block_allocator_get_size_total        (const IFBMemoryBlockAllocator* block_allocator);
    const ifb_u32 block_allocator_get_block_size        (const IFBMemoryBlockAllocator* block_allocator)
    const ifb_u32 block_allocator_get_block_count_total (const IFBMemoryBlockAllocator* block_allocator)
    const ifb_u32 block_allocator_get_block_count_used  (const IFBMemoryBlockAllocator* block_allocator)
    const ifb_u32 block_allocator_get_block_count_free  (const IFBMemoryBlockAllocator* block_allocator)
};


#endif //IFB_MEMORY_HPP