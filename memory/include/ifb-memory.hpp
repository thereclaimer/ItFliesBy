#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//arena types
enum IFBMemoryArenaType_ {
    IFBMemoryArenaType_Base   = 0,
    IFBMemoryArenaType_Linear = 1,
    IFBMemoryArenaType_Block  = 2
};
typedef IFBU32 IFBMemoryArenaType;

//handles
struct IFBHNDMemory { 
    IFBU32 offset; 
};

struct IFBHNDMemoryReservation : IFBHNDMemory { };
struct IFBHNDMemoryArena       : IFBHNDMemory { };
struct IFBHNDMemoryArenaLinear : IFBHNDMemory { };
struct IFBHNDMemoryArenaBlock  : IFBHNDMemory { };

#define IFB_MEMORY_HANDLE_INVALID 0

#define ifb_memory_macro_handle_valid(handle) handle.offset != 0

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/
 
struct IFBMemorySystemInfo {
    IFBU32 page_size;
    IFBU32 granularity;
};

namespace ifb_memory {

    //create/destroy
    const IFBB8
    context_create(
        const IFBPlatformApi* platform_api,
        const IFBByte*       stack_memory,
        const IFBU32         stack_size);
    
    const IFBB8  context_destroy                   (IFBVoid);

    //system info
    const IFBB8  context_get_system_info           (IFBMemorySystemInfo* system_info);

    //alignment
    const IFBU32 context_align_size_to_page        (const IFBU32 size);
    const IFBU32 context_align_size_to_granularity (const IFBU32 size);
    
    //size
    const IFBU64 context_get_size_from_page_count  (const IFBU32 page_count);
    const IFBU32 context_get_page_count_from_size  (const IFBU64 size);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBMemoryStackInfo {
    IFBU32 size_total;
    IFBU32 size_used;
};

namespace ifb_memory {

    //push
    const IFBU32 stack_push        (const IFBU32 size, const IFBU32 alignment = 0);

    //pointers/info
    const IFBPtr stack_get_pointer (const IFBU32 offset);
    const IFBB8  stack_get_info    (IFBMemoryStackInfo* stack_info_ptr);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBMemoryReservationInfo {
    IFBU32 page_count_total;
    IFBU32 page_count_committed;
    IFBU32 size_total;
    IFBU32 size_committed;
    IFBU32 arena_count;
};

namespace ifb_memory {

    //reserve/release
    const IFBHNDMemoryReservation reserve_memory (const IFBU64                    size_minimum);
    const IFBB8                     release_memory (const IFBHNDMemoryReservation reservation_handle);

    //arena commit
    const IFBHNDMemoryArena       reservation_commit_arena_unmanaged (const IFBHNDMemoryReservation reservation_handle, const IFBU32 arena_size_minimum);
    const IFBHNDMemoryArenaLinear reservation_commit_arena_linear    (const IFBHNDMemoryReservation reservation_handle, const IFBU32 arena_size_minimum);
    const IFBHNDMemoryArenaBlock  reservation_commit_arena_block     (const IFBHNDMemoryReservation reservation_handle, const IFBU32 block_size_minimum, const IFBU32 block_count);

    //info
    const IFBB8
    reservation_get_info(
        const IFBHNDMemoryReservation reservation_handle,
              IFBMemoryReservationInfo*  reservation_info_ptr);
};

/**********************************************************************************/
/* ARENA - BASE                                                                   */
/**********************************************************************************/

struct IFBMemoryArenaInfo {
    IFBHNDMemoryReservation reservation_handle;
    IFBHNDMemoryArena       arena_handle;
    IFBU32                    page_start;
    IFBU32                    page_count;
    IFBU32                    size_total;
};

namespace ifb_memory {

    //pointers
    const IFBPtr arena_get_pointer (const IFBHNDMemoryArena arena_handle, const IFBU32 offset);
    const IFBB8  arena_get_info    (const IFBHNDMemoryArena arena_handle, IFBMemoryArenaInfo* arena_info_ptr);
};

/**********************************************************************************/
/* ARENA - LINEAR                                                                 */
/**********************************************************************************/

struct IFBMemoryArenaLinearInfo {
    IFBHNDMemoryReservation reservation_handle;
    IFBHNDMemoryArenaLinear linear_arena_handle;
    IFBU32                    page_start;
    IFBU32                    page_count;
    IFBU32                    size_total;
    IFBU32                    position;
    IFBU32                    save_point;
};

namespace ifb_memory {

    //save point
    IFBVoid      linear_arena_save_point_set            (const IFBHNDMemoryArenaLinear linear_arena_handle);
    IFBVoid      linear_arena_save_point_clear          (const IFBHNDMemoryArenaLinear linear_arena_handle);
    
    //reset
    IFBVoid      linear_arena_reset_to_start            (const IFBHNDMemoryArenaLinear linear_arena_handle);
    IFBVoid      linear_arena_reset_to_save_point       (const IFBHNDMemoryArenaLinear linear_arena_handle);

    //reserve/release    
    const IFBPtr linear_arena_reserve_bytes_absolute    (const IFBHNDMemoryArenaLinear linear_arena_handle, const IFBU32 size,  const IFBU32  alignment = 0);
    const IFBU32 linear_arena_reserve_bytes_relative    (const IFBHNDMemoryArenaLinear linear_arena_handle, const IFBU32 size,  const IFBU32  alignment = 0);
    const IFBU32 linear_arena_reserve_bytes_absolute    (const IFBHNDMemoryArenaLinear linear_arena_handle, const IFBU32 count, const IFBU32* size_array, IFBPtr* pointer_array);
    const IFBU32 linear_arena_reserve_bytes_relative    (const IFBHNDMemoryArenaLinear linear_arena_handle, const IFBU32 count, const IFBU32* size_array, IFBU32* offset_array);
    const IFBB8  linear_arena_release_bytes             (const IFBHNDMemoryArenaLinear linear_arena_handle, const IFBU32 size,  const IFBU32  alignment = 0);

    //pointers
    const IFBPtr linear_arena_get_pointer_at_offset     (const IFBHNDMemoryArenaLinear linear_arena_handle, const IFBU32 offset);
    const IFBPtr linear_arena_get_pointer_at_position   (const IFBHNDMemoryArenaLinear linear_arena_handle);
    const IFBPtr linear_arena_get_pointer_at_save_point (const IFBHNDMemoryArenaLinear linear_arena_handle);
    const IFBPtr linear_arena_get_pointer_at_start      (const IFBHNDMemoryArenaLinear linear_arena_handle);

    //info
    const IFBB8  linear_arena_get_info                  (const IFBHNDMemoryArenaLinear linear_arena_handle, IFBMemoryArenaLinearInfo* linear_arena_info_ptr);
    const IFBB8  linear_arena_offset_valid              (const IFBHNDMemoryArenaLinear linear_arena_handle, const IFBU32 offset);
};

/**********************************************************************************/
/* ARENA - BLOCK                                                                  */
/**********************************************************************************/

struct IFBMemoryArenaBlockInfo {
    IFBHNDMemoryReservation reservation_handle;
    IFBHNDMemoryArenaBlock  block_arena_handle;
    IFBU32                    page_start;
    IFBU32                    page_count;
    IFBU32                    size_total;
    IFBU32                    block_size;
    IFBU32                    block_count_total;
    IFBU32                    block_count_free;
};

namespace ifb_memory {

    IFBVoid      block_arena_reset               (const IFBHNDMemoryArenaBlock block_arena_handle);

    //reserve/release
    const IFBB8  block_arena_block_reserve       (const IFBHNDMemoryArenaBlock block_arena_handle, IFBU32&      block_index_ref);
    const IFBB8  block_arena_block_reserve_index (const IFBHNDMemoryArenaBlock block_arena_handle, const IFBU32 block_index);
    const IFBB8  block_arena_block_release       (const IFBHNDMemoryArenaBlock block_arena_handle, const IFBU32 block_index);
    const IFBB8  block_arena_block_is_free       (const IFBHNDMemoryArenaBlock block_arena_handle, const IFBU32 block_index);

    //pointers
    const IFBPtr block_get_pointer               (const IFBHNDMemoryArenaBlock block_arena_handle, const IFBU32 block_index, const IFBU32 offset = 0);

    //size/count
    const IFBB8  block_arena_get_info            (const IFBHNDMemoryArenaBlock block_arena_handle, IFBMemoryArenaBlockInfo* block_arena_info);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_memory_macro_stack_push_type(type)                                          ifb_memory::stack_push(sizeof(type))
#define ifb_memory_macro_stack_push_array(type,count)                                   ifb_memory::stack_push(sizeof(type) * count)
#define ifb_memory_macro_stack_push_struct(struct)                                      ifb_memory::stack_push(sizeof(struct), alignof(struct))
#define ifb_memory_macro_stack_get_type_pointer(offset,type)                     (type*)ifb_memory::stack_get_pointer(offset)      

#define ifb_memory_macro_linear_arena_reserve_type_absolute(arena,type)          (type*)ifb_memory::linear_arena_reserve_bytes_absolute(arena, sizeof(type))
#define ifb_memory_macro_linear_arena_reserve_type_relative(arena,type)          (type*)ifb_memory::linear_arena_reserve_bytes_relative(arena, sizeof(type))
#define ifb_memory_macro_linear_arena_reserve_array_absolute(arena,type,count)   (type*)ifb_memory::linear_arena_reserve_bytes_absolute(arena, sizeof(type) * count)
#define ifb_memory_macro_linear_arena_reserve_array_relative(arena,type,count)   (type*)ifb_memory::linear_arena_reserve_bytes_relative(arena, sizeof(type) * count)
#define ifb_memory_macro_linear_arena_reserve_struct_absolute(arena,struct)    (struct*)ifb_memory::linear_arena_reserve_bytes_absolute(arena, sizeof(struct), alignof(struct))
#define ifb_memory_macro_linear_arena_reserve_struct_relative(arena,struct)    (struct*)ifb_memory::linear_arena_reserve_bytes_relative(arena, sizeof(struct), alignof(struct))

#define ifb_memory_macro_linear_arena_release_type(arena,type)                          ifb_memory::linear_arena_release_bytes(arena, sizeof(type))
#define ifb_memory_macro_linear_arena_release_type(arena,type)                          ifb_memory::linear_arena_release_bytes(arena, sizeof(type))
#define ifb_memory_macro_linear_arena_release_array(arena,type,count)                   ifb_memory::linear_arena_release_bytes(arena, sizeof(type) * count)
#define ifb_memory_macro_linear_arena_release_array(arena,type,count)                   ifb_memory::linear_arena_release_bytes(arena, sizeof(type) * count)
#define ifb_memory_macro_linear_arena_release_struct(arena,struct)                      ifb_memory::linear_arena_release_bytes(arena, sizeof(struct), alignof(struct))
#define ifb_memory_macro_linear_arena_release_struct(arena,struct)                      ifb_memory::linear_arena_release_bytes(arena, sizeof(struct), alignof(struct))

#endif //IFB_MEMORY_HPP