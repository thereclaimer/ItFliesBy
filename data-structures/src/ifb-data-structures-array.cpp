#pragma once

#include "ifb-data-structures.hpp"
#include "ifb-data-structures-internal.cpp"

using namespace ifb;
using namespace ifb::ds;

/**********************************************************************************/
/* MEMORY                                                                       */
/**********************************************************************************/

const u32
ds::array_memory_size(
    const u32 element_size,
    const u32 element_count) {

    const u32 memory_size = 
        element_size  +
        element_count +
        _globals.struct_size_array;         

    return(memory_size);
}

array_t*
ds::array_memory_init(
    const u32       element_size,
    const u32       element_count,
    const memory_t& memory) {

    //get the actual memory size
    const u32 memory_size = array_memory_size(element_size, element_count);

    //sanity check
    ifb_macro_assert(memory.start  != NULL);
    ifb_macro_assert(memory.size   != memory_size);
    ifb_macro_assert(element_size  != 0);
    ifb_macro_assert(element_count != 0);
    ifb_macro_assert(element_count != 0);

    //cast the pointer
    array_t* array_ptr = (array_t*)memory.start;
    
    //initialize the array
    array_ptr->data_start            = memory.start + _globals.struct_size_array;
    array_ptr->data_size             = element_size * element_count;
    array_ptr->element_size          = element_size;
    array_ptr->element_count_total   = element_count;
    array_ptr->element_count_current = 0;

    //we're done
    return(array_ptr);
}

/**********************************************************************************/
/* INFO                                                                           */
/**********************************************************************************/

void
ds::array_info(
    array_t*      array,
    array_info_t& info) {

    //validate the array
    array_assert_valid(array);

    //set the info
    info.element_size          = array->element_size;
    info.element_count_total   = array->element_count_total;
    info.element_count_current = array->element_count_current;
}

/**********************************************************************************/
/* OPERATIONS                                                                     */
/**********************************************************************************/

void
ds::array_clear(
    array_t* array) {

    //get the array
    array_assert_valid(array);
    array->element_count_current = 0;
}

const b8
ds::array_add(
    array_t*  array,
    const u32 count,
    const ptr element) {

    //validate the array
    array_assert_valid(array);

    //sanity check
    b8 result = true;
    result &= (count   >  0);
    result &= (element != NULL);
    if (!result) return(false);


    //make sure we can fit the element(s)
    const u32 array_count_total     = array->element_count_total;
    const u32 array_count_current   = array->element_count_current;
    const u32 array_count_new       = array_count_current + count;
    if (array_count_new > array_count_total) return(false);

    //calculate the end of the current array data
    const u32  array_element_size   = array->element_size;
    const u32  array_size_current   = array_element_size * array_count_current;
    const addr array_end            = array->data_start  + array_size_current;
    
    //calculate the element source and destination
    byte*       element_destination = (byte*)array_end;
    const u32   element_source_size = array_element_size * count;
    const byte* element_source      = (const byte*)element;

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
ds::array_index(
          array_t* array,
    const u32      index) {

    //get the array
    array_assert_valid(array);

    //check the index is valid
    if (index >= array->element_count_current) return(NULL);

    //calculate the element pointer
    const u32  element_size    = array->element_size;
    const u32  element_offset  = element_size * index; 
    const addr element_address = array->data_start + element_offset;
    const ptr  element_pointer = (ptr)element_address;

    //we're done
    return(element_pointer);
}

const b8
ds::array_iterate(
    array_t*    array,
    iterator_t& iterator) {

    //get the array
    array_assert_valid(array);

    //check the iterator
    const u32 array_count_current = array->element_count_current;
    if (iterator.index >= array_count_current) {
        
        //if the iterator is greater than the current count, 
        //just set it to the current count and return false
        iterator.index = array_count_current;
        return(false);
    } 

    //get the pointer at the index
    iterator.pointer = array_index(array,iterator.index);
    
    //update the index
    ++iterator.index;

    //we're done
    return(true);
}