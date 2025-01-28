#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemory;

struct IFBMemoryHandle               { ifb_u32 stack_offset; };
struct IFBMemoryArenaHandle          { ifb_ptr arena;        };          
struct IFBMemoryStackAllocatorHandle { ifb_ptr allocator;    };
struct IFBMemoryBlockAllocatorHandle { ifb_ptr allocator;    };

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_memory {

    IFBMemory* create(
        const IFBPlatformApi& platform_api_ref,
        const ifb_byte*       stack_memory,
        const ifb_u32         stack_size,
        const ifb_u32         arena_count);
    
    const ifb_b8 destroy(IFBMemory* memory_ptr);
};


/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_memory {

    //push
    const IFBMemoryHandle stack_push         (IFBMemory* memory_ptr, const ifb_u32 size);
    const IFBMemoryHandle stack_push_aligned (IFBMemory* memory_ptr, const ifb_u32 size, const ifb_u32 alignment);
   
    //pointers
    const ifb_ptr stack_get_pointer  (IFBMemory* memory_ptr, const IFBMemoryHandle memory_handle);
};

#define ifb_memory_macro_stack_push_struct(memory_ptr,struct) ifb_memory::stack_push_aligned(memory_ptr, sizeof(struct), alignof(struct))

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

namespace ifb_memory {

    const ifb_b8 reserve (IFBMemory* memory_ptr, const ifb_u64 reservation_size_minimum);
    const ifb_b8 release (IFBMemory* memory_ptr);

    const ifb_address reservation_get_start_address   (const IFBMemory* memory_ptr);
    const ifb_ptr     reservation_get_start_pointer   (const IFBMemory* memory_ptr);
    const ifb_u32     reservation_get_page_size       (const IFBMemory* memory_ptr);
    const ifb_u32     reservation_get_pages_total     (const IFBMemory* memory_ptr);
    const ifb_u32     reservation_get_pages_committed (const IFBMemory* memory_ptr);
    const ifb_u64     reservation_get_size_total      (const IFBMemory* memory_ptr);
    const ifb_u64     reservation_get_size_committed  (const IFBMemory* memory_ptr);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

struct IFBMemoryArenaCommitRequest {

    ifb_u32 scratch_space_minimum;
    
    struct {
        ifb_u32  count;
        ifb_u32* block_size_array;
        ifb_u32* block_count_array;
    } block_allocators;
    
    struct {
        ifb_u32  count;
        ifb_u32* stack_sizes;
    } stack_allocators;
};

struct IFBMemoryArenaCommitResult {
    struct {
        IFBMemoryStackAllocatorHandle* stack;
        IFBMemoryBlockAllocatorHandle* block;
    } allocator_handle_arrays;
};

namespace ifb_memory {

    //commit
    const IFBMemoryArenaId
    arena_commit(
              IFBMemory* memory_ptr,
        const ifb_u32    arena_size_minimum);

    const IFBMemoryArenaId
    arena_commit(
              IFBMemory*                   memory_ptr,
        const IFBMemoryArenaCommitRequest& arena_commit_request_ref,
              IFBMemoryArenaCommitResult&  arena_commit_result_ref);

    //reset
    const ifb_b8      arena_reset_all            (const IFBMemoryArenaId arena_id);
    const ifb_b8      arena_reset_allocators     (const IFBMemoryArenaId arena_id);
    const ifb_b8      arena_reset_scratch_space  (const IFBMemoryArenaId arena_id);

    //push/pull
    const ifb_ptr     arena_scratch_push         (const IFBMemoryArenaId arena_id, const ifb_u32 size);
    const ifb_ptr     arena_scratch_pull         (const IFBMemoryArenaId arena_id, const ifb_u32 size);
    const ifb_ptr     arena_scratch_push_aligned (const IFBMemoryArenaId arena_id, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr     arena_scratch_pull_aligned (const IFBMemoryArenaId arena_id, const ifb_u32 size, const ifb_u32 alignment);

    //size/count
    const ifb_u32     arena_get_page_count       (const IFBMemoryArenaId arena_id);
    const ifb_u32     arena_get_page_start       (const IFBMemoryArenaId arena_id);    
    const ifb_u32     arena_get_size_total       (const IFBMemoryArenaId arena_id);    
    const ifb_u32     arena_get_size_allocators  (const IFBMemoryArenaId arena_id);    
    const ifb_u32     arena_get_size_scratch     (const IFBMemoryArenaId arena_id);    
};

/**********************************************************************************/
/* STACK ALLOCATOR                                                                */
/**********************************************************************************/

namespace ifb_memory {

    //save point
    const ifb_ptr stack_allocator_save_point_set       (const IFBMemoryStackAllocatorHandle stack_allocator_handle);
    const ifb_ptr stack_allocator_save_point_clear     (const IFBMemoryStackAllocatorHandle stack_allocator_handle);
    const ifb_ptr stack_allocator_save_point_get       (const IFBMemoryStackAllocatorHandle stack_allocator_handle);
    
    //reset
    const ifb_ptr stack_allocator_reset                (const IFBMemoryStackAllocatorHandle stack_allocator_handle);
    const ifb_ptr stack_allocator_reset_to_save_point  (const IFBMemoryStackAllocatorHandle stack_allocator_handle);

    //push/pull    
    const ifb_ptr stack_allocator_push                 (const IFBMemoryStackAllocatorHandle stack_allocator_handle, const ifb_u32 size);
    const ifb_ptr stack_allocator_pull                 (const IFBMemoryStackAllocatorHandle stack_allocator_handle, const ifb_u32 size);
    const ifb_ptr stack_allocator_push_aligned         (const IFBMemoryStackAllocatorHandle stack_allocator_handle, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr stack_allocator_pull_aligned         (const IFBMemoryStackAllocatorHandle stack_allocator_handle, const ifb_u32 size, const ifb_u32 alignment);
    
    //size
    const ifb_u32 stack_allocator_get_size_total       (const IFBMemoryStackAllocatorHandle stack_allocator_handle);
    const ifb_u32 stack_allocator_get_size_used        (const IFBMemoryStackAllocatorHandle stack_allocator_handle);
    const ifb_u32 stack_allocator_get_size_free        (const IFBMemoryStackAllocatorHandle stack_allocator_handle);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

namespace ifb_memory {

    //reset
    const ifb_ptr block_allocator_reset                 (const IFBMemoryBlockAllocatorHandle block_allocator_handle);

    //reserve/release
    const ifb_ptr block_allocator_reserve_block         (const IFBMemoryBlockAllocatorHandle block_allocator_handle);
    const ifb_ptr block_allocator_release_block         (const IFBMemoryBlockAllocatorHandle block_allocator_handle);

    //size/count
    const ifb_u32 block_allocator_get_size_total        (const IFBMemoryBlockAllocatorHandle block_allocator_handle);
    const ifb_u32 block_allocator_get_block_size        (const IFBMemoryBlockAllocatorHandle block_allocator_handle);
    const ifb_u32 block_allocator_get_block_count_total (const IFBMemoryBlockAllocatorHandle block_allocator_handle);
    const ifb_u32 block_allocator_get_block_count_used  (const IFBMemoryBlockAllocatorHandle block_allocator_handle);
    const ifb_u32 block_allocator_get_block_count_free  (const IFBMemoryBlockAllocatorHandle block_allocator_handle);
};


#endif //IFB_MEMORY_HPP