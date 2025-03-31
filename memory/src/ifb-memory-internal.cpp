#pragma once

#include "ifb-memory.hpp"

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb::memory {

    void validate_stack           (const stack_t*       stack);
    void validate_reservation     (const reservation_t* reservation);
    void validate_arena           (const arena_t*       arena);

};

/**********************************************************************************/
/* MEMORY MANAGER DEFINITIONS                                                     */
/**********************************************************************************/

namespace ifb::memory {

    struct stack_t {
        u32 size;
        u32 position;
    };

    struct reservation_t {
        stack_t* stack;
        addr     start;
        struct {
            arena_t* committed;
            arena_t* decommitted;
        } arenas;
        struct {
            u32 arena;
            u32 page;
            u32 granularity;
        } sizes;
        u32 page_count_used;
    };

    struct arena_t {
        reservation_t* reservation;
        arena_t*       next;
        arena_t*       prev;
        addr           start;
        u32            page_number;
        u32            position;
    };
};

#define IFB_MEMORY_STRUCT_SIZE_STACK       ifb_macro_align_size_struct(stack_t)
#define IFB_MEMORY_STRUCT_SIZE_RESERVATION ifb_macro_align_size_struct(reservation_t)
#define IFB_MEMORY_STRUCT_SIZE_ARENA       ifb_macro_align_size_struct(arena_t)

#define macro_stack_push_arena(stack)             (arena_t*)ifb::memory::stack_push_bytes_absolute_pointer (stack, IFB_MEMORY_STRUCT_SIZE_ARENA)
#define macro_stack_push_reservation(stack) (reservation_t*)ifb::memory::stack_push_bytes_absolute_pointer (stack, IFB_MEMORY_STRUCT_SIZE_RESERVATION)

inline void
memory::validate_stack(
    const stack_t* stack) {

    ifb_macro_assert(stack);
    ifb_macro_assert(stack->size     >= IFB_MEMORY_STRUCT_SIZE_STACK);
    ifb_macro_assert(stack->position >= IFB_MEMORY_STRUCT_SIZE_STACK);
    ifb_macro_assert(stack->position <  stack->size);
}   

inline void
memory::validate_reservation(
    const reservation_t* reservation) {

    ifb_macro_assert(reservation);
    ifb_macro_assert(reservation->stack);
    ifb_macro_assert(reservation->start);
    ifb_macro_assert(reservation->sizes.arena);
    ifb_macro_assert(reservation->sizes.page);
    ifb_macro_assert(reservation->sizes.granularity);
}

inline void
memory::validate_arena(
    const arena_t* arena) {

    ifb_macro_assert(arena);
    ifb_macro_assert(arena->reservation);
    ifb_macro_assert(arena->start);
}