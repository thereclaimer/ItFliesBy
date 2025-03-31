#pragma once

#include "ifb-data-structures.hpp"
#include "ifb-data-structures-internal.cpp"


/**********************************************************************************/
/* MEMORY                                                                       */
/**********************************************************************************/

void
array::size(
    array_args_t& args) {

    //cache args
    const u32 element_size  = args.element_size;
    const u32 element_count = args.element_count;

    //calculate the memory size
    args.memory_size = array_macro_size_total(
        args.element_size,
        args.element_count);
}

array_t*
array::create(
    array_args_t& args) {

    //sanity check
    ifb_macro_assert(args.memory_ptr    != NULL);
    ifb_macro_assert(args.memory_size   != 0);
    ifb_macro_assert(args.element_size  != 0);
    ifb_macro_assert(args.element_count != 0);

    //get the addresses
    const addr array_start_struct = (addr)args.memory_ptr;
    const addr array_start_data   = array_start_struct + STRUCT_SIZE_ARRAY;

    //cast the pointer
    array_t* array_ptr = (array_t*)args.memory_ptr;
    
    //initialize the array
    array_ptr->start                 = array_start_data;
    array_ptr->size                  = array_macro_size_data(args.element_size, args.element_count);
    array_ptr->element_size          = args.element_size;
    array_ptr->element_count_total   = args.element_count;
    array_ptr->element_count_current = 0;

    //we're done
    return(array_ptr);
}

/**********************************************************************************/
/* INFO                                                                           */
/**********************************************************************************/

void
array::info(
    array_t*      array,
    array_info_t& info) {

    assert_valid(array);

    //set the info
    info.element_size          = array->element_size;
    info.element_count_total   = array->element_count_total;
    info.element_count_current = array->element_count_current;
}

/**********************************************************************************/
/* OPERATIONS                                                                     */
/**********************************************************************************/

void
array::clear(
    array_t* array) {

    //get the array
    assert_valid(array);
    array->element_count_current = 0;
}

const b8
array::add(
          array_t* array,
    const u32      count,
    const ptr      element) {

    //sanity check
    b8 result = true;
    result &= (count   >  0);
    result &= (element != NULL);
    if (!result) return(false);

    //get the array
    assert_valid(array);

    //make sure we can fit the element(s)
    const u32 array_count_total   = array->element_count_total;
    const u32 array_count_current = array->element_count_current;
    const u32 array_count_new     = array_count_current + count;
    if (array_count_new > array_count_total) return(false);

    //calculate the end of the current array data
    const u32  array_element_size = array->element_size;
    const u32  array_size_current = array_element_size * array_count_current;
    const addr array_end          = array->start + array_size_current;
    
    //calculate the element source and destination
    ifb::byte*       element_destination = (ifb::byte*)array_end;
    const u32   element_source_size = array_element_size * count;
    const ifb::byte* element_source      = (const ifb::byte*)element;

    //copy the data
    for (
        u32 byte_index = 0;
               byte_index < element_source_size;
             ++byte_index) {

        element_destination[byte_index] = element_source[byte_index];        
    }

    //update the count and do a final sanity check
    array->element_count_current = array_count_new;
    ifb_macro_assert(array->element_count_current < array_count_total);

    //we're done
    return(true);
}

const ptr
array::index(
          array_t* array,
    const u32      index) {

    //get the array
    assert_valid(array);

    //check the index is valid
    if (index >= array->element_count_current) return(NULL);

    //calculate the element pointer
    const u32  element_size    = array->element_size;
    const u32  element_offset  = element_size * index; 
    const addr element_address = array->start + element_offset;
    const ptr  element_pointer = (ptr)element_address;

    //we're done
    return(element_pointer);
}

const b8
array::iterate(
    array_t*    array,
    iterator_t& iterator) {

    //get the array
    assert_valid(array);

    //check the iterator
    const u32 array_count_current = array->element_count_current;
    if (iterator.index >= array_count_current) {
        
        //if the iterator is greater than the current count, 
        //just set it to the current count and return false
        iterator.index = array_count_current;
        return(false);
    } 

    //get the pointer at the index
    iterator.pointer = array::index(array,iterator.index);
    
    //update the index
    ++iterator.index;

    //we're done
    return(true);
}