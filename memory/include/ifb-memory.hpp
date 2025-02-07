#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

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
struct IFBMemoryBlockArena;
struct IFBMemoryBlock;

typedef ifb_u32 IFBMemoryArenaType;

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_memory {

    IFBMemory*
    create(
        const IFBPlatformApi& platform_api_ref,
        const ifb_byte*       stack_memory,
        const ifb_u32         stack_size);
    
    const ifb_b8 destroy(IFBMemory* memory_ptr);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_memory {

    //push absolute
    const ifb_ptr stack_push                  (IFBMemory* memory_ptr, const ifb_u32 size);
    const ifb_ptr stack_push_aligned          (IFBMemory* memory_ptr, const ifb_u32 size, const ifb_u32 alignment);

    //push offset
    const ifb_u32 stack_push_offset           (IFBMemory* memory_ptr, const ifb_u32 size);
    const ifb_u32 stack_push_offset_aligned   (IFBMemory* memory_ptr, const ifb_u32 size, const ifb_u32 alignment);
    
    //push relative
    const ifb_u32 stack_push_relative         (IFBMemory* memory_ptr, const ifb_ptr reference, const ifb_u32 size);
    const ifb_u32 stack_push_relative_aligned (IFBMemory* memory_ptr, const ifb_ptr reference, const ifb_u32 size, const ifb_u32 alignment);

    //pointers
    const ifb_ptr stack_get_pointer           (const IFBMemory* memory_ptr, const ifb_u32 stack_position);
    const ifb_ptr stack_get_pointer_relative  (const IFBMemory* memory_ptr, const ifb_u32 reference, const ifb_u32 offset);

    //size
    const ifb_u32 stack_get_size_total        (const IFBMemory* memory_ptr);
    const ifb_u32 stack_get_size_free         (const IFBMemory* memory_ptr);
    const ifb_u32 stack_get_size_used         (const IFBMemory* memory_ptr);
};

#define ifb_memory_macro_stack_push_type(memory_ptr,type)                          (type*)ifb_memory::stack_push(memory_ptr, sizeof(struct))
#define ifb_memory_macro_stack_push_type_relative(memory_ptr,reference,type)              ifb_memory::stack_push_relative(memory_ptr, reference, sizeof(struct))

#define ifb_memory_macro_stack_push_struct(memory_ptr,struct)                    (struct*)ifb_memory::stack_push_aligned(memory_ptr, sizeof(struct), alignof(struct))
#define ifb_memory_macro_stack_push_struct_relative(memory_ptr,reference,struct)          ifb_memory::stack_push_relative_aligned(memory_ptr, reference, sizeof(struct), alignof(struct))

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

namespace ifb_memory {

    //reserve/release
    const ifb_b8  reserve                               (IFBMemory* memory_ptr, const ifb_u64 reservation_size_minimum);
    const ifb_b8  release                               (IFBMemory* memory_ptr);

    //alignment
    const ifb_u32 reservation_size_align_to_page        (const IFBMemory* memory_ptr, const ifb_u32 size);    
    const ifb_u32 reservation_size_align_to_granularity (const IFBMemory* memory_ptr, const ifb_u32 size);
    
    //pages
    const ifb_u32 reservation_get_page_size             (const IFBMemory* memory_ptr);
    const ifb_u32 reservation_get_page_count_total      (const IFBMemory* memory_ptr);
    const ifb_u32 reservation_get_page_count_committed  (const IFBMemory* memory_ptr);
    const ifb_u32 reservation_get_page_count_free       (const IFBMemory* memory_ptr);
    const ifb_u32 reservation_get_page_count_from_size  (const IFBMemory* memory_ptr, const ifb_u32 size);

    //size
    const ifb_u64 reservation_get_size_total            (const IFBMemory* memory_ptr);
    const ifb_u64 reservation_get_size_committed        (const IFBMemory* memory_ptr);
};

/**********************************************************************************/
/* ARENA - BASE                                                                   */
/**********************************************************************************/

namespace ifb_memory {

    //commit
    IFBMemoryArena*
    arena_commit(
              IFBMemory* memory_ptr,
        const ifb_u32    arena_size_minimum);

    //reset
    const ifb_b8  arena_reset          (IFBMemoryArena* arena_ptr);

    //pointers
    const ifb_ptr arena_get_pointer    (const IFBMemoryArena* arena_ptr, const ifb_u32 offset);

    //size
    const ifb_u32 arena_get_page_count (const IFBMemoryArena* arena_ptr);
    const ifb_u32 arena_get_page_start (const IFBMemoryArena* arena_ptr);    
    const ifb_u32 arena_get_size_total (const IFBMemoryArena* arena_ptr);    
};

/**********************************************************************************/
/* ARENA - LINEAR                                                                 */
/**********************************************************************************/

namespace ifb_memory {

    //commit
    IFBMemoryLinearArena*
    linear_arena_commit(
              IFBMemory* memory_ptr,
        const ifb_u32    arena_size_minimum);

    //save point
    const ifb_ptr linear_arena_save_point_set        (IFBMemoryLinearArena* linear_arena_ptr);
    const ifb_ptr linear_arena_save_point_clear      (IFBMemoryLinearArena* linear_arena_ptr);
    const ifb_ptr linear_arena_save_point_get        (IFBMemoryLinearArena* linear_arena_ptr);
    
    //reset
    const ifb_ptr linear_arena_reset                 (IFBMemoryLinearArena* linear_arena_handle);
    const ifb_ptr linear_arena_reset_to_save_point   (IFBMemoryLinearArena* linear_arena_handle);

    //push/pull    
    const ifb_ptr linear_arena_bytes_reserve         (IFBMemoryLinearArena* linear_arena_ptr, const ifb_u32 size);
    const ifb_ptr linear_arena_bytes_release         (IFBMemoryLinearArena* linear_arena_ptr, const ifb_u32 size);
    const ifb_ptr linear_arena_bytes_reserve_aligned (IFBMemoryLinearArena* linear_arena_ptr, const ifb_u32 size, const ifb_u32 alignment);
    const ifb_ptr linear_arena_bytes_release_aligned (IFBMemoryLinearArena* linear_arena_ptr, const ifb_u32 size, const ifb_u32 alignment);
    
    //size
    const ifb_u32 linear_arena_get_size_total        (const IFBMemoryLinearArena* linear_arena_ptr);
    const ifb_u32 linear_arena_get_size_used         (const IFBMemoryLinearArena* linear_arena_ptr);
    const ifb_u32 linear_arena_get_size_free         (const IFBMemoryLinearArena* linear_arena_ptr);
};

/**********************************************************************************/
/* ARENA - BLOCK                                                                  */
/**********************************************************************************/

namespace ifb_memory {

    IFBMemoryBlockArena*
    block_arena_commit(
              IFBMemory* memory_ptr,
        const ifb_u32    block_size_minimum,
        const ifb_u32    block_count);

    //reset
    ifb_void      block_arena_reset                 (IFBMemoryBlockArena* block_arena_ptr);

    //reserve/release
    const ifb_b8  block_arena_block_reserve         (IFBMemoryBlockArena* block_arena_ptr, ifb_u32&      block_index_ref);
    const ifb_b8  block_arena_block_reserve_index   (IFBMemoryBlockArena* block_arena_ptr, const ifb_u32 block_index);
    const ifb_b8  block_arena_block_release         (IFBMemoryBlockArena* block_arena_ptr, const ifb_u32 block_index);
    const ifb_b8  block_arena_block_is_free         (IFBMemoryBlockArena* block_arena_ptr, const ifb_u32 block_index);

    //pointers
    const ifb_ptr block_get_pointer                 (const IFBMemoryBlockArena* block_arena_ptr, const ifb_u32 block_index, const ifb_u32 offset = 0);

    //size/count
    const ifb_u32 block_arena_get_size_total        (const IFBMemoryBlockArena* block_arena_ptr);
    const ifb_u32 block_arena_get_block_size        (const IFBMemoryBlockArena* block_arena_ptr);
    const ifb_u32 block_arena_get_block_count_total (const IFBMemoryBlockArena* block_arena_ptr);
    const ifb_u32 block_arena_get_block_count_used  (const IFBMemoryBlockArena* block_arena_ptr);
    const ifb_u32 block_arena_get_block_count_free  (const IFBMemoryBlockArena* block_arena_ptr);
};


#endif //IFB_MEMORY_HPP