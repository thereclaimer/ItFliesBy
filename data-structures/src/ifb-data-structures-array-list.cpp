#pragma once

#include "ifb-data-structures.hpp"
#include "ifb-data-structures-internal.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBArrayList : IFBDataStructure {
    IFBU32 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_current;
};

namespace ifb_array_list {

    //validate
    IFBArrayList* cast_and_assert_valid (const IFBDS64ArrayList array_list_handle);

    //shift
    IFBVoid       shift_down            (IFBArrayList* array_list, const IFBU32 index, const IFBU32 count);
    IFBVoid       shift_up              (IFBArrayList* array_list, const IFBU32 index, const IFBU32 count);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

const IFBU32
ifb_array_list::memory_allocation_size(
    const IFBU32 element_size,
    const IFBU32 element_count) {

    //calculate the struct and data size
    const IFBU32 size_struct = ifb_macro_align_size_struct(IFBArrayList); 
    const IFBU32 size_data   = element_size * element_count;
    const IFBU32 size_total  = size_struct  * size_data;

    //if the data size is 0, there's nothing to do
    const IFBU32 result = size_data == 0 
        ? 0
        : size_total;

    //we're done
    return(result);
}

IFBArrayList*
ifb_array_list::memory_initialize(
    const IFBU32 element_size,
    const IFBU32 element_count,
    const IFBPtr memory) {

    //calculate the sizes
    const IFBU32  size_struct = ifb_macro_align_size_struct(IFBArrayList); 
    const IFBU32  size_data   = element_size * element_count;
    const IFBU32  size_total  = size_struct  * size_data;

    //calculate the addresses
    const IFBAddr addr_struct = (IFBAddr)memory;
    const IFBAddr addr_data   = addr_struct + size_struct; 

    //sanity check
    IFBB8 valid = true;
    valid &= (size_data != 0);
    valid &= (memory    != NULL);
    if (!valid) return(NULL);

    //cast the memory
    IFBArrayList* array_list = (IFBArrayList*)memory;    
    
    //initialize the array list
    array_list->start                 = addr_data;
    array_list->size                  = size_data;    
    array_list->element_size          = element_size;
    array_list->element_count_total   = element_count;
    array_list->element_count_current = 0;

    //we're done
    return(array_list);
}

IFBVoid                ifb_array_list::memory_size  (IFBArrayListMemory& memory);
const IFBDS64ArrayList ifb_array_list::memory_init  (IFBArrayListMemory& memory);

/**********************************************************************************/
/* OPERATIONS                                                                     */
/**********************************************************************************/

const IFBB8
ifb_array_list::reset(
    IFBArrayList* array_list_ptr) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);
    
    //reset the current count
    array_list_ptr->element_count_current = 0;
    
    //we're done
    return(true);
}

const IFBB8
ifb_array_list::remove(
          IFBArrayList* array_list_ptr,
    const IFBU32        index) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);

    //get the counts
    const IFBU32 count_current = array_list_ptr->element_count_current;
    const IFBU32 count_new     = count_current - 1; 

    //make sure we can do the removal
    IFBB8 can_remove = true;                // we can remove IF...
    can_remove &= (count_current != 0);     //...we have a non-zero count AND
    can_remove &= (index <= count_current); //...the index is less than the count
    if (!can_remove) return(false);         // if we can't remove, we're done

    //shift the memory down
    ifb_array_list::shift_down(array_list_ptr,index,1);

    //update the count
    array_list_ptr->element_count_current = count_new;    

    return(true);
}

const IFBB8
ifb_array_list::add_to_front(
          IFBArrayList* array_list_ptr,
    const IFBPtr        element_ptr) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);

    //get the counts
    const IFBU32 count_max     = array_list_ptr->element_count_total;
    const IFBU32 count_current = array_list_ptr->element_count_current;
    const IFBU32 count_new     = count_current + 1; 

    //make sure we can do the add
    IFBB8 can_add = count_current <= count_max;
    
    // if we can't add, we're done
    if (!can_add) return(false);       

    //shift everything up by the current count
    ifb_array_list::shift_up(array_list_ptr,0,count_current);

    //add the new element to the front
    const IFBU32   element_size = array_list_ptr->element_size;
    const IFBByte* source       = (IFBByte*)element_ptr; 
    IFBByte*       destination  = (IFBByte*)array_list_ptr->start; 

    for (
        IFBU32 byte_index = 0;
               byte_index < element_size;
             ++byte_index) {

        destination[byte_index] = source[byte_index];
    }

    return(true);
}

const IFBB8
ifb_array_list::add_to_end(
          IFBArrayList* array_list_ptr,
    const IFBPtr        element_ptr) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);

    //get the counts
    const IFBU32 count_max     = array_list_ptr->element_count_total;
    const IFBU32 count_current = array_list_ptr->element_count_current;
    const IFBU32 count_new     = count_current + 1; 

    //make sure we can do the add
    IFBB8 can_add = count_current <= count_max;
    
    // if we can't add, we're done
    if (!can_add) return(false);       

    //no need to shift, just calculate the start and size
    const IFBU32   element_size       = array_list_ptr->element_size;
    const IFBU32   destination_offset = element_size * count_current; 
    const IFBAddr  destination_start  = array_list_ptr->start + destination_offset;
    const IFBByte* source             = (IFBByte*)element_ptr;
    IFBByte*       destination        = (IFBByte*)destination_start; 

    for (
        IFBU32 byte_index = 0;
               byte_index < element_size;
             ++byte_index) {

        destination[byte_index] = source[byte_index];
    }

    return(true);
}

const IFBB8
ifb_array_list::insert(
          IFBArrayList* array_list_ptr,
    const IFBPtr        element_ptr,
    const IFBU32        index) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);

    //if the index is at the front or the end, 
    //just call the corresponding method
    const IFBB8 is_at_front = (index == 0);
    const IFBB8 is_at_end   = (index == array_list_ptr->element_count_current);
    if (is_at_front || is_at_end) {

        //call the corresponding method
        const IFBB8 result = is_at_front 
            ? ifb_array_list::add_to_front (array_list_ptr, element_ptr)
            : ifb_array_list::add_to_end   (array_list_ptr, element_ptr);

        //we're done
        return(result);
    }

    //get the counts
    const IFBU32 count_max     = array_list_ptr->element_count_total;
    const IFBU32 count_current = array_list_ptr->element_count_current;
    const IFBU32 count_new     = count_current + 1; 
    const IFBU32 count_shift   = count_current - index;

    //make sure we can do the insert
    IFBB8 can_insert = true;
    can_insert &= (index        < count_current);
    can_insert &= (count_new   <= count_max);
    can_insert &= (count_shift  >  0);
    if (!can_insert) return(false);

    //shift the memory up
    ifb_array_list::shift_up(array_list_ptr,index,count_shift);

    //copy everything over
    const IFBU32   element_size       = array_list_ptr->element_size;
    const IFBU32   destination_offset = element_size * index; 
    const IFBAddr  destination_start  = array_list_ptr->start + destination_offset;
    const IFBByte* source             = (IFBByte*)element_ptr;
    IFBByte*       destination        = (IFBByte*)destination_start; 

    for (
        IFBU32 byte_index = 0;
               byte_index < element_size;
             ++byte_index) {

        destination[byte_index] = source[byte_index];
    }

    //we're done
    return(true);
}

/**********************************************************************************/
/* SIZE
/**********************************************************************************/

const IFBU32
ifb_array_list::get_size_total(
    const IFBArrayList* array_list_ptr) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);

    //calculate total size
    const IFBU32 element_size  = array_list_ptr->element_size;
    const IFBU32 element_count = array_list_ptr->element_count_total;
    const IFBU32 size_total    = element_size * element_count;

    //we're done
    return(size_total);
}

const IFBU32
ifb_array_list::get_size_used(
    const IFBArrayList* array_list_ptr) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);

    //calculate total size
    const IFBU32 element_size  = array_list_ptr->element_size;
    const IFBU32 element_count = array_list_ptr->element_count_current;
    const IFBU32 size_total    = element_size * element_count;

    //we're done
    return(size_total);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

const IFBPtr
ifb_array_list::get_element_first(
    const IFBArrayList* array_list_ptr) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);

    //check if the list is empty
    const IFBB8 list_is_empty = (array_list_ptr->element_count_current == 0); 

    //if the list is empty, just return null
    //otherwise, cast the data start
    const IFBPtr element = list_is_empty
        ? NULL
        : (IFBPtr)array_list_ptr->start;

    //we're done
    return(element);
}

const IFBPtr
ifb_array_list::get_element_last(
    const IFBArrayList* array_list_ptr) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);

    //get the offset of the last element
    const IFBU32 element_count  = array_list_ptr->element_count_current;
    const IFBU32 element_size   = array_list_ptr->element_size;
    const IFBU32 element_offset = element_count * element_size;

    //get the address, if we have a valid offset
    const IFBAddr element_address = element_offset 
        ? array_list_ptr->start + element_offset
        : 0;

    //cast the element
    const IFBPtr element = (IFBPtr)element_address; 

    //we're done
    return(element);
}

const IFBPtr
ifb_array_list::get_element_at_index(
    const IFBArrayList* array_list_ptr,
    const IFBU32        index) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);

    //get the offset of the last index
    const IFBU32 element_size   = array_list_ptr->element_size;
    const IFBU32 element_offset = index * element_size;

    //get the address, if we have a valid index
    const IFBAddr element_address = element_offset
        ? index < array_list_ptr->element_count_current
        : 0;

    //cast the element
    const IFBPtr element = (IFBPtr)element_address; 

    //we're done
    return(element);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBVoid
ifb_array_list::assert_valid(
    const IFBArrayList* array_list) {

    //assert the pointer isn't null
    ifb_macro_assert(array_list);

    //constants
    const IFBU32 element_size        = array_list->element_size;
    const IFBU32 element_count_total = array_list->element_count_total;
    const IFBU32 size_total          = element_size * element_count_total;

    //validate the list
    IFBB8 valid = true;                                                  // the list is valid IF...
    valid &= (array_list->start            != 0);                   //...the data start isn't null AND
    valid &= (array_list->size             == size_total);          //...the data size is accurate AND
    valid &= (array_list->element_size          != 0);                   //...the element size isn't 0  AND
    valid &= (array_list->element_count_total   != 0);                   //...the tota count isn't 0    AND
    valid &= (array_list->element_count_current <= element_count_total); //...the current count isn't greater than the total count
    ifb_macro_assert(valid);
}

//TODO: verify
inline IFBVoid
ifb_array_list::shift_down(
          IFBArrayList* array_list,
    const IFBU32        index,
    const IFBU32        count) {

    ifb_macro_assert(count != 0);
    ifb_macro_assert(index <= array_list->element_count_total);

    //calculate sizes
    const IFBU32 size_element = array_list->element_size;
    const IFBU32 size_shift   = size_element * count; 
    const IFBU32 index_offset = size_element * index;

    //calculate the source
    const IFBAddr  shift_source_start = array_list->start + index_offset;
    IFBByte*       shift_source       = (IFBByte*)shift_source_start; 

    //copy the values
    for (
        IFBU32 byte_index_destination = 0;
               byte_index_destination < size_shift;
             ++byte_index_destination) {

        //calculate source index
        const IFBU32 byte_index_source = byte_index_destination + 1; 

        //get the source and destination
        IFBByte& ref_byte_destination = shift_source[byte_index_destination];
        IFBByte& ref_byte_source      = shift_source[byte_index_source];

        //copy the value    
        ref_byte_destination = ref_byte_source;
    }   
}

//TODO: verify
inline IFBVoid
ifb_array_list::shift_up(
          IFBArrayList* array_list,
    const IFBU32        index,
    const IFBU32        count) {

    ifb_macro_assert(count != 0);
    ifb_macro_assert(index <= array_list->element_count_total);

    //calculate sizes
    const IFBU32 size_element = array_list->element_size;
    const IFBU32 size_shift   = size_element * count; 
    const IFBU32 index_offset = size_element * index;

    //calculate the source
    const IFBAddr  shift_source_start = array_list->start + index_offset;
    IFBByte*       shift_source       = (IFBByte*)shift_source_start; 

    //copy the values
    for (
        IFBU32 byte_index_destination  = size_shift;
               byte_index_destination  > 0;
             --byte_index_destination) {

        //calculate source index
        const IFBU32 byte_index_source = byte_index_destination - 1; 

        //get the source and destination
        IFBByte& ref_byte_destination = shift_source[byte_index_destination];
        IFBByte& ref_byte_source      = shift_source[byte_index_source];

        //copy the value    
        ref_byte_destination = ref_byte_source;
    }
}