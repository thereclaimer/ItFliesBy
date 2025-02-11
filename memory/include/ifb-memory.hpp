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
struct IFBMemoryHandle { ifb_u32 stack_position; };
struct IFBMemoryReservationHandle : IFBMemoryHandle { };
struct IFBMemoryArenaHandle       : IFBMemoryHandle { };
struct IFBMemoryLinearArenaHandle : IFBMemoryHandle { };
struct IFBMemoryBlockArenaHandle  : IFBMemoryHandle { };

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBMemorySystemInfo {
    ifb_u32 page_size;
    ifb_u32 granularity;
};

namespace ifb_memory {

    //create/destroy
    inline const ifb_b8 context_create  (const ifb_byte* stack_memory, const ifb_u32 stack_size);
    inline const ifb_b8 context_destroy (ifb_void);

    //system info
    inline const ifb_b8 context_get_system_info (IFBMemorySystemInfo* system_info);
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

struct IFBMemoryStackInfo {
    ifb_u32 size_total;
    ifb_u32 size_used;
    ifb_u32 size_free;
};

namespace ifb_memory {

    //push
    inline const IFBMemoryHandle stack_push (const ifb_u32 size, const ifb_u32 alignment = 0);

    //pointers/info
    inline const ifb_ptr stack_get_pointer  (const IFBMemoryHandle memory_handle);
    inline const ifb_b8  stack_get_info     (IFBMemoryStackInfo* stack_info_ptr);
};

#define ifb_memory_macro_stack_push_type(type)     ifb_memory::stack_push(sizeof(type))
#define ifb_memory_macro_stack_push_struct(struct) ifb_memory::stack_push(sizeof(struct), alignof(struct))

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBMemoryReservationInfo {
    ifb_u32 page_count_total;
    ifb_u32 page_count_used;
    ifb_u32 size_total;
    ifb_u32 size_used;
};

namespace ifb_memory {

    //reserve/release
    inline const IFBMemoryReservationHandle reserve_memory (const ifb_u64                    size_minimum);
    inline const ifb_b8                     release_memory (const IFBMemoryReservationHandle reservation_handle);

    //info
    inline const ifb_b8
    reservation_get_info(
        const IFBMemoryReservationHandle reservation_handle,
              IFBMemoryReservationInfo*  reservation_info_ptr);
};

/**********************************************************************************/
/* ARENA - BASE                                                                   */
/**********************************************************************************/

struct IFBMemoryArenaInfo {
    ifb_u32 page_start;
    ifb_u32 page_count;
    ifb_u32 size_total;
};

namespace ifb_memory {

    //commit
    inline const IFBMemoryArenaHandle
    arena_commit(
        const IFBMemoryReservationHandle reservation_handle,
        const ifb_u32                    arena_size_minimum);

    //pointers
    inline const ifb_ptr arena_get_pointer (const IFBMemoryArenaHandle arena_handle, const ifb_u32 offset);
    inline const ifb_b8  arena_get_info    (const IFBMemoryArenaHandle arena_handle);
};

/**********************************************************************************/
/* ARENA - LINEAR                                                                 */
/**********************************************************************************/

struct IFBMemoryLinearArenaInfo : IFBMemoryArenaInfo {
    ifb_u32 position;
    ifb_u32 save_point;
};

namespace ifb_memory {

    //commit
    inline const IFBMemoryLinearArenaHandle
    linear_arena_commit(
        const IFBMemoryReservationHandle reservation_handle,
        const ifb_u32                    arena_size_minimum);

    //save point
    inline const ifb_ptr linear_arena_set_save_point      (const IFBMemoryLinearArenaHandle linear_arena_handle);
    inline const ifb_ptr linear_arena_clear_save_point    (const IFBMemoryLinearArenaHandle linear_arena_handle);
    
    //reset
    inline const ifb_ptr linear_arena_reset               (const IFBMemoryLinearArenaHandle linear_arena_handle);
    inline const ifb_ptr linear_arena_reset_to_save_point (const IFBMemoryLinearArenaHandle linear_arena_handle);

    //reserve/release    
    inline const ifb_ptr linear_arena_reserve_bytes       (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 size, const ifb_u32 alignment = 0);
    inline const ifb_ptr linear_arena_release_bytes       (const IFBMemoryLinearArenaHandle linear_arena_handle, const ifb_u32 size, const ifb_u32 alignment = 0);
    
    //info
    inline const ifb_b8  linear_arena_get_info            (const IFBMemoryLinearArenaHandle linear_arena_handle, IFBMemoryLinearArenaInfo* linear_arena_info_ptr);
};

/**********************************************************************************/
/* ARENA - BLOCK                                                                  */
/**********************************************************************************/

struct IFBMemoryBlockArenaInfo : IFBMemoryArenaInfo {
    ifb_u32 block_size;
    ifb_u32 block_count_total;
    ifb_u32 block_count_free;
};

namespace ifb_memory {

    inline const IFBMemoryBlockArenaHandle
    block_arena_commit(
        const ifb_u32 block_size_minimum,
        const ifb_u32 block_count);

    //reset
    inline ifb_void      block_arena_reset               (const IFBMemoryBlockArenaHandle block_arena_handle);

    //reserve/release
    inline const ifb_b8  block_arena_block_reserve       (const IFBMemoryBlockArenaHandle block_arena_handle, ifb_u32&      block_index_ref);
    inline const ifb_b8  block_arena_block_reserve_index (const IFBMemoryBlockArenaHandle block_arena_handle, const ifb_u32 block_index);
    inline const ifb_b8  block_arena_block_release       (const IFBMemoryBlockArenaHandle block_arena_handle, const ifb_u32 block_index);
    inline const ifb_b8  block_arena_block_is_free       (const IFBMemoryBlockArenaHandle block_arena_handle, const ifb_u32 block_index);

    //pointers
    inline const ifb_ptr block_get_pointer               (const IFBMemoryBlockArenaHandle block_arena_handle, const ifb_u32 block_index, const ifb_u32 offset = 0);

    //size/count
    inline const ifb_b8  block_arena_get_info            (const IFBMemoryBlockArenaHandle block_arena_handle, IFBMemoryBlockArenaInfo* block_arena_info);
};


#endif //IFB_MEMORY_HPP