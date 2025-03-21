#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryManagerArgs;
struct IFBMemoryManager;
struct IFBMemoryContext;
struct IFBMemoryContextStack;
struct IFBMemoryArena;
struct IFBMemoryReservation;
struct IFBMemoryBlock;


struct IFBMemoryBlock {
    IFBAddr start;
    IFBU64  size;
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

#define IFB_MEMORY_STACK_INVALID_OFFSET 0xFFFFFFFF

namespace ifb_memory {

    IFBMemoryStack* stack_create                (const IFBByte* stack_memory, const IFBU32 stack_size);

    const IFBU32    stack_push_bytes_relative (IFBMemoryStack* stack, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr    stack_push_bytes_absolute (IFBMemoryStack* stack, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBB8     stack_pull_bytes          (IFBMemoryStack* stack, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr    stack_get_pointer         (IFBMemoryStack* stack, const IFBU32 offset);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

struct IFBMemoryManagerArgs {
    IFBMemoryStack* stack;    
    IFBU64          size_reservation;
    IFBU64          size_arena;
};

namespace ifb_memory {

    IFBMemoryManager* manager_create  (IFBMemoryManagerArgs* args);
    const IFBB8       manager_destroy (IFBMemoryManager* memory_manager);

};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBMemoryContext {
    IFBMemoryReservation* ptr_reservation_first;
    IFBMemoryReservation* ptr_reservation_last;
    IFBMemoryArena*       ptr_arena_first;
    IFBMemoryArena*       ptr_arena_last;
    IFBU32                stack_size;
    IFBU32                stack_position;
    IFBU32                count_reservations;
    IFBU32                count_arenas;
    IFBU32                system_page_size;
    IFBU32                system_granularity;
};

namespace ifb_memory {

    //create/destroy 
    IFBMemoryContext*     context_create                    (const IFBByte* stack_memory, const IFBU64 stack_size);
    const IFBB8           context_destroy                   (IFBMemoryContext* ptr_context);

    //alignment
    const IFBU32          context_align_size_to_page        (const IFBMemoryContext* ptr_context, const IFBU32 size);
    const IFBU32          context_align_size_to_granularity (const IFBMemoryContext* ptr_context, const IFBU32 size);
    
    //size
    const IFBU64          context_get_size_from_page_count  (const IFBMemoryContext* ptr_context, const IFBU32 page_count);
    const IFBU32          context_get_page_count_from_size  (const IFBMemoryContext* ptr_context, const IFBU64 size);

    //stack
    const IFBU32          context_stack_commit_relative     (IFBMemoryContext*       ptr_context, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr          context_stack_commit_absolute     (IFBMemoryContext*       ptr_context, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBPtr          context_stack_get_pointer         (const IFBMemoryContext* ptr_context, const IFBU32 offset);

    //reservations
    IFBMemoryReservation* context_reserve_platform_memory   (IFBMemoryContext*     ptr_context, const IFBU64 size_minimum);
    const IFBB8           context_release_platform_memory   (IFBMemoryReservation* ptr_reservation);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBMemoryReservation {
    IFBMemoryContext*     ptr_context;
    IFBMemoryReservation* ptr_next;
    IFBAddr               start;
    IFBU32                page_count_total;
    IFBU32                page_count_committed;
};

namespace ifb_memory {

    //arena commit
    IFBMemoryArena*
    reservation_commit_arena(
              IFBMemoryReservation* ptr_reservation,
        const IFBU32                size_minimum);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

struct IFBMemoryArena {
    IFBMemoryReservation* ptr_reservation;
    IFBMemoryArena*       ptr_next;
    IFBAddr               start;
    IFBU32                size;
    IFBU32                position_committed;
    IFBU32                position_reserved;
};

namespace ifb_memory {

    //reset
    IFBVoid        arena_reset_all              (IFBMemoryArena* ptr_arena);
    IFBVoid        arena_reset_committed_space  (IFBMemoryArena* ptr_arena);
    IFBVoid        arena_reset_reserved_space   (IFBMemoryArena* ptr_arena);
    
    //pointers
    const IFBPtr   arena_get_pointer            (const IFBMemoryArena* ptr_arena, const IFBU32  offset);
    const IFBAddr  arena_get_start              (const IFBMemoryArena* ptr_arena);

    //reserve/release    
    const IFBPtr   arena_reserve_bytes_absolute (IFBMemoryArena* ptr_arena, const IFBU32 size, const IFBU32  alignment = 0);
    const IFBU32   arena_reserve_bytes_relative (IFBMemoryArena* ptr_arena, const IFBU32 size, const IFBU32  alignment = 0);
    const IFBB8    arena_release_bytes          (IFBMemoryArena* ptr_arena, const IFBU32 size, const IFBU32  alignment = 0);
    
    //commit
    const IFBPtr   arena_commit_bytes_absolute  (IFBMemoryArena* ptr_arena, const IFBU32 size, const IFBU32  alignment = 0);
    const IFBU32   arena_commit_bytes_relative  (IFBMemoryArena* ptr_arena, const IFBU32 size, const IFBU32  alignment = 0);

    //strings
    const IFBChar* arena_commit_string          (IFBMemoryArena* ptr_arena, const IFBChar* c_string, const IFBU32 max_length);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_memory_macro_commit_struct_to_arena_absolute(arena_handle,struct_type) (struct_type*)ifb_memory::arena_commit_bytes_absolute(arena_handle,sizeof(struct_type),alignof(struct_type))
#define ifb_memory_macro_commit_struct_to_arena_relative(arena_handle,struct_type)               ifb_memory::arena_commit_bytes_relative(arena_handle,sizeof(struct_type),alignof(struct_type))
#define ifb_memory_macro_commit_type_to_arena_absolute(arena_handle,size,type)            (type*)ifb_memory::arena_commit_bytes_relative(arena_handle,size)

#define ifb_memory_macro_get_pointer_from_arena(arena_handle,offset,type)                 (type*)ifb_memory::arena_get_pointer(arena_handle,offset)

#endif //IFB_MEMORY_HPP