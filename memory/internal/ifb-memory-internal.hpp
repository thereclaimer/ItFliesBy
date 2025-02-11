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

struct IFBMemoryStack {
    ifb_address end;
    ifb_u32     size;
    ifb_u32     position;
};

namespace ifb_memory {
    
    IFBMemoryArena*       stack_push_arena_base        (IFBMemoryContext* memory_ptr);
    IFBMemoryLinearArena* stack_push_arena_linear      (IFBMemoryContext* memory_ptr);
    IFBMemoryBlockArena*  stack_push_arena_block       (IFBMemoryContext* memory_ptr);
    IFBMemoryBlock*       stack_push_arena_block_array (IFBMemoryContext* memory_ptr, const ifb_u32 block_count);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBMemoryReservation {
    IFBMemoryReservation* next;
    ifb_address           start;
    ifb_u32               pages_total;
    ifb_u32               pages_committed;
    IFBMemoryArenaList    arena_list;
};

struct IFBMemoryReservationList {
    IFBMemoryReservation* first;
    IFBMemoryReservation* last;
    ifb_u32               count;
};

namespace ifb_memory {

    const ifb_ptr reservation_get_page_start_next (const IFBMemory* memory_ptr);
    const ifb_ptr reservation_get_page_start      (const IFBMemory* memory_ptr, const ifb_u32 page_number);
    
    const ifb_address 
    reservation_commit_pages(
        IFBMemoryReservation* reservation_ptr)
};

/**********************************************************************************/
/* ARENA BASE                                                                     */
/**********************************************************************************/

struct IFBMemoryArena {
    IFBMemoryArena*    next;
    IFBMemoryArenaType type;    
    ifb_u32            page_start;
    ifb_u32            page_count;
};

struct IFBMemoryArenaList {
    IFBMemoryArena* first;    
    IFBMemoryArena* last;    
    ifb_u32         count;
};

namespace ifb_memory {

    const ifb_b8 arena_list_add (IFBMemoryArenaList& arena_list_ref, IFBMemoryArena* arena_base_ptr);
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

struct IFBMemoryBlock {
    ifb_address start;
};

struct IFBMemoryBlockArena : IFBMemoryArena  {
    IFBMemoryBlock* block_array;
    ifb_u32         block_count;
    ifb_u32         block_size;
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

    ifb_global IFBMemoryContext* _context_ptr;

    inline IFBMemoryContext*         context();
    inline IFBMemoryStack&           context_get_stack()            { return(_context_ptr->stack);       }
    inline IFBMemorySystemInfo&      context_get_system_info()      { return(_context_ptr->system_info); }
    inline IFBMemoryReservationList& context_get_reservation_list() { return(_context_ptr->reservation_list); } 
};

#define ifb_memory_macro_assert_context() ifb_macro_assert(ifb_memory::context())

#endif //IFB_MEMORY_INTERNAL_HPP