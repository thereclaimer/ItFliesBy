#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBHNDReservation     : IFBHND { };
struct IFBHNDArena           : IFBHND { };

struct IFBHNDAllocator : IFBHND {
    IFBHNDArena arena;
};

struct IFBHNDBlockAllocator  : IFBHNDAllocator { };
struct IFBHNDLinearAllocator : IFBHNDAllocator { };

#define ifb_memory_macro_handle_valid(handle) handle.offset != 0

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
    const IFBB8 context_create  (const IFBByte* stack_memory, const IFBU32 stack_size);
    const IFBB8 context_destroy (IFBVoid);

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
    const IFBHNDReservation context_reserve_platform_memory (const IFBU32            size_minimum);
    const IFBB8             context_release_platform_memory (const IFBHNDReservation reservation_handle);

    //pointers
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBReservationInfo {
    IFBU32 page_count_total;
    IFBU32 page_count_committed;
    IFBU32 size_total;
    IFBU32 size_committed;
    IFBU32 arena_count;
};

namespace ifb_memory {


    //arena commit
    const IFBHNDArena reservation_commit_arena(const IFBU32 size_minimum);

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
    IFBU32            page_start;
    IFBU32            page_count;
    IFBU32            size_total;
    IFBU32            size_used;
};

namespace ifb_memory {

    //reset
    const IFBB8  arena_reset                  (const IFBHNDArena arena_handle);
    
    //pointers
    const IFBPtr arena_get_pointer            (const IFBHNDArena arena_handle, const IFBU32        offset);
    const IFBB8  arena_get_info               (const IFBHNDArena arena_handle, IFBMemoryArenaInfo* arena_info_ptr);

    //reserve/release    
    const IFBPtr arena_reserve_bytes_absolute (const IFBHNDArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
    const IFBU32 arena_reserve_bytes_relative (const IFBHNDArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
    const IFBB8  arena_release_bytes          (const IFBHNDArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);

    //allocators
    const IFBHNDLinearAllocator arena_commit_allocator_linear (const ifb_u32 size);
    const IFBHNDBlockAllocator  arena_commit_allocator_block  (const ifb_u32 block_size, const ifb_u32 block_count);

};

/**********************************************************************************/
/* ARENA - LINEAR                                                                 */
/**********************************************************************************/

struct IFBMemoryArenaLinearInfo {
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
    const IFBB8  linear_allocator_get_info                  (const IFBHNDLinearAllocator linear_allocator_handle, IFBMemoryArenaLinearInfo* linear_allocator_info_ptr);
};

/**********************************************************************************/
/* ARENA - BLOCK                                                                  */
/**********************************************************************************/

struct IFBMemoryArenaBlockInfo {
    IFBHNDReservation    handle_reservation;
    IFBHNDBlockAllocator handle_allocator;
    IFBU32               block_size;
    IFBU32               block_count_total;
    IFBU32               block_count_free;
};

namespace ifb_memory {

    //reset
    IFBVoid      block_allocator_reset          (const IFBHNDBlockAllocator block_allocator_handle);

    //reserve/release
    const IFBU32 block_allocator_reserve_block_relative  (const IFBHNDBlockAllocator block_allocator_handle);
    const IFBPtr block_allocator_reserve_block_absolute  (const IFBHNDBlockAllocator block_allocator_handle);
    const IFBB8  block_allocator_release_block_relative  (const IFBHNDBlockAllocator block_allocator_handle, const IFBPtr block_memory);
    const IFBB8  block_allocator_release_block_absolute  (const IFBHNDBlockAllocator block_allocator_handle, const IFBPtr block_offset);

    //info
    const IFBB8  block_allocator_get_info       (const IFBHNDBlockAllocator block_allocator_handle, IFBMemoryArenaBlockInfo* block_allocator_info);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_memory_macro_stack_push_type(type)                                          ifb_memory::stack_push(sizeof(type))
#define ifb_memory_macro_stack_push_array(type,count)                                   ifb_memory::stack_push(sizeof(type) * count)
#define ifb_memory_macro_stack_push_struct(struct)                                      ifb_memory::stack_push(sizeof(struct), alignof(struct))
#define ifb_memory_macro_stack_get_type_pointer(offset,type)                     (type*)ifb_memory::stack_get_pointer(offset)      

#define ifb_memory_macro_linear_allocator_reserve_type_absolute(arena,type)          (type*)ifb_memory::linear_allocator_reserve_bytes_absolute(arena, sizeof(type))
#define ifb_memory_macro_linear_allocator_reserve_type_relative(arena,type)          (type*)ifb_memory::linear_allocator_reserve_bytes_relative(arena, sizeof(type))
#define ifb_memory_macro_linear_allocator_reserve_array_absolute(arena,type,count)   (type*)ifb_memory::linear_allocator_reserve_bytes_absolute(arena, sizeof(type) * count)
#define ifb_memory_macro_linear_allocator_reserve_array_relative(arena,type,count)   (type*)ifb_memory::linear_allocator_reserve_bytes_relative(arena, sizeof(type) * count)
#define ifb_memory_macro_linear_allocator_reserve_struct_absolute(arena,struct)    (struct*)ifb_memory::linear_allocator_reserve_bytes_absolute(arena, sizeof(struct), alignof(struct))
#define ifb_memory_macro_linear_allocator_reserve_struct_relative(arena,struct)    (struct*)ifb_memory::linear_allocator_reserve_bytes_relative(arena, sizeof(struct), alignof(struct))

#define ifb_memory_macro_linear_allocator_release_type(arena,type)                          ifb_memory::linear_allocator_release_bytes(arena, sizeof(type))
#define ifb_memory_macro_linear_allocator_release_type(arena,type)                          ifb_memory::linear_allocator_release_bytes(arena, sizeof(type))
#define ifb_memory_macro_linear_allocator_release_array(arena,type,count)                   ifb_memory::linear_allocator_release_bytes(arena, sizeof(type) * count)
#define ifb_memory_macro_linear_allocator_release_array(arena,type,count)                   ifb_memory::linear_allocator_release_bytes(arena, sizeof(type) * count)
#define ifb_memory_macro_linear_allocator_release_struct(arena,struct)                      ifb_memory::linear_allocator_release_bytes(arena, sizeof(struct), alignof(struct))
#define ifb_memory_macro_linear_allocator_release_struct(arena,struct)                      ifb_memory::linear_allocator_release_bytes(arena, sizeof(struct), alignof(struct))

#endif //IFB_MEMORY_HPP