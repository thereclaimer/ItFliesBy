#pragma once

#include "ifb-data-structures.hpp"

/**********************************************************************************/
/* ARRAY                                                                          */
/**********************************************************************************/

struct IFBArray : IFBDataStructure {
    ifb_u32 element_size;
    ifb_u32 element_count;
};

/**********************************************************************************/
/* ALLOCATE                                                                       */
/**********************************************************************************/

inline const ifb_u32
ifb_array::allocation_size_structure(
    ifb_void) {

    const ifb_u32 struct_size = ifb_macro_align_size_struct(IFBArray);
    return(struct_size);
}

inline const ifb_u32
ifb_array::allocation_size_total(
    const ifb_u32 element_size,
    const ifb_u32 element_count) {

    //calculate the allocation size
    const ifb_u32 struct_size     = ifb_macro_align_size_struct(IFBArray);
    const ifb_u32 data_size       = element_size * element_count;
    const ifb_u32 allocation_size = struct_size  + data_size;

    //we're done
    return(allocation_size);
}

inline const ifb_u32
ifb_array::allocation_size_data(
    const ifb_u32 element_size,
    const ifb_u32 element_count) {

    //calculate the allocation size
    const ifb_u32 data_size = element_size * element_count;

    //we're done
    return(data_size);
}

/**********************************************************************************/
/* CREATE/INITIALIZE                                                              */
/**********************************************************************************/

inline IFBArray*
ifb_array::create(
    const ifb_ptr memory,
    const ifb_u32 element_size,
    const ifb_u32 element_count) {

    //sanity check
    ifb_b8 valid = true;
    valid &= memory        != NULL;
    valid &= element_size   > 0;
    valid &= element_count  > 0;
    if (!valid) return(NULL);

    //calculate the array data start and size    
    const ifb_u32     struct_size  = ifb_macro_align_size_struct(IFBArray);
    const ifb_address struct_start = (ifb_address)memory;
    const ifb_address data_start   = struct_start + struct_size;
    const ifb_size    data_size    = element_size * element_count; 

    //initialize the array  
    IFBArray* array_ptr = (IFBArray*)memory;
    array_ptr->start         = data_start;
    array_ptr->size          = data_size;
    array_ptr->element_size  = element_size;
    array_ptr->element_count = element_count;

    //we're done
    return(array_ptr);
}

inline const ifb_b8
ifb_array::initialize(
          IFBArray* array_ptr,
    const ifb_ptr   data,
    const ifb_u32   element_size,
    const ifb_u32   element_count) {

    //sanity check
    ifb_b8 valid = true;
    valid &= array_ptr     != NULL;
    valid &= data          != NULL;
    valid &= element_size   > 0;
    valid &= element_count  > 0;
    if (!valid) return(false);

    //initialize the array
    array_ptr->start         = (ifb_address)data;
    array_ptr->size          = element_size * element_count;
    array_ptr->element_size  = element_size;
    array_ptr->element_count = element_count;

    //we're done
    return(true);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

inline const ifb_ptr
ifb_array::get_pointer_indexed(
    const IFBArray* array_ptr,
    const ifb_u32   index) {

    //sanity check
    if (!array_ptr || index >= array_ptr->element_count) return(NULL);

    //calculate the pointer at the index
    const ifb_u32     offset  = index * array_ptr->element_size;
    const ifb_address address = array_ptr->start + offset;
    const ifb_ptr     pointer = (ifb_ptr)address;

    //we're done
    return(pointer); 
}

inline const ifb_ptr
ifb_array::get_pointer_start(
    const IFBArray* array_ptr) {

    //sanity check
    if (!array_ptr) return(NULL);

    //cast the start address
    const ifb_ptr pointer = (ifb_ptr)array_ptr->start;

    //we're done
    return(pointer);

}

/**********************************************************************************/
/* SIZE / COUNT                                                                   */
/**********************************************************************************/

inline const ifb_u32
ifb_array::get_element_size(
    const IFBArray* array_ptr) {

    const ifb_u32 element_size = array_ptr
        ? array_ptr->element_size
        : 0;
        
    return(element_size);
}

inline const ifb_u32
ifb_array::get_element_count(
    const IFBArray* array_ptr) {

    const ifb_u32 element_count = array_ptr
        ? array_ptr->element_count
        : 0;

    return(element_count);
}

inline const ifb_u32
ifb_array::get_array_size(
    const IFBArray* array_ptr) {

    //sanity check
    if (!array_ptr) return(0);

    //calculate the size
    const ifb_u32 array_size = array_ptr->element_count * array_ptr->element_size;

    //we're done
    return(array_size);
}