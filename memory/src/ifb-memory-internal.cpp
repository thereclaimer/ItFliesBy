#pragma once

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryReservation;
struct IFBMemoryArena;

namespace ifb_memory {

    IFBVoid validate_stack       (const IFBMemoryStack*       stack);
    IFBVoid validate_reservation (const IFBMemoryReservation* reservation);
    IFBVoid validate_arena       (const IFBMemoryArena*       arena);
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
    struct {
        IFBU32 arena;
        IFBU32 page;
        IFBU32 granularity;
    } sizes;
    IFBU32 page_count_used;
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
#define IFB_MEMORY_STRUCT_SIZE_ARENA       ifb_macro_align_size_struct(IFBMemoryArena)

#define ifb_memory_macro_stack_push_arena(stack)             (IFBMemoryArena*)ifb_memory::stack_push_bytes_absolute(stack,IFB_MEMORY_STRUCT_SIZE_ARENA)
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
    ifb_macro_assert(reservation->stack);
    ifb_macro_assert(reservation->start);
    ifb_macro_assert(reservation->sizes.arena);
    ifb_macro_assert(reservation->sizes.page);
    ifb_macro_assert(reservation->sizes.granularity);
}

inline IFBVoid
ifb_memory::validate_arena(
    const IFBMemoryArena* arena) {

    ifb_macro_assert(arena);
    ifb_macro_assert(arena->reservation);
    ifb_macro_assert(arena->start);
}