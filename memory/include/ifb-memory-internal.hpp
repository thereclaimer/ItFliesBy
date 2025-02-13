#ifndef IFB_MEMORY_INTERNAL_HPP
#define IFB_MEMORY_INTERNAL_HPP

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryContext;
struct IFBMemoryReservation;
struct IFBMemoryArena;
struct IFBMemoryStack;
struct IFBMemoryLinearArena;
struct IFBMemoryBlockArena;
struct IFBMemoryBlock;

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

#define IFB_MEMORY_HANDLE_MINIMUM sizeof(IFBMemoryContext)

struct IFBMemoryStack {
    ifb_address start;
    ifb_address end;
    ifb_u32     size;
    ifb_u32     position;
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBMemoryReservation {
    IFBMemoryReservation* next;
    ifb_address           start;
    ifb_u32               stack_offset;
    ifb_u32               page_count_total;
    ifb_u32               page_count_committed;
    IFBMemoryArenaList    arena_list;
};

struct IFBMemoryReservationList {
    IFBMemoryReservation* first;
    IFBMemoryReservation* last;
    ifb_u32               count;
};

/**********************************************************************************/
/* ARENA BASE                                                                     */
/**********************************************************************************/

struct IFBMemoryArena {
    ifb_address           start;
    IFBMemoryReservation* reservation;
    IFBMemoryArena*       next;
    IFBMemoryArenaType    type;    
    ifb_u32               page_start;
    ifb_u32               page_count;
    ifb_u32               size_total;
    ifb_u32               stack_position;
};

struct IFBMemoryArenaList {
    IFBMemoryArena* first;    
    IFBMemoryArena* last;    
    ifb_u32         count;
};

/**********************************************************************************/
/* ARENA LINEAR                                                                   */
/**********************************************************************************/

struct IFBMemoryLinearArena : IFBMemoryArena {
    ifb_u32 position;
    ifb_u32 save_point;
};

/**********************************************************************************/
/* ARENA BLOCK                                                                    */
/**********************************************************************************/

struct IFBMemoryBlockArena : IFBMemoryArena  {
    ifb_address* block_address_array;
    ifb_u32      block_count;
    ifb_u32      block_size;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBMemoryContext {
    IFBMemoryStack           stack;
    IFBMemorySystemInfo      system_info;
    IFBMemoryReservationList reservation_list;
};

namespace ifb_memory {

    inline IFBMemoryContext*         context                         (ifb_void);
    inline IFBMemoryStack&           context_get_stack               (ifb_void);            
    inline IFBMemorySystemInfo&      context_get_system_info         (ifb_void);      
    inline IFBMemoryReservationList& context_get_reservation_list    (ifb_void); 
};

#endif //IFB_MEMORY_INTERNAL_HPP