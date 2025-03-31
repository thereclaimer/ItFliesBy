#pragma once

#include "ifb-memory.hpp"

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb::memory {

    void validate_stack           (const mem_stack_t*       stack);
    void validate_reservation     (const mem_reservation_t* reservation);
    void validate_arena           (const mem_arena_t*       arena);
};

/**********************************************************************************/
/* MEMORY MANAGER DEFINITIONS                                                     */
/**********************************************************************************/

namespace ifb::memory {

    struct mem_stack_t {
        u32 size;
        u32 position;
    };

    struct mem_reservation_t {
        mem_stack_t* stack;
        addr         start;
        struct {
            mem_arena_t* committed;
            mem_arena_t* decommitted;
        } arenas;
        struct {
            u32 arena;
            u32 page;
            u32 granularity;
        } sizes;
        u32 page_count_used;
    };

    struct mem_arena_t {
        mem_reservation_t* reservation;
        mem_arena_t*       next;
        mem_arena_t*       prev;
        addr               start;
        u32                page_number;
        u32                position;
    };
};

#define IFB_MEMORY_STRUCT_SIZE_STACK       ifb_macro_align_size_struct(mem_stack_t)
#define IFB_MEMORY_STRUCT_SIZE_RESERVATION ifb_macro_align_size_struct(mem_reservation_t)
#define IFB_MEMORY_STRUCT_SIZE_ARENA       ifb_macro_align_size_struct(mem_arena_t)

#define macro_stack_push_arena(stack)             (mem_arena_t*)ifb::memory::stack_push_bytes_absolute_pointer (stack, IFB_MEMORY_STRUCT_SIZE_ARENA)
#define macro_stack_push_reservation(stack) (mem_reservation_t*)ifb::memory::stack_push_bytes_absolute_pointer (stack, IFB_MEMORY_STRUCT_SIZE_RESERVATION)

inline void
memory::validate_stack(
    const mem_stack_t* stack) {

    ifb_macro_assert(stack);
    ifb_macro_assert(stack->size     >= IFB_MEMORY_STRUCT_SIZE_STACK);
    ifb_macro_assert(stack->position >= IFB_MEMORY_STRUCT_SIZE_STACK);
    ifb_macro_assert(stack->position <  stack->size);
}   

inline void
memory::validate_reservation(
    const mem_reservation_t* reservation) {

    ifb_macro_assert(reservation);
    ifb_macro_assert(reservation->stack);
    ifb_macro_assert(reservation->start);
    ifb_macro_assert(reservation->sizes.arena);
    ifb_macro_assert(reservation->sizes.page);
    ifb_macro_assert(reservation->sizes.granularity);
}

inline void
memory::validate_arena(
    const mem_arena_t* arena) {

    ifb_macro_assert(arena);
    ifb_macro_assert(arena->reservation);
    ifb_macro_assert(arena->start);
}