#ifndef IFB_TYPES_MEMORY_HPP
#define IFB_TYPES_MEMORY_HPP

#include "ifb-types-primitives.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBHNDMemoryContext;
struct IFBHNDMemoryReservation;
struct IFBHNDMemoryArena;
struct IFBMemoryContext;
struct IFBMemoryArena;
struct IFBMemoryReservation;
struct IFBMemoryBlock;

/**********************************************************************************/
/* MEMORY TYPES                                                                   */
/**********************************************************************************/

struct IFBHNDMemoryContext     : IFBHNDPTR { };
struct IFBHNDMemoryReservation : IFBHNDPTR { };
struct IFBHNDMemoryArena       : IFBHNDPTR { };

struct IFBMemoryBlock {
    IFBAddr start;
    IFBU64  size;
};

struct IFBMemoryContext {
    IFBMemoryReservation* ptr_reservation_first;
    IFBMemoryReservation* ptr_reservation_last;
    IFBMemoryArena*       ptr_arena_first;
    IFBMemoryArena*       ptr_arena_last;
    IFBAddr               stack_start;
    IFBU32                stack_size;
    IFBU32                stack_position;
    IFBU32                count_reservations;
    IFBU32                count_arenas;
    IFBU32                system_page_size;
    IFBU32                system_granularity;
};

struct IFBMemoryReservation {
    IFBMemoryContext*     ptr_context;
    IFBMemoryReservation* ptr_next;
    IFBAddr               start;
    IFBU32                page_count_total;
    IFBU32                page_count_committed;
};

struct IFBMemoryArena {
    IFBMemoryReservation* ptr_reservation;
    IFBMemoryArena*       ptr_next;
    IFBAddr               start;
    IFBU32                size;
    IFBU32                position_committed;
    IFBU32                position_reserved;
};

#endif //IFB_TYPES_MEMORY_HPP