#pragma once

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryReservation;
struct IFBMemoryArena;

namespace ifb_memory {

    void validate_stack       (const IFBMemoryStack*       stack);
    void validate_reservation (const IFBMemoryReservation* reservation);
    void validate_arena       (const IFBMemoryArena*       arena);
};

/**********************************************************************************/
/* MEMORY MANAGER DEFINITIONS                                                     */
/**********************************************************************************/

struct IFBMemoryStack {
    ifb::u32  size;
    ifb::u32  position;
};

struct IFBMemoryReservation {
    IFBMemoryStack* stack;
    ifb::addr         start;
    struct {
        IFBMemoryArena* committed;
        IFBMemoryArena* decommitted;
    } arenas;
    struct {
        ifb::u32 arena;
        ifb::u32 page;
        ifb::u32 granularity;
    } sizes;
    ifb::u32 page_count_used;
};

struct IFBMemoryArena {
    IFBMemoryReservation* reservation;
    IFBMemoryArena*       next;
    IFBMemoryArena*       prev;
    ifb::addr               start;
    ifb::u32                page_number;
    ifb::u32                position;
};


#define IFB_MEMORY_STRUCT_SIZE_STACK       ifb_macro_align_size_struct(IFBMemoryStack)
#define IFB_MEMORY_STRUCT_SIZE_RESERVATION ifb_macro_align_size_struct(IFBMemoryReservation)
#define IFB_MEMORY_STRUCT_SIZE_ARENA       ifb_macro_align_size_struct(IFBMemoryArena)

#define ifb_memory_macro_stack_push_arena(stack)             (IFBMemoryArena*)ifb_memory::stack_push_bytes_absolute_pointer(stack,IFB_MEMORY_STRUCT_SIZE_ARENA)
#define ifb_memory_macro_stack_push_reservation(stack) (IFBMemoryReservation*)ifb_memory::stack_push_bytes_absolute_pointer(stack,IFB_MEMORY_STRUCT_SIZE_RESERVATION)

inline void
ifb_memory::validate_stack(
    const IFBMemoryStack* stack) {

    ifb_macro_assert(stack);
    ifb_macro_assert(stack->size     >= IFB_MEMORY_STRUCT_SIZE_STACK);
    ifb_macro_assert(stack->position >= IFB_MEMORY_STRUCT_SIZE_STACK);
    ifb_macro_assert(stack->position <  stack->size);
}   

inline void
ifb_memory::validate_reservation(
    const IFBMemoryReservation* reservation) {

    ifb_macro_assert(reservation);
    ifb_macro_assert(reservation->stack);
    ifb_macro_assert(reservation->start);
    ifb_macro_assert(reservation->sizes.arena);
    ifb_macro_assert(reservation->sizes.page);
    ifb_macro_assert(reservation->sizes.granularity);
}

inline void
ifb_memory::validate_arena(
    const IFBMemoryArena* arena) {

    ifb_macro_assert(arena);
    ifb_macro_assert(arena->reservation);
    ifb_macro_assert(arena->start);
}