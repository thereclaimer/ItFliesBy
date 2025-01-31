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
struct IFBMemoryLinearArena;
struct IFBMemoryBlockAllocator;

typedef IFBMemory*            IFBMemoryHandle;
typedef IFBMemoryArena*       IFBMemoryArenaHandle;
typedef IFBMemoryLinearArena* IFBMemoryLinearArenaHandle;
typedef IFBMemoryBlockArena*  IFBMemoryBlockArenaHandle;

typedef ifb_u32 IFBMemoryArenaType;

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

    //push absolute
    const ifb_ptr stack_push                  (const IFBMemoryHandle memory_handle, const ifb_u32 size);
    const ifb_ptr stack_push_aligned          (const IFBMemoryHandle memory_handle, const ifb_u32 size, const ifb_u32 alignment);

    //push offset
    const ifb_u32 stack_push_offset           (const IFBMemoryHandle memory_handle, const ifb_u32 size);
    const ifb_u32 stack_push_offset_aligned   (const IFBMemoryHandle memory_handle, const ifb_u32 size, const ifb_u32 alignment);
    
    //push relative
    const ifb_u32 stack_push_relative         (const IFBMemoryHandle memory_handle, const ifb_ptr reference, const ifb_u32 size);
    const ifb_u32 stack_push_relative_aligned (const IFBMemoryHandle memory_handle, const ifb_ptr reference, const ifb_u32 size, const ifb_u32 alignment);

    //pointers
    const ifb_ptr stack_get_pointer           (const IFBMemoryHandle memory_handle, const ifb_u32 stack_position);
    const ifb_ptr stack_get_pointer_relative  (const IFBMemoryHandle memory_handle, const ifb_u32 reference, const ifb_u32 offset);
};

#define ifb_memory_macro_stack_push_type(memory_handle,type)                    (struct*)ifb_memory::stack_push(memory_handle, sizeof(struct))
#define ifb_memory_macro_stack_push_type_relative(memory_handle,reference,type) ifb_memory::stack_push_relative(memory_handle, reference, sizeof(struct))

#define ifb_memory_macro_stack_push_struct(memory_handle,struct)                    (struct*)ifb_memory::stack_push_aligned(memory_handle, sizeof(struct), alignof(struct))
#define ifb_memory_macro_stack_push_struct_relative(memory_handle,reference,struct) ifb_memory::stack_push_relative_aligned(memory_handle, reference, sizeof(struct), alignof(struct))

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

namespace ifb_memory {

    //reserve/release
    const ifb_b8 reserve                                (const IFBMemoryHandle memory_handle, const ifb_u64 reservation_size_minimum);
    const ifb_b8 release                                (const IFBMemoryHandle memory_handle);

    //alignment
    const ifb_u32 reservation_size_align_to_page        (const IFBMemoryHandle memory_handle, const ifb_u32 size);    
    const ifb_u32 reservation_size_align_to_granularity (const IFBMemoryHandle memory_handle, const ifb_u32 size);
    
    //pages
    const ifb_u32 reservation_get_page_size             (const IFBMemoryHandle memory_handle);
    const ifb_u32 reservation_get_page_count_total      (const IFBMemoryHandle memory_handle);
    const ifb_u32 reservation_get_page_count_committed  (const IFBMemoryHandle memory_handle);
    const ifb_u32 reservation_get_page_count_free       (const IFBMemoryHandle memory_handle);
    const ifb_u32 reservation_get_page_count_from_size  (const IFBMemoryHandle memory_handle, const ifb_u32 size);

    //size
    const ifb_u64 reservation_get_size_total            (const IFBMemoryHandle memory_handle);
    const ifb_u64 reservation_get_size_committed        (const IFBMemoryHandle memory_handle);
};

/**********************************************************************************/
/* ARENA - BASE                                                                   */
/**********************************************************************************/

namespace ifb_memory {

    //commit
    const IFBMemoryArenaHandle
    arena_commit(
        const IFBMemoryHandle memory_handle,
        const ifb_u32         arena_size_minimum);

    //reset
    const ifb_b8  arena_reset          (const IFBMemoryArenaHandle arena_handle);

    //pointers
    const ifb_ptr arena_get_pointer    (const IFBMemoryArenaHandle arena_handle, const ifb_u32 offset);

    //size
    const ifb_u32 arena_get_page_count (const IFBMemoryArenaHandle arena_handle);
    const ifb_u32 arena_get_page_start (const IFBMemoryArenaHandle arena_handle);    
    const ifb_u32 arena_get_size_total (const IFBMemoryArenaHandle arena_handle);    
};

/**********************************************************************************/
/* ARENA - LINEAR                                                                 */
/**********************************************************************************/

namespace ifb_memory {

    //commit
    const IFBMemoryLinearArenaHandle
    linear_arena_commit(
        const IFBMemoryHandle memory_handle,
        const ifb_u32         arena_size_minimum);

    //save point
    const ifb_ptr linear_arena_save_point_set        (const IFBMemoryLinearArenaHandle linear_arena_handle);
    const ifb_ptr linear_arena_save_point_clear      (const IFBMemoryLinearArenaHandle linear_arena_handle);
    const ifb_ptr linear_arena_save_point_get        (const IFBMemoryLinearArenaHandle linear_arena_handle);
    
    //reset
    const ifb_ptr linear_arena_reset                 (const IFBMemoryLinearArenaHandle linear_arena_handle);
    const ifb_ptr linear_arena_reset_to_save_point   (const IFBMemoryLinearArenaHandle linear_arena_handle);

    //push/pull    
    const ifb_ptr linear_arena_bytes_reserve         (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 size);
    const ifb_ptr linear_arena_bytes_release         (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 size);
    const ifb_ptr linear_arena_bytes_reserve_aligned (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr linear_arena_bytes_release_aligned (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 size, const ifb_u32 alignment);
    
    //size
    const ifb_u32 linear_arena_get_size_total        (const IFBMemoryLinearArenaHandle linear_arena_handle);
    const ifb_u32 linear_arena_get_size_used         (const IFBMemoryLinearArenaHandle linear_arena_handle);
    const ifb_u32 linear_arena_get_size_free         (const IFBMemoryLinearArenaHandle linear_arena_handle);
};

/**********************************************************************************/
/* ARENA - BLOCK                                                                  */
/**********************************************************************************/

namespace ifb_memory {

    const IFBMemoryBlockArena
    block_arena_commit(
        const IFBMemoryHandle memory_handle,
        const ifb_u32         block_size_minimum,
        const ifb_u32         block_count);

    //reset
    const ifb_ptr block_arena_reset                 (const IFBMemoryBlockArenaHandle block_arena_handle);

    //reserve/release
    const ifb_ptr block_arena_block_reserve         (const IFBMemoryBlockArenaHandle block_arena_handle);
    const ifb_b8  block_arena_block_release         (const IFBMemoryBlockArenaHandle block_arena_handle);

    //size/count
    const ifb_u32 block_arena_get_size_total        (const IFBMemoryBlockArenaHandle block_arena_handle);
    const ifb_u32 block_arena_get_block_size        (const IFBMemoryBlockArenaHandle block_arena_handle);
    const ifb_u32 block_arena_get_block_count_total (const IFBMemoryBlockArenaHandle block_arena_handle);
    const ifb_u32 block_arena_get_block_count_used  (const IFBMemoryBlockArenaHandle block_arena_handle);
    const ifb_u32 block_arena_get_block_count_free  (const IFBMemoryBlockArenaHandle block_arena_handle);
};


#endif //IFB_MEMORY_HPP