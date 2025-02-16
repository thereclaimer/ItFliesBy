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
typedef ifb_u32 IFBMemoryArenaType;

//handles
struct IFBMemoryHandle { ifb_u32 offset; };
struct IFBMemoryReservationHandle : IFBMemoryHandle { };
struct IFBMemoryArenaHandle       : IFBMemoryHandle { };
struct IFBMemoryLinearArenaHandle : IFBMemoryHandle { };
struct IFBMemoryBlockArenaHandle  : IFBMemoryHandle { };

#define IFB_MEMORY_HANDLE_INVALID 0

#define ifb_memory_macro_handle_valid(handle) handle.offset != 0

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/
 
struct IFBMemorySystemInfo {
    ifb_u32 page_size;
    ifb_u32 granularity;
};

namespace ifb_memory {

    //create/destroy
    const ifb_b8
    context_create(
        const IFBPlatformApi* platform_api,
        const ifb_byte*       stack_memory,
        const ifb_u32         stack_size);
    
    const ifb_b8 context_destroy                   (ifb_void);

    //system info
    const ifb_b8  context_get_system_info           (IFBMemorySystemInfo* system_info);

    //alignment
    const ifb_u32 context_align_size_to_page        (const ifb_u32 size);
    const ifb_u32 context_align_size_to_granularity (const ifb_u32 size);
    
    //size
    const ifb_u64 context_get_size_from_page_count  (const ifb_u32 page_count);
    const ifb_u32 context_get_page_count_from_size  (const ifb_u64 size);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBMemoryStackInfo {
    ifb_u32 size_total;
    ifb_u32 size_used;
};

namespace ifb_memory {

    //push
    const ifb_u32 stack_push        (const ifb_u32 size, const ifb_u32 alignment = 0);

    //pointers/info
    const ifb_ptr stack_get_pointer (const ifb_u32 offset);
    const ifb_b8  stack_get_info    (IFBMemoryStackInfo* stack_info_ptr);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBMemoryReservationInfo {
    ifb_u32 page_count_total;
    ifb_u32 page_count_committed;
    ifb_u32 size_total;
    ifb_u32 size_committed;
    ifb_u32 arena_count;
};

namespace ifb_memory {

    //reserve/release
    const IFBMemoryReservationHandle reserve_memory (const ifb_u64                    size_minimum);
    const ifb_b8                     release_memory (const IFBMemoryReservationHandle reservation_handle);

    //arena commit
    const IFBMemoryArenaHandle       reservation_commit_arena        (const IFBMemoryReservationHandle reservation_handle, const ifb_u32 arena_size_minimum);
    const IFBMemoryLinearArenaHandle reservation_commit_linear_arena (const IFBMemoryReservationHandle reservation_handle, const ifb_u32 arena_size_minimum);
    const IFBMemoryBlockArenaHandle  reservation_commit_block_arena  (const IFBMemoryReservationHandle reservation_handle, const ifb_u32 block_size_minimum, const ifb_u32 block_count);

    //info
    const ifb_b8
    reservation_get_info(
        const IFBMemoryReservationHandle reservation_handle,
              IFBMemoryReservationInfo*  reservation_info_ptr);
};

/**********************************************************************************/
/* ARENA - BASE                                                                   */
/**********************************************************************************/

struct IFBMemoryArenaInfo {
    IFBMemoryReservationHandle reservation_handle;
    IFBMemoryArenaHandle       arena_handle;
    ifb_u32                    page_start;
    ifb_u32                    page_count;
    ifb_u32                    size_total;
};

namespace ifb_memory {

    //pointers
    const ifb_ptr arena_get_pointer (const IFBMemoryArenaHandle arena_handle, const ifb_u32 offset);
    const ifb_b8  arena_get_info    (const IFBMemoryArenaHandle arena_handle, IFBMemoryArenaInfo* arena_info_ptr);
};

/**********************************************************************************/
/* ARENA - LINEAR                                                                 */
/**********************************************************************************/

struct IFBMemoryLinearArenaInfo {
    IFBMemoryReservationHandle reservation_handle;
    IFBMemoryLinearArenaHandle linear_arena_handle;
    ifb_u32                    page_start;
    ifb_u32                    page_count;
    ifb_u32                    size_total;
    ifb_u32                    position;
    ifb_u32                    save_point;
};

namespace ifb_memory {

    //save point
    ifb_void      linear_arena_save_point_set            (const IFBMemoryLinearArenaHandle linear_arena_handle);
    ifb_void      linear_arena_save_point_clear          (const IFBMemoryLinearArenaHandle linear_arena_handle);
    
    //reset
    ifb_void      linear_arena_reset_to_start            (const IFBMemoryLinearArenaHandle linear_arena_handle);
    ifb_void      linear_arena_reset_to_save_point       (const IFBMemoryLinearArenaHandle linear_arena_handle);

    //reserve/release    
    const ifb_ptr linear_arena_reserve_bytes_absolute    (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 size, const ifb_u32 alignment = 0);
    const ifb_u32 linear_arena_reserve_bytes_relative    (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 size, const ifb_u32 alignment = 0);
    const ifb_b8  linear_arena_release_bytes             (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 size, const ifb_u32 alignment = 0);

    //pointers
    const ifb_ptr linear_arena_get_pointer_at_offset     (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 offset);
    const ifb_ptr linear_arena_get_pointer_at_position   (const IFBMemoryLinearArenaHandle linear_arena_handle);
    const ifb_ptr linear_arena_get_pointer_at_save_point (const IFBMemoryLinearArenaHandle linear_arena_handle);
    const ifb_ptr linear_arena_get_pointer_at_start      (const IFBMemoryLinearArenaHandle linear_arena_handle);

    //info
    const ifb_b8  linear_arena_get_info                  (const IFBMemoryLinearArenaHandle linear_arena_handle, IFBMemoryLinearArenaInfo* linear_arena_info_ptr);
};

/**********************************************************************************/
/* ARENA - BLOCK                                                                  */
/**********************************************************************************/

struct IFBMemoryBlockArenaInfo {
    IFBMemoryReservationHandle reservation_handle;
    IFBMemoryBlockArenaHandle  block_arena_handle;
    ifb_u32                    page_start;
    ifb_u32                    page_count;
    ifb_u32                    size_total;
    ifb_u32                    block_size;
    ifb_u32                    block_count_total;
    ifb_u32                    block_count_free;
};

namespace ifb_memory {

    ifb_void      block_arena_reset               (const IFBMemoryBlockArenaHandle block_arena_handle);

    //reserve/release
    const ifb_b8  block_arena_block_reserve       (const IFBMemoryBlockArenaHandle block_arena_handle, ifb_u32&      block_index_ref);
    const ifb_b8  block_arena_block_reserve_index (const IFBMemoryBlockArenaHandle block_arena_handle, const ifb_u32 block_index);
    const ifb_b8  block_arena_block_release       (const IFBMemoryBlockArenaHandle block_arena_handle, const ifb_u32 block_index);
    const ifb_b8  block_arena_block_is_free       (const IFBMemoryBlockArenaHandle block_arena_handle, const ifb_u32 block_index);

    //pointers
    const ifb_ptr block_get_pointer               (const IFBMemoryBlockArenaHandle block_arena_handle, const ifb_u32 block_index, const ifb_u32 offset = 0);

    //size/count
    const ifb_b8  block_arena_get_info            (const IFBMemoryBlockArenaHandle block_arena_handle, IFBMemoryBlockArenaInfo* block_arena_info);
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