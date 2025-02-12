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
    const ifb_u32 memory_struct_size = ifb_macro_align_size_struct(IFBMemory);

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
    return(memory_ptr);
}

ifb_internal inline const ifb_b8
ifb_memory::context_destroy(
    IFBMemoryContext* memory_context_ptr) {

    //sanity check
    ifb_macro_assert(memory_context_ptr);

    //release the reservation
    const ifb_b8 result = ifb_memory::release(memory_context_ptr);

    //clear the stack
    const ifb_u32 stack_size  = memory_context_ptr->stack.size;
    const ifb_ptr stack_start = (ifb_ptr)memory_context_ptr; 
    memset(stack_start,0,stack_size);

    //we're done
    return(result);
}

/**********************************************************************************/
/* SYSTEM INFO                                                                    */
/**********************************************************************************/

ifb_internal inline const ifb_b8 
ifb_memory::context_get_system_info(
    const IFBMemoryContext*    memory_context_ptr,
          IFBMemorySystemInfo* system_info) {

    //sanity check
    ifb_macro_assert(memory_context_ptr);
    if (!system_info) return(false);

    //get the system info
    IFBMemorySystemInfo& context_system_info = memory_context_ptr->system_info;
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