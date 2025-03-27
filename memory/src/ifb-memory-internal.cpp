#pragma once

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryReservation;
struct IFBMemoryArena;

namespace ifb_memory {

    IFBVoid validate_stack       (const IFBMemoryStack* stack);
    IFBVoid validate_reservation (const IFBMemoryReservation* reservation);
};

/**********************************************************************************/
/* MEMORY MANAGER DEFINITIONS                                                     */
/**********************************************************************************/

struct IFBMemoryStack {
    IFBU32  size;
    IFBU32  position;
};

struct IFBMemoryReservation {
    IFBMemoryStack* stack;
    IFBAddr         start;
    struct {
        IFBMemoryArena* committed;
        IFBMemoryArena* decommitted;
    } arenas;
    IFBU32 page_count_used;
    IFBU32 size_arena;
    IFBU32 size_page;
    IFBU32 size_granularity;
};

struct IFBMemoryArena {
    IFBMemoryReservation* reservation;
    IFBMemoryArena*       next;
    IFBMemoryArena*       prev;
    IFBAddr               start;
    IFBU32                page_number;
    IFBU32                position;
};


#define IFB_MEMORY_STRUCT_SIZE_STACK       ifb_macro_align_size_struct(IFBMemoryStack)
#define IFB_MEMORY_STRUCT_SIZE_RESERVATION ifb_macro_align_size_struct(IFBMemoryReservation)

#define ifb_memory_macro_stack_push_arena(stack)             (IFBMemoryStack*)ifb_memory::stack_push_bytes_absolute(stack,IFB_MEMORY_STRUCT_SIZE_STACK)
#define ifb_memory_macro_stack_push_reservation(stack) (IFBMemoryReservation*)ifb_memory::stack_push_bytes_absolute(stack,IFB_MEMORY_STRUCT_SIZE_RESERVATION)

inline IFBVoid
ifb_memory::validate_stack(
    const IFBMemoryStack* stack) {

    ifb_macro_assert(stack);
    ifb_macro_assert(stack->size     >= IFB_MEMORY_STRUCT_SIZE_STACK);
    ifb_macro_assert(stack->position >= IFB_MEMORY_STRUCT_SIZE_STACK);
    ifb_macro_assert(stack->position <  stack->size);
}   

inline IFBVoid
ifb_memory::validate_reservation(
    const IFBMemoryReservation* reservation) {

    ifb_macro_assert(reservation);
    ifb_macro_assert(reservation->system_memory_start);
    ifb_macro_assert(reservation->stack_offset);
    ifb_macro_assert(reservation->size_arena);
    ifb_macro_assert(reservation->size_page);
    ifb_macro_assert(reservation->size_granularity);
}   