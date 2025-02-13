#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* GLOBAL CONTEXT                                                                 */
/**********************************************************************************/

ifb_global IFBMemoryContext* _context_ptr;

/**********************************************************************************/
/* CREATE / DESTROY                                                               */
/**********************************************************************************/

ifb_internal inline const ifb_b8
ifb_memory::context_create(
    const ifb_byte* stack_memory,
    const ifb_u32   stack_size) {

    //calculate the size of the memory struct
    const ifb_u32 memory_struct_size = ifb_macro_align_size_struct(IFBMemoryContext);

    // make sure the platform api methods are defined 
    // and the stack is valid and large enough
    ifb_b8 result = true;
    result &= ifb_platform::system_api_valid();
    result &= ifb_platform::memory_api_valid();
    result &= stack_memory != NULL;
    result &= stack_size   >= memory_struct_size;

    //if everything isn't valid, we're done
    if (!result) return(NULL);

    //cast the stack memory to the memory struct
    _context_ptr = (IFBMemoryContext*)stack_memory;

    //cache the properties
    IFBMemoryStack&           stack_ref            = _context_ptr->stack;
    IFBMemoryReservationList& reservation_list_ref = _context_ptr->reservation_list;

    //initialize the stac
    stack_ref.start    = (ifb_address)stack_memory;
    stack_ref.end      = stack_ref.start + stack_size;
    stack_ref.position = memory_struct_size;
    stack_ref.size     = stack_size;

    //clear the reservation list
    reservation_list_ref.first = NULL;
    reservation_list_ref.last  = NULL;
    reservation_list_ref.count = 0;

    //we're done
    return(true);
}

ifb_internal inline const ifb_b8
ifb_memory::context_destroy(
    ifb_void) {

    //sanity check
    ifb_macro_assert(_context_ptr);

    const ifb_u32 page_size = _context_ptr->system_info.page_size;

    //release the reservations
    ifb_b8 result = true;
    for (
        IFBMemoryReservation* current_reservation_ptr = _context_ptr->reservation_list.first;
        current_reservation_ptr != NULL;
        current_reservation_ptr = current_reservation_ptr->next) {

        //get the current reservation info
        const ifb_u32 current_reservation_size  = current_reservation_ptr->page_count_total * page_size;  
        const ifb_ptr current_reservation_start = (ifb_ptr)current_reservation_ptr->start;

        //release it
        result &= ifb_platform::memory_release(
            current_reservation_start,
            current_reservation_size);
    }

    //clear the stack
    const ifb_u32 stack_size  = _context_ptr->stack.size;
    const ifb_ptr stack_start = (ifb_ptr)_context_ptr; 
    memset(stack_start,0,stack_size);

    //we're done
    return(result);
}

/**********************************************************************************/
/* SYSTEM INFO                                                                    */
/**********************************************************************************/

ifb_internal inline const ifb_b8 
ifb_memory::context_get_system_info(
    IFBMemorySystemInfo* system_info) {

    //sanity check
    ifb_macro_assert(_context_ptr);
    if (!system_info) return(false);

    //get the system info
    IFBMemorySystemInfo& context_system_info = _context_ptr->system_info;
    system_info->page_size   = context_system_info.page_size;
    system_info->granularity = context_system_info.granularity;

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

ifb_internal inline IFBMemoryContext*
ifb_memory::context(
    ifb_void) {

    ifb_macro_assert(_context_ptr);
    return(_context_ptr);
}

ifb_internal inline IFBMemoryStack&
ifb_memory::context_get_stack(
    ifb_void) {

    ifb_macro_assert(_context_ptr);
    return(_context_ptr->stack);
}

ifb_internal inline IFBMemorySystemInfo&
ifb_memory::context_get_system_info(
    ifb_void) {
    
    ifb_macro_assert(_context_ptr);
    return(_context_ptr->system_info);
}

ifb_internal inline IFBMemoryReservationList&
ifb_memory::context_get_reservation_list(
    ifb_void) {
    
    ifb_macro_assert(_context_ptr);
    return(_context_ptr->reservation_list);
} 