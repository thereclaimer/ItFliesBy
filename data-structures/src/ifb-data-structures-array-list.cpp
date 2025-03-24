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

IFBVoid
ifb_array_list::size(
    IFBArrayListArgs& args) {

    const IFBU32 array_list_size_struct = ifb_macro_align_size_struct(IFBArrayList);
    const IFBU32 array_list_size_data   = args.element_size * args.element_count;
    args.memory_size = array_list_size_struct + array_list_size_data; 
}

const IFBDS64ArrayList
ifb_array_list::create(
    IFBArrayListArgs& args) {

    //validate the args
    IFBB8 args_are_valid = true;
    args_are_valid &= (args.memory_ptr    != NULL);
    args_are_valid &= (args.memory_size   != 0);
    args_are_valid &= (args.element_size  != 0);
    args_are_valid &= (args.element_count != 0);
    ifb_macro_assert(args_are_valid);

    //sizes
    const IFBU32 array_list_size_data     = args.element_size * args.element_count;
    const IFBU32 array_list_size_struct   = ifb_macro_align_size_struct(IFBArrayList);

    //cast the pointer
    const IFBAddr array_list_start_struct = (IFBAddr)args.memory_ptr;
    const IFBAddr array_list_start_data   = array_list_start_struct + array_list_size_struct; 
    IFBArrayList* array_list_ptr          = (IFBArrayList*)array_list_start_struct;

    //intialize the array list
    array_list_ptr->start                 = array_list_start_data;
    array_list_ptr->size                  = array_list_size_data;    
    array_list_ptr->element_size          = args.element_size;
    array_list_ptr->element_count_total   = args.element_count;
    array_list_ptr->element_count_current = 0;

    //return the handle
    IFBDS64ArrayList array_list_handle;
    array_list_handle.h64 = array_list_start_struct;
    return(array_list_handle);
}

/**********************************************************************************/
/* OPERATIONS                                                                     */
/**********************************************************************************/

const IFBB8
ifb_array_list::reset(
    const IFBDS64ArrayList array_list_handle) {

    //assert the list is valid
    ifb_array_list::assert_valid(array_list_ptr);
    
    //reset the current count
    array_list_ptr->element_count_current = 0;
    
    //we're done
    return(true);
}

const IFBB8
ifb_array_list::remove(
    const IFBDS64ArrayList array_list_handle,
    const IFBU32           index) {

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
    const IFBDS64ArrayList array_list_handle,
    const IFBPtr           element_ptr) {

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
    const IFBDS64ArrayList array_list_handle,
    const IFBPtr           element_ptr) {

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
    const IFBDS64ArrayList array_list_handle,
    const IFBPtr           element_ptr,
    const IFBU32           index) {

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


const IFBPtr
ifb_array_list::first(
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
ifb_array_list::last(
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
ifb_array_list::index(
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
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBVoid
ifb_array_list::cast_and_assert_valid(
    const IFBDS64ArrayList array_list_handle) {

    //assert the pointer isn't null
    ifb_macro_assert(array_list);

    IFBB8 is_valid = true;
    is_valid &= (array_list->start                 != 0);
    is_valid &= (array_list->size                  != 0);
    is_valid &= (array_list->element_size          != 0);
    is_valid &= (array_list->element_count_total   != 0);
    is_valid &= (array_list->element_count_current <= array_list->element_count_total);
    ifb_macro_assert(is_valid);
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