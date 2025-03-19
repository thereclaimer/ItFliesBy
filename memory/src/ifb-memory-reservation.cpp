#include "ifb-memory.hpp"

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

//arena commit
IFBMemoryArena*
ifb_memory::reservation_commit_arena(
          IFBMemoryReservation* ptr_reservation,
    const IFBU32                size_minimum) {

    IFBMemoryArena* ptr_arena = NULL;

    //sanity check
    ifb_macro_assert(ptr_reservation);
    ifb_macro_assert(size_minimum);

    //get the context
    IFBMemoryContext* ptr_context = ptr_reservation->ptr_context;

    //calculate the commit start
    const IFBU32  page_size         = ptr_context->system_page_size; 
    const IFBU32  commit_size       = ifb_macro_align_a_to_b(size_minimum,page_size);
    const IFBU32  commit_page_count = commit_size / page_size;
    const IFBU32  commit_offset     = ptr_reservation->page_count_committed * page_size; 
    const IFBAddr commit_start_addr = ptr_reservation->start                + commit_offset;
    const IFBPtr  commit_start_ptr  = (IFBPtr)commit_start_addr;

    //do the commit
    const IFBPtr commit_result = ifb_platform::memory_commit(
        commit_start_ptr,
        commit_size);
    
    //make sure we got the expected result
    if (commit_result != commit_start_ptr) return(NULL);

    //search the list for arenas to recycle
    for (
        IFBMemoryArena* ptr_arena_current = ptr_context->ptr_arena_first;
        ptr_arena_current != NULL;
        ptr_arena_current = ptr_arena_current->ptr_next) {
            
        //if the arena has no reservation and no start address
        //it is free to use
        IFBB8 arena_is_free = true;
        arena_is_free &= (ptr_arena_current->ptr_reservation == NULL);
        arena_is_free &= (ptr_arena_current->start           == 0);
        if (arena_is_free) {
            ptr_arena = ptr_arena_current;
            break;
        }
    }
    
    //if we didn't find an arena struct, we need to commit a new one
    if (!ptr_arena) {

        //commit reservation structure
        const IFBU32 arena_struct_size = ifb_macro_align_size_struct(IFBMemoryArena); 
        ptr_arena = (IFBMemoryArena*)ifb_memory::context_stack_commit_absolute(
            ptr_reservation->ptr_context,
            arena_struct_size);
    }
     
    //we should always have an arena at this point
    ifb_macro_assert(ptr_arena);

    //initialize the arena
    ptr_arena->ptr_reservation    = ptr_reservation;
    ptr_arena->ptr_next           = NULL;
    ptr_arena->start              = (IFBAddr)commit_result;
    ptr_arena->size               = commit_size;
    ptr_arena->position_committed = commit_size - 1;
    ptr_arena->position_reserved  = 0;
    
    //if this is the first one, we need to initialize the list
    if (ptr_context->count_arenas == 0) {

        //pointers should be null
        ifb_macro_assert(ptr_context->ptr_arena_first == NULL);
        ifb_macro_assert(ptr_context->ptr_arena_last  == NULL);

        //initialize the list
        ptr_context->ptr_arena_first = ptr_arena;
        ptr_context->ptr_arena_last  = ptr_arena;
        ptr_context->count_arenas    = 1;
    }
    else {

        //first and last elements should NOT be null
        ifb_macro_assert(ptr_context->ptr_arena_first);
        ifb_macro_assert(ptr_context->ptr_arena_last);
        
        //cache first and last elements
        IFBMemoryArena* element_first = ptr_context->ptr_arena_first; 
        IFBMemoryArena* element_last  = ptr_context->ptr_arena_last; 
        
        //if we are adding a second element, make sure
        //we update the next pointer for the first element
        if (ptr_context->count_arenas == 1) {
            ifb_macro_assert(element_first->ptr_next == NULL);
            element_first->ptr_next = ptr_arena;
        }
        
        //update the end of the list
        ifb_macro_assert(element_first->ptr_next);
        element_last->ptr_next      = ptr_arena;
        ptr_context->ptr_arena_last = ptr_arena; 

        //update the count
        ++ptr_context->count_arenas;
    }

    //update the reservation
    ptr_reservation->page_count_committed += commit_page_count;

    //we're done
    return(ptr_arena);
}