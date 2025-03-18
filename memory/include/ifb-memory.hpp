#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/


struct IFBHNDAllocator : IFBHND32 {
    IFBHNDArena arena;
};

struct IFBHNDBlockAllocator  : IFBHNDAllocator { };
struct IFBHNDLinearAllocator : IFBHNDAllocator { };

#define ifb_memory_macro_handle_valid(handle) handle.pointer != 0

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/
 
struct IFBMemoryContextInfo {
    IFBU64 size_platform_memory_reserved;
    IFBU64 size_platform_memory_committed;
    IFBU32 size_stack_total;
    IFBU32 size_stack_used;
    IFBU32 system_page_size;
    IFBU32 system_granularity;
    IFBU32 count_reservations;
    IFBU32 count_arenas;
};

namespace ifb_memory {

    //create/destroy
    const IFBB8 
    context_create(
        const IFBSystemMemoryInfo* system_memory_info,
        const IFBByte*             stack_memory,
        const IFBU32               stack_size);
    
    const IFBB8  context_destroy (IFBVoid);

    //info
    const IFBB8  context_get_info (IFBMemoryContextInfo* system_info);

    //alignment
    const IFBU32 context_align_size_to_page        (const IFBU32 size);
    const IFBU32 context_align_size_to_granularity (const IFBU32 size);
    
    //size
    const IFBU64 context_get_size_from_page_count (const IFBU32 page_count);
    const IFBU32 context_get_page_count_from_size (const IFBU64 size);

    //stack
    const IFBU32 context_stack_commit_relative (const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr context_stack_commit_absolute (const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr context_stack_get_pointer     (const IFBU32 offset);

    //reservations
    const IFBHNDReservation context_reserve_platform_memory (const IFBU64            size_minimum);
    const IFBB8             context_release_platform_memory (const IFBHNDReservation reservation_handle);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBReservationInfo {
    IFBU32 page_count_total;
    IFBU32 page_count_committed;
    IFBU64 size_total;
    IFBU64 size_committed;
};

namespace ifb_memory {

    //arena commit
    const IFBHNDArena
    reservation_commit_arena(
        const IFBHNDReservation reservation_handle,
        const IFBU32            size_minimum);

    //info
    const IFBB8
    reservation_get_info(
        const IFBHNDReservation   reservation_handle,
              IFBReservationInfo* reservation_info_ptr);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

struct IFBArenaInfo {
    IFBHNDReservation handle_reservation;
    IFBHNDArena       handle_arena;
    IFBU32            size_total;
    IFBU32            size_reserved;
    IFBU32            size_committed;
};

namespace ifb_memory {

    //reset
    IFBVoid      arena_reset_all                (const IFBHNDArena arena_handle);
    IFBVoid      arena_reset_committed_space    (const IFBHNDArena arena_handle);
    IFBVoid      arena_reset_reserved_space     (const IFBHNDArena arena_handle);
    
    //pointers
    const IFBPtr  arena_get_pointer             (const IFBHNDArena arena_handle, const IFBU32  offset);
    const IFBB8   arena_get_info                (const IFBHNDArena arena_handle, IFBArenaInfo* arena_info_ptr);
    const IFBAddr arena_get_start               (const IFBHNDArena arena_handle);

    //reserve/release    
    const IFBPtr   arena_reserve_bytes_absolute (const IFBHNDArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
    const IFBU32   arena_reserve_bytes_relative (const IFBHNDArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
    const IFBB8    arena_release_bytes          (const IFBHNDArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
    
    //commit
    const IFBPtr   arena_commit_bytes_absolute  (const IFBHNDArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
    const IFBU32   arena_commit_bytes_relative  (const IFBHNDArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);

    //strings
    const IFBChar* arena_commit_string          (const IFBHNDArena arena_handle, const IFBChar* c_string, const IFBU32 max_length);
};

/**********************************************************************************/
/* LINEAR ALLOCATOR                                                               */
/**********************************************************************************/

struct IFBLinearAllocatorInfo {
    IFBHNDReservation     handle_reservation;
    IFBHNDLinearAllocator handle_allocator;
    IFBU32                page_start;
    IFBU32                page_count;
    IFBU32                size_total;
    IFBU32                position;
    IFBU32                save_point;
};

namespace ifb_memory {

    //save point
    IFBVoid      linear_allocator_save_point_set            (const IFBHNDLinearAllocator linear_allocator_handle);
    IFBVoid      linear_allocator_save_point_clear          (const IFBHNDLinearAllocator linear_allocator_handle);
    
    //reset
    IFBVoid      linear_allocator_reset_to_start            (const IFBHNDLinearAllocator linear_allocator_handle);
    IFBVoid      linear_allocator_reset_to_save_point       (const IFBHNDLinearAllocator linear_allocator_handle);

    //reserve/release    
    const IFBPtr linear_allocator_reserve_bytes_absolute    (const IFBHNDLinearAllocator linear_allocator_handle, const IFBU32 size,  const IFBU32  alignment = 0);
    const IFBU32 linear_allocator_reserve_bytes_relative    (const IFBHNDLinearAllocator linear_allocator_handle, const IFBU32 size,  const IFBU32  alignment = 0);
    const IFBB8  linear_allocator_release_bytes             (const IFBHNDLinearAllocator linear_allocator_handle, const IFBU32 size,  const IFBU32  alignment = 0);

    //pointers
    const IFBPtr linear_allocator_get_pointer_at_offset     (const IFBHNDLinearAllocator linear_allocator_handle, const IFBU32 offset);
    const IFBPtr linear_allocator_get_pointer_at_position   (const IFBHNDLinearAllocator linear_allocator_handle);
    const IFBPtr linear_allocator_get_pointer_at_save_point (const IFBHNDLinearAllocator linear_allocator_handle);
    const IFBPtr linear_allocator_get_pointer_at_start      (const IFBHNDLinearAllocator linear_allocator_handle);

    //info
    const IFBB8  linear_allocator_get_info                  (const IFBHNDLinearAllocator linear_allocator_handle, IFBLinearAllocatorInfo* linear_allocator_info_ptr);
};

/**********************************************************************************/
/* ARENA - BLOCK                                                                  */
/**********************************************************************************/

struct IFBBlockAllocatorInfo {
    IFBHNDReservation    handle_reservation;
    IFBHNDBlockAllocator handle_allocator;
    IFBU32               block_size;
    IFBU32               block_count_total;
    IFBU32               block_count_free;
};

namespace ifb_memory {

    //reset
    IFBVoid      block_allocator_reset                   (const IFBHNDBlockAllocator block_allocator_handle);

    //reserve/release
    const IFBU32 block_allocator_reserve_block_relative  (const IFBHNDBlockAllocator block_allocator_handle);
    const IFBPtr block_allocator_reserve_block_absolute  (const IFBHNDBlockAllocator block_allocator_handle);
    const IFBB8  block_allocator_release_block_relative  (const IFBHNDBlockAllocator block_allocator_handle, const IFBPtr block_memory);
    const IFBB8  block_allocator_release_block_absolute  (const IFBHNDBlockAllocator block_allocator_handle, const IFBPtr block_offset);

    //info
    const IFBB8  block_allocator_get_info                (const IFBHNDBlockAllocator block_allocator_handle, IFBBlockAllocatorInfo* block_allocator_info);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_memory_macro_commit_struct_to_arena_absolute(arena_handle,struct_type) (struct_type*)ifb_memory::arena_commit_bytes_absolute(arena_handle,sizeof(struct_type),alignof(struct_type))
#define ifb_memory_macro_commit_struct_to_arena_relative(arena_handle,struct_type)               ifb_memory::arena_commit_bytes_relative(arena_handle,sizeof(struct_type),alignof(struct_type))

#define ifb_memory_macro_get_pointer_from_arena(arena_handle,offset,type)                 (type*)ifb_memory::arena_get_pointer(arena_handle,offset)

#endif //IFB_MEMORY_HPP