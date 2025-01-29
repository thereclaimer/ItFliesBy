#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemory;
struct IFBMemoryArena;
struct IFBMemoryPage;
struct IFBMemoryPageCommit;
struct IFBMemoryStack;
struct IFBMemoryReservation;
struct IFBMemoryArena;
struct IFBMemoryArenaTable;
struct IFBMemoryLinearAllocator;
struct IFBMemoryBlockAllocator;

typedef IFBMemory*                IFBMemoryHandle;
typedef IFBMemoryArena*           IFBMemoryArenaHandle;
typedef IFBMemoryLinearAllocator* IFBMemoryLinearAllocatorHandle;
typedef IFBMemoryBlockAllocator*  IFBMemoryBlockAllocatorHandle;

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_memory {

    const IFBMemoryHandle
    create(
        const IFBPlatformApi& platform_api_ref,
        const ifb_byte*       stack_memory,
        const ifb_u32         stack_size,
        const ifb_u32         arena_count);
    
    const ifb_b8 destroy(const IFBMemoryHandle memory_handle);
};


/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_memory {

    //push
    const ifb_ptr stack_push         (const IFBMemoryHandle memory_handle, const ifb_u32 size);
    const ifb_ptr stack_push_aligned (const IFBMemoryHandle memory_handle, const ifb_u32 size, const ifb_u32 alignment);
};

#define ifb_memory_macro_stack_push_struct(memory_handle,struct) ifb_memory::stack_push_aligned(memory_handle, sizeof(struct), alignof(struct))

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

namespace ifb_memory {

    //reserve/release
    const ifb_b8 reserve (const IFBMemoryHandle memory_handle, const ifb_u64 reservation_size_minimum);
    const ifb_b8 release (const IFBMemoryHandle memory_handle);

    //alignment
    const ifb_u32 reservation_size_align_to_page        (const IFBMemoryHandle memory_handle, const ifb_u32 size);    
    const ifb_u32 reservation_size_align_to_granularity (const IFBMemoryHandle memory_handle, const ifb_u32 size);
    
    //pages
    const ifb_u32 reservation_get_page_size            (const IFBMemoryHandle memory_handle);
    const ifb_u32 reservation_get_page_count_total     (const IFBMemoryHandle memory_handle);
    const ifb_u32 reservation_get_page_count_committed (const IFBMemoryHandle memory_handle);
    const ifb_u32 reservation_get_page_count_free      (const IFBMemoryHandle memory_handle);
    const ifb_u32 reservation_get_page_count_from_size (const IFBMemoryHandle memory_handle, const ifb_u32 size);

    //size
    const ifb_u64 reservation_get_size_total     (const IFBMemoryHandle memory_handle);
    const ifb_u64 reservation_get_size_committed (const IFBMemoryHandle memory_handle);
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
        ifb_u32* sizes;
    } linear_allocators;
};

struct IFBMemoryArenaCommitResult {
    struct {
        IFBMemoryLinearAllocatorHandle* linear;
        IFBMemoryBlockAllocatorHandle*  block;
    } allocator_handle_arrays;
};

namespace ifb_memory {

    //commit
    const IFBMemoryArenaHandle
    arena_commit(
        const IFBMemoryHandle memory_handle,
        const ifb_u32         arena_size_minimum);

    const IFBMemoryArenaHandle
    arena_commit(
        const IFBMemoryHandle              memory_handle,
        const IFBMemoryArenaCommitRequest& arena_commit_request_ref,
              IFBMemoryArenaCommitResult&  arena_commit_result_ref);

    //reset
    const ifb_b8 arena_reset_all             (const IFBMemoryArenaHandle arena_handle);
    const ifb_b8 arena_reset_allocators      (const IFBMemoryArenaHandle arena_handle);
    const ifb_b8 arena_reset_scratch_space   (const IFBMemoryArenaHandle arena_handle);

    //push/pull
    const ifb_ptr arena_scratch_push         (const IFBMemoryArenaHandle arena_handle, const ifb_u32 size);
    const ifb_ptr arena_scratch_pull         (const IFBMemoryArenaHandle arena_handle, const ifb_u32 size);
    const ifb_ptr arena_scratch_push_aligned (const IFBMemoryArenaHandle arena_handle, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr arena_scratch_pull_aligned (const IFBMemoryArenaHandle arena_handle, const ifb_u32 size, const ifb_u32 alignment);

    //size/count
    const ifb_u32 arena_get_page_count       (const IFBMemoryArenaHandle arena_handle);
    const ifb_u32 arena_get_page_start       (const IFBMemoryArenaHandle arena_handle);    
    const ifb_u32 arena_get_size_total       (const IFBMemoryArenaHandle arena_handle);    
    const ifb_u32 arena_get_size_allocators  (const IFBMemoryArenaHandle arena_handle);    
    const ifb_u32 arena_get_size_scratch     (const IFBMemoryArenaHandle arena_handle);    
};

/**********************************************************************************/
/* LINEAR ALLOCATOR                                                               */
/**********************************************************************************/

namespace ifb_memory {

    //save point
    const ifb_ptr linear_allocator_save_point_set      (const IFBMemoryLinearAllocatorHandle stack_allocator_handle);
    const ifb_ptr linear_allocator_save_point_clear    (const IFBMemoryLinearAllocatorHandle stack_allocator_handle);
    const ifb_ptr linear_allocator_save_point_get      (const IFBMemoryLinearAllocatorHandle stack_allocator_handle);
    
    //reset
    const ifb_ptr linear_allocator_reset               (const IFBMemoryLinearAllocatorHandle stack_allocator_handle);
    const ifb_ptr linear_allocator_reset_to_save_point (const IFBMemoryLinearAllocatorHandle stack_allocator_handle);

    //push/pull    
    const ifb_ptr linear_allocator_reserve             (const IFBMemoryLinearAllocatorHandle stack_allocator_handle, const ifb_u32 size);
    const ifb_ptr linear_allocator_release             (const IFBMemoryLinearAllocatorHandle stack_allocator_handle, const ifb_u32 size);
    const ifb_ptr linear_allocator_reserve_aligned     (const IFBMemoryLinearAllocatorHandle stack_allocator_handle, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr linear_allocator_release_aligned     (const IFBMemoryLinearAllocatorHandle stack_allocator_handle, const ifb_u32 size, const ifb_u32 alignment);
    
    //size
    const ifb_u32 stack_allocator_get_size_total       (const IFBMemoryLinearAllocatorHandle stack_allocator_handle);
    const ifb_u32 stack_allocator_get_size_used        (const IFBMemoryLinearAllocatorHandle stack_allocator_handle);
    const ifb_u32 stack_allocator_get_size_free        (const IFBMemoryLinearAllocatorHandle stack_allocator_handle);
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