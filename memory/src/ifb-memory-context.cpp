#include "ifb-memory.hpp"

ifb_global const IFBU32 IFB_MEMORY_CONTEXT_STRUCT_SIZE = ifb_macro_align_size_struct(IFBMemoryContext);

/**********************************************************************************/
/* CREATE / DESTROY                                                               */
/**********************************************************************************/

IFBMemoryContext*
ifb_memory::context_create(
    const IFBByte* stack_memory,
    const IFBU64   stack_size) {

    IFBB8 result = true; 

    //get the system memory info
    IFBSystemMemoryInfo memory_info;
    result &= ifb_platform::system_get_info_memory(&memory_info);

    //we can proceed IF...
    result &= (stack_memory                      != NULL);                           //...the stack memory isn't null AND
    result &= (stack_size                        >= IFB_MEMORY_CONTEXT_STRUCT_SIZE); //...the stack memory can fit the context AND
    result &= (memory_info.page_size              > 0);                              //...the system page size isn't 0 AND
    result &= (memory_info.allocation_granularity > 0);                              //...the system granularity isn't 0
    if (!result) return(NULL);                                                       // if everything isn't valid, we're done

    //cast and initialize the context
    IFBMemoryContext* ptr_context = (IFBMemoryContext*)stack_memory;
    ptr_context->ptr_reservation_first = NULL;
    ptr_context->ptr_reservation_last  = NULL;
    ptr_context->stack_size            = stack_size; 
    ptr_context->stack_position        = IFB_MEMORY_CONTEXT_STRUCT_SIZE;
    ptr_context->system_page_size      = memory_info.page_size;
    ptr_context->system_granularity    = memory_info.allocation_granularity;

    //we're done
    return(ptr_context);
}

const IFBB8
ifb_memory::context_destroy(
    IFBMemoryContext* ptr_context) {

    //TODO
    ifb_macro_panic();
    return(false);
}

/**********************************************************************************/
/* ALIGNMENT                                                                      */
/**********************************************************************************/

const IFBU32 
ifb_memory::context_align_size_to_page(
    const IFBMemoryContext* ptr_context, 
    const IFBU32            size) {

    ifb_macro_assert(ptr_context);

    //get the page size
    const IFBU32 page_size = ptr_context->system_page_size;
    ifb_macro_assert(page_size);

    //align the size
    const IFBU32 size_aligned = ifb_macro_align_a_to_b(size,page_size); 

    //we're done
    return(size_aligned);
}

const IFBU32 
ifb_memory::context_align_size_to_granularity(
    const IFBMemoryContext* ptr_context, 
    const IFBU32            size) {

    ifb_macro_assert(ptr_context);

    //get the granularity
    const IFBU32 granularity = ptr_context->system_granularity;
    ifb_macro_assert(granularity);

    //align the size
    const IFBU32 size_aligned = ifb_macro_align_a_to_b(size,granularity); 

    //we're done
    return(size_aligned);
}

/**********************************************************************************/
/* SIZE                                                                           */
/**********************************************************************************/

const IFBU64
ifb_memory::context_get_size_from_page_count(
    const IFBMemoryContext* ptr_context, 
    const IFBU32            page_count) {

    ifb_macro_assert(ptr_context);

    //get the page size
    const IFBU32 page_size = ptr_context->system_page_size;
    ifb_macro_assert(page_size);

    //calculate the size
    const IFBU64 size = page_count * page_size;

    //we're done
    return(size);
}

const IFBU32
ifb_memory::context_get_page_count_from_size(
    const IFBMemoryContext* ptr_context, 
    const IFBU64            size) {

    ifb_macro_assert(ptr_context);

    //get the page size
    const IFBU32 page_size = ptr_context->system_page_size;
    ifb_macro_assert(page_size);

    //calculate the page count
    const IFBU32 page_count = (IFBU32)(size / page_size);
    
    //we're done
    return(page_count);  
}

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

const IFBU32
ifb_memory::context_stack_commit_relative(
          IFBMemoryContext* ptr_context, 
    const IFBU32            size,
    const IFBU32            alignment) {

    ifb_macro_assert(ptr_context);

    //calculate the aligned size
    const IFBU32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    //calculate the new position
    const IFBU32 offset       = ptr_context->stack_position;
    const IFBU32 position_new = offset + size_aligned;

    //make sure we can fit the commit
    ifb_macro_assert(position_new < ptr_context->stack_size);

    //update the position
    ptr_context->stack_position = position_new;
    
    //we're done
    return(offset);
}

const IFBPtr
ifb_memory::context_stack_commit_absolute(
          IFBMemoryContext* ptr_context, 
    const IFBU32            size,
    const IFBU32            alignment) {

    ifb_macro_assert(ptr_context);

    //calculate the aligned size
    const IFBU32 size_aligned = ifb_macro_align_a_to_b(size,alignment);

    //calculate the new position
    const IFBU32 stack_size             = ptr_context->stack_size;
    const IFBU32 stack_position_current = ptr_context->stack_position;
    const IFBU32 stack_position_new     = stack_position_current + size_aligned;

    //make sure we can fit the commit
    ifb_macro_assert(stack_position_new < stack_size);

    //update the position
    ptr_context->stack_position = stack_position_new;
    
    //calculate the pointer
    const IFBAddr stack_start          = (IFBAddr)ptr_context;
    const IFBAddr stack_result_offset  = stack_start + stack_position_current;
    const IFBPtr  stack_result_pointer = (IFBPtr)stack_result_offset;

    //we're done
    return(stack_result_pointer);
}

const IFBPtr
ifb_memory::context_stack_get_pointer(
    const IFBMemoryContext* ptr_context, 
    const IFBU32            offset) {

    ifb_macro_assert(ptr_context);

    //calculate the pointer
    const IFBAddr stack_start   = (IFBAddr)ptr_context;
    const IFBAddr stack_offset  = stack_start + offset;
    const IFBPtr  stack_pointer = (stack_offset < ptr_context->stack_size) ? (IFBPtr)stack_offset : NULL; 
        
    //we're done
    return(stack_pointer);
}

/**********************************************************************************/
/* RESERVATIONS                                                                   */
/**********************************************************************************/

//reservations
IFBMemoryReservation*
ifb_memory::context_reserve_platform_memory(
          IFBMemoryContext* ptr_context, 
    const IFBU64            size_minimum) {

    //sanity check
    ifb_macro_assert(ptr_context);
    ifb_macro_assert(size_minimum);

    //get the granularity and page size 
    const IFBU32 granularity = ptr_context->system_granularity;
    const IFBU32 page_size   = ptr_context->system_page_size;
    ifb_macro_assert(granularity);
    ifb_macro_assert(page_size);
    
    //align the size
    const IFBU64 size_aligned = ifb_macro_align_a_to_b(size_minimum,(IFBU64)granularity);

    //make the reservation
    const IFBPtr ptr_platform_memory = ifb_platform::memory_reserve(size_aligned);
    if (!ptr_platform_memory) return(NULL);

    //search the list for reservations to recycle
    IFBMemoryReservation* ptr_reservation = NULL;
    for (
        IFBMemoryReservation* ptr_reservation_current = ptr_context->ptr_reservation_first;
        ptr_reservation_current != NULL;
        ptr_reservation_current = ptr_reservation_current->ptr_next) {
            
            //if the reservation has no pages and no start address
            //it is free to use
            IFBB8 reservation_is_free = true;
            reservation_is_free &= ptr_reservation_current->page_count_total == 0;
            reservation_is_free &= ptr_reservation_current->start            == 0;
            if (reservation_is_free) {
                ptr_reservation = ptr_reservation_current;
                break;
            }
    }
    
    //if we didn't find a reservation struct, we need to commit a new one
    if (!ptr_reservation) {

        //struct size
        const IFBU32 reservation_struct_size = ifb_macro_align_size_struct(IFBMemoryReservation); 

        //stack commit
        ptr_reservation = (IFBMemoryReservation*)ifb_memory::context_stack_commit_absolute(
            ptr_context,
            reservation_struct_size);
    }
    
    //we should always have a reservation at this point
    ifb_macro_assert(ptr_reservation);

    //calculate page count
    const IFBU32 page_count = size_aligned / page_size;

    //initialize the reservation
    ptr_reservation->ptr_context          = ptr_context;
    ptr_reservation->ptr_next             = NULL;
    ptr_reservation->start                = (IFBAddr)ptr_platform_memory;
    ptr_reservation->page_count_total     = page_count;
    ptr_reservation->page_count_committed = 0;

    //if this is the first one, we need to initialize the list
    if (ptr_context->count_reservations == 0) {

        //pointers should be null
        ifb_macro_assert(ptr_context->ptr_reservation_first == NULL);
        ifb_macro_assert(ptr_context->ptr_reservation_last  == NULL);

        //initialize the list
        ptr_context->ptr_reservation_first = ptr_reservation;
        ptr_context->ptr_reservation_last  = ptr_reservation;
        ptr_context->count_reservations    = 1;
    }
    else {

        //first and last elements should NOT be null
        ifb_macro_assert(ptr_context->ptr_reservation_first);
        ifb_macro_assert(ptr_context->ptr_reservation_last);
        
        //cache first and last elements
        IFBMemoryReservation* ptr_element_first = ptr_context->ptr_reservation_first; 
        IFBMemoryReservation* ptr_element_last  = ptr_context->ptr_reservation_last; 
        
        //if we are adding a second element, make sure
        //we update the next pointer for the first element
        if (ptr_context->count_reservations == 1) {
            ifb_macro_assert(ptr_element_first->ptr_next == NULL);
            ptr_element_first->ptr_next = ptr_reservation;
        }
        
        //update the end of the list
        ifb_macro_assert(ptr_element_first->ptr_next);
        ptr_element_last->ptr_next        = ptr_reservation;
        ptr_context->ptr_reservation_last = ptr_reservation; 

        //update the count
        ++ptr_context->count_reservations;
    }
    
    //we're done
    return(ptr_reservation);
}

const IFBB8
ifb_memory::context_release_platform_memory(
    IFBMemoryReservation* ptr_reservation) {

    //sanity check
    ifb_macro_assert(ptr_reservation);
    IFBMemoryContext* ptr_context = ptr_reservation->ptr_context;
    ifb_macro_assert(ptr_context);

    //calculate reservation size
    const IFBU32 page_size         = ptr_context->system_page_size; 
    const IFBPtr reservation_start = (IFBPtr)ptr_reservation->start;
    const IFBU64 reservation_size  = ptr_reservation->page_count_total * page_size; 

    //release memory
    const IFBB8 result = ifb_platform::memory_release(
        reservation_start,
        reservation_size);

    //if that failed, we're done
    if (!result) return(false);
        
    //update the reservation
    ptr_reservation->start                = 0;
    ptr_reservation->page_count_total     = 0;
    ptr_reservation->page_count_committed = 0;

    //we're done
    return(true);
}