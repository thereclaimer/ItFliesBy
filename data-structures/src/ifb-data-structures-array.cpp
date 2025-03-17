#pragma once

#include "ifb-data-structures.hpp"


/**********************************************************************************/
/* ALLOCATE                                                                       */
/**********************************************************************************/

inline const IFBU32
ifb_array::allocation_size_structure(
    IFBVoid) {

    const IFBU32 struct_size = ifb_macro_align_size_struct(IFBArray);
    return(struct_size);
}

inline const IFBU32
ifb_array::allocation_size_total(
    const IFBU32 element_size,
    const IFBU32 element_count) {

    //calculate the allocation size
    const IFBU32 struct_size     = ifb_macro_align_size_struct(IFBArray);
    const IFBU32 data_size       = element_size * element_count;
    const IFBU32 allocation_size = struct_size  + data_size;

    //we're done
    return(allocation_size);
}

inline const IFBU32
ifb_array::allocation_size_data(
    const IFBU32 element_size,
    const IFBU32 element_count) {

    //calculate the allocation size
    const IFBU32 data_size = element_size * element_count;

    //we're done
    return(data_size);
}

/**********************************************************************************/
/* ARENA RESERVE                                                                  */
/**********************************************************************************/

inline IFBArray*
ifb_array::reserve_from_arena(
    const IFBHNDLinearAllocator linear_arena_handle,
    const IFBU32                    element_size,
    const IFBU32                    element_count) {

    IFBB8 result = true;

    //sanity check
    result &= ifb_memory_macro_handle_valid(linear_arena_handle);
    result &= element_size  > 0;
    result &= element_count > 0;
    if (!result) return(NULL);

    //calculate allocation size
    const IFBU32 array_size_struct = ifb_macro_align_size_struct(IFBArray);
    const IFBU32 array_size_data   = element_size * element_count;
    const IFBU32 array_size_total  = array_size_struct + array_size_data;

    //reserve the bytes
    const IFBPtr pointer = ifb_memory::linear_arena_reserve_bytes_absolute(
        linear_arena_handle,
        array_size_total);

    //if that didn't work, we're done
    if (!pointer) return(NULL);

    //calculate the start of the data
    const IFBAddr array_data_start = ((IFBAddr)pointer) + array_size_struct;

    //cast and initialize the array
    IFBArray* ptr_array = (IFBArray*)pointer;
    ptr_array->start         = array_data_start;
    ptr_array->size          = array_size_data;
    ptr_array->element_size  = element_size;
    ptr_array->element_count = element_count;

    //we're done
    return(ptr_array);
}

inline IFBArray*
ifb_array::reserve_from_arena(
    const IFBHNDArenaBlock  block_arena_handle,
    const IFBU32                    element_size,
    const IFBU32                    element_count) {

    //TODO
    return(NULL);
}

/**********************************************************************************/
/* CREATE/INITIALIZE                                                              */
/**********************************************************************************/

inline IFBArray*
ifb_array::create(
    const IFBPtr memory,
    const IFBU32 element_size,
    const IFBU32 element_count) {

    //sanity check
    IFBB8 valid = true;
    valid &= memory        != NULL;
    valid &= element_size   > 0;
    valid &= element_count  > 0;
    if (!valid) return(NULL);

    //calculate the array data start and size    
    const IFBU32     struct_size  = ifb_macro_align_size_struct(IFBArray);
    const IFBAddr struct_start = (IFBAddr)memory;
    const IFBAddr data_start   = struct_start + struct_size;
    const IFBSize    data_size    = element_size * element_count; 

    //initialize the array  
    IFBArray* array_ptr = (IFBArray*)memory;
    array_ptr->start         = data_start;
    array_ptr->size          = data_size;
    array_ptr->element_size  = element_size;
    array_ptr->element_count = element_count;

    //we're done
    return(array_ptr);
}

inline const IFBB8
ifb_array::initialize(
          IFBArray* array_ptr,
    const IFBPtr   data,
    const IFBU32   element_size,
    const IFBU32   element_count) {

    //sanity check
    IFBB8 valid = true;
    valid &= array_ptr     != NULL;
    valid &= data          != NULL;
    valid &= element_size   > 0;
    valid &= element_count  > 0;
    if (!valid) return(false);

    //initialize the array
    array_ptr->start         = (IFBAddr)data;
    array_ptr->size          = element_size * element_count;
    array_ptr->element_size  = element_size;
    array_ptr->element_count = element_count;

    //we're done
    return(true);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

inline const IFBPtr
ifb_array::get_pointer_indexed(
    const IFBArray* array_ptr,
    const IFBU32   index) {

    //sanity check
    if (!array_ptr || index >= array_ptr->element_count) return(NULL);

    //calculate the pointer at the index
    const IFBU32     offset  = index * array_ptr->element_size;
    const IFBAddr address = array_ptr->start + offset;
    const IFBPtr     pointer = (IFBPtr)address;

    //we're done
    return(pointer); 
}

inline const IFBPtr
ifb_array::get_pointer_start(
    const IFBArray* array_ptr) {

    //sanity check
    if (!array_ptr) return(NULL);

    //cast the start address
    const IFBPtr pointer = (IFBPtr)array_ptr->start;

    //we're done
    return(pointer);

}

/**********************************************************************************/
/* SIZE / COUNT                                                                   */
/**********************************************************************************/

inline const IFBU32
ifb_array::get_element_size(
    const IFBArray* array_ptr) {

    const IFBU32 element_size = array_ptr
        ? array_ptr->element_size
        : 0;
        
    return(element_size);
}

inline const IFBU32
ifb_array::get_element_count(
    const IFBArray* array_ptr) {

    const IFBU32 element_count = array_ptr
        ? array_ptr->element_count
        : 0;

    return(element_count);
}

inline const IFBU32
ifb_array::get_array_size(
    const IFBArray* array_ptr) {

    //sanity check
    if (!array_ptr) return(0);

    //calculate the size
    const IFBU32 array_size = array_ptr->element_count * array_ptr->element_size;

    //we're done
    return(array_size);
}