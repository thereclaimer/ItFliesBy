#ifndef IFB_MEMORY_INTERNAL_HPP
#define IFB_MEMORY_INTERNAL_HPP

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryContext;
struct IFBMemoryStack;
struct IFBMemoryBlock;

struct IFBReservation;
struct IFBArena;
struct IFBLinearAllocator;
struct IFBBlockAllocator;

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

struct IFBArena {
    IFBHNDReservation handle_reservation;
    IFBHNDArena       handle_arena;
    IFBArena*         ptr_next;
    IFBAddr           start;
    IFBU32            size;
    IFBU32            position_committed;
    IFBU32            position_reserved;
};

struct IFBArenaList {
    IFBArena* ptr_first;    
    IFBArena* ptr_last;    
    IFBU32    count;
};

/**********************************************************************************/
/* LINEAR ALLOCATOR                                                               */
/**********************************************************************************/

struct IFBLinearAllocator {
    IFBHNDArena arena_handle;
    IFBAddr     start;
    IFBU32      size;
    IFBU32      position;
    IFBU32      save_point;
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBMemoryArenaBlock {
    IFBAddr*    block_address_array;
    IFBHNDArena arena_handle;
    IFBAddr     start;
    IFBU32      block_count;
    IFBU32      block_size;
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBReservation {
    IFBReservation*    next;
    IFBAddr            start;
    IFBHNDReservation  handle;
    IFBU32             page_size;
    IFBU32             page_count_total;
    IFBU32             page_count_committed;
};

struct IFBReservationList {
    IFBReservation* first;
    IFBReservation* last;
    IFBU32          count;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

#define IFB_MEMORY_HANDLE_MINIMUM sizeof(IFBMemoryContext)

struct IFBMemoryContextStack {
    IFBAddr start;
    IFBU32  size;
    IFBU32  position;
};

struct IFBMemoryContextOffsets {
    IFBU32 info;
    IFBU32 reservation_list;
    IFBU32 arena_list;
};

struct IFBMemoryContext {
    IFBMemoryContextStack   stack;
    IFBMemoryContextOffsets offsets;
};


namespace ifb_memory {

    IFBMemoryContextStack&   context_get_stack            (IFBVoid);
    IFBMemoryContextOffsets& context_get_offsets          (IFBVoid);
    IFBMemoryContextInfo*    context_get_local_info       (IFBVoid);      
    IFBReservationList*      context_get_reservation_list (IFBVoid); 
    IFBArenaList*            context_get_arena_list       (IFBVoid); 

    IFBReservation*          context_get_reservation      (const IFBHNDReservation reservation_handle);
    IFBArena*                context_get_arena            (const IFBHNDArena       arena_handle);
};


#endif //IFB_MEMORY_INTERNAL_HPP