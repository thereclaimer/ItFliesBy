#pragma once

#include "ifb-data-structures.hpp"
#include "ifb-data-structures-internal.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBArrayList : IFBDataStructure {
    ifb::u32 element_size;
    ifb::u32 element_count_total;
    ifb::u32 element_count_current;
};

namespace ifb_array_list {

    //validate
    IFBArrayList* cast_and_assert_valid (const IFBDS64ArrayList array_list_handle);

    //shift
    void       shift_down            (IFBArrayList* array_list, const ifb::u32 index, const ifb::u32 count);
    void       shift_up              (IFBArrayList* array_list, const ifb::u32 index, const ifb::u32 count);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

const ifb::u32
ifb_array_list::size(
    const ifb::u32 element_size,
    const ifb::u32 element_count) {

    const ifb::u32 array_list_size_struct = ifb_macro_align_size_struct(IFBArrayList);
    const ifb::u32 array_list_size_data   = element_size * element_count;
    const ifb::u32 array_list_size_total  = array_list_size_struct + array_list_size_data; 

    return(array_list_size_total);
}

const IFBDS64ArrayList
ifb_array_list::create(
    IFBArrayListArgs& args) {

    //validate the args
    ifb::b8 args_are_valid = true;
    args_are_valid &= (args.memory_ptr    != NULL);
    args_are_valid &= (args.memory_size   != 0);
    args_are_valid &= (args.element_size  != 0);
    args_are_valid &= (args.element_count != 0);
    ifb_macro_assert(args_are_valid);

    //sizes
    const ifb::u32 array_list_size_data     = args.element_size * args.element_count;
    const ifb::u32 array_list_size_struct   = ifb_macro_align_size_struct(IFBArrayList);

    //cast the pointer
    const ifb::addr array_list_start_struct = (ifb::addr)args.memory_ptr;
    const ifb::addr array_list_start_data   = array_list_start_struct + array_list_size_struct; 
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

void
ifb_array_list::reset(
    const IFBDS64ArrayList array_list_handle) {

    //assert the list is valid
    IFBArrayList* array_list = ifb_array_list::cast_and_assert_valid(array_list_handle);
    
    //reset the current count
    array_list->element_count_current = 0;
}

const ifb::b8
ifb_array_list::remove(
    const IFBDS64ArrayList array_list_handle,
    const ifb::u32           index) {

    //assert the list is valid
    IFBArrayList* array_list = ifb_array_list::cast_and_assert_valid(array_list_handle);

    //get the counts
    const ifb::u32 count_current = array_list->element_count_current;
    const ifb::u32 count_new     = count_current - 1; 

    //make sure we can do the removal
    ifb::b8 can_remove = true;                // we can remove IF...
    can_remove &= (count_current != 0);     //...we have a non-zero count AND
    can_remove &= (index <= count_current); //...the index is less than the count
    if (!can_remove) return(false);         // if we can't remove, we're done

    //shift the memory down
    ifb_array_list::shift_down(array_list,index,1);

    //update the count
    array_list->element_count_current = count_new;    

    return(true);
}

const ifb::b8
ifb_array_list::add_to_front(
    const IFBDS64ArrayList array_list_handle,
    const ifb::ptr           element_ptr) {

    //assert the list is valid
    IFBArrayList* array_list = ifb_array_list::cast_and_assert_valid(array_list_handle);

    //get the counts
    const ifb::u32 count_max     = array_list->element_count_total;
    const ifb::u32 count_current = array_list->element_count_current;
    const ifb::u32 count_new     = count_current + 1; 

    //make sure we can do the add
    ifb::b8 can_add = count_current <= count_max;
    
    // if we can't add, we're done
    if (!can_add) return(false);       

    //shift everything up by the current count
    ifb_array_list::shift_up(array_list,0,count_current);

    //add the new element to the front
    const ifb::u32   element_size = array_list->element_size;
    const ifb::byte* source       = (ifb::byte*)element_ptr; 
    ifb::byte*       destination  = (ifb::byte*)array_list->start; 

    for (
        ifb::u32 byte_index = 0;
               byte_index < element_size;
             ++byte_index) {

        destination[byte_index] = source[byte_index];
    }

    return(true);
}

const ifb::b8
ifb_array_list::add_to_end(
    const IFBDS64ArrayList array_list_handle,
    const ifb::ptr           element_ptr) {

    //assert the list is valid
    IFBArrayList* array_list = ifb_array_list::cast_and_assert_valid(array_list_handle);

    //get the counts
    const ifb::u32 count_max     = array_list->element_count_total;
    const ifb::u32 count_current = array_list->element_count_current;
    const ifb::u32 count_new     = count_current + 1; 

    //make sure we can do the add
    ifb::b8 can_add = count_current <= count_max;
    
    // if we can't add, we're done
    if (!can_add) return(false);       

    //no need to shift, just calculate the start and size
    const ifb::u32   element_size       = array_list->element_size;
    const ifb::u32   destination_offset = element_size * count_current; 
    const ifb::addr  destination_start  = array_list->start + destination_offset;
    const ifb::byte* source             = (ifb::byte*)element_ptr;
    ifb::byte*       destination        = (ifb::byte*)destination_start; 

    for (
        ifb::u32 byte_index = 0;
               byte_index < element_size;
             ++byte_index) {

        destination[byte_index] = source[byte_index];
    }

    return(true);
}

const ifb::b8
ifb_array_list::insert(
    const IFBDS64ArrayList array_list_handle,
    const ifb::u32           index,
    const ifb::ptr           element_ptr) {

    //assert the list is valid
    IFBArrayList* array_list = ifb_array_list::cast_and_assert_valid(array_list_handle);

    //if the index is at the front or the end, 
    //just call the corresponding method
    const ifb::b8 is_at_front = (index == 0);
    const ifb::b8 is_at_end   = (index == array_list->element_count_current);
    if (is_at_front || is_at_end) {

        //call the corresponding method
        const ifb::b8 result = is_at_front 
            ? ifb_array_list::add_to_front (array_list_handle, element_ptr)
            : ifb_array_list::add_to_end   (array_list_handle, element_ptr);

        //we're done
        return(result);
    }

    //get the counts
    const ifb::u32 count_max     = array_list->element_count_total;
    const ifb::u32 count_current = array_list->element_count_current;
    const ifb::u32 count_new     = count_current + 1; 
    const ifb::u32 count_shift   = count_current - index;

    //make sure we can do the insert
    ifb::b8 can_insert = true;
    can_insert &= (index        < count_current);
    can_insert &= (count_new   <= count_max);
    can_insert &= (count_shift  >  0);
    if (!can_insert) return(false);

    //shift the memory up
    ifb_array_list::shift_up(array_list,index, count_shift);

    //copy everything over
    const ifb::u32   element_size       = array_list->element_size;
    const ifb::u32   destination_offset = element_size * index; 
    const ifb::addr  destination_start  = array_list->start + destination_offset;
    const ifb::byte* source             = (ifb::byte*)element_ptr;
    ifb::byte*       destination        = (ifb::byte*)destination_start; 

    for (
        ifb::u32 byte_index = 0;
               byte_index < element_size;
             ++byte_index) {

        destination[byte_index] = source[byte_index];
    }

    //we're done
    return(true);
}


const ifb::ptr
ifb_array_list::first(
    const IFBDS64ArrayList array_list_handle) {

    //assert the list is valid
    IFBArrayList* array_list = ifb_array_list::cast_and_assert_valid(array_list_handle);

    //check if the list is empty
    const ifb::b8 list_is_empty = (array_list->element_count_current == 0); 

    //if the list is empty, just return null
    //otherwise, cast the data start
    const ifb::ptr element = list_is_empty
        ? NULL
        : (ifb::ptr)array_list->start;

    //we're done
    return(element);
}

const ifb::ptr
ifb_array_list::last(
    const IFBDS64ArrayList array_list_handle) {

    //assert the list is valid
    IFBArrayList* array_list = ifb_array_list::cast_and_assert_valid(array_list_handle);

    //get the offset of the last element
    const ifb::u32 element_count  = array_list->element_count_current;
    const ifb::u32 element_size   = array_list->element_size;
    const ifb::u32 element_offset = element_count * element_size;

    //get the address, if we have a valid offset
    const ifb::addr element_address = element_offset 
        ? array_list->start + element_offset
        : 0;

    //cast the element
    const ifb::ptr element = (ifb::ptr)element_address; 

    //we're done
    return(element);
}

const ifb::ptr
ifb_array_list::index(
    const IFBDS64ArrayList array_list_handle,
    const ifb::u32           index) {

    //assert the list is valid
    IFBArrayList* array_list = ifb_array_list::cast_and_assert_valid(array_list_handle);

    //get the offset of the last index
    const ifb::u32 element_size   = array_list->element_size;
    const ifb::u32 element_offset = index * element_size;

    //get the address, if we have a valid index
    const ifb::addr element_address = element_offset
        ? index < array_list->element_count_current
        : 0;

    //cast the element
    const ifb::ptr element = (ifb::ptr)element_address; 

    //we're done
    return(element);
}


/**********************************************************************************/
/* SIZE
/**********************************************************************************/

void 
ifb_array_list::info(
    const IFBDS64ArrayList  array_list_handle,
          IFBArrayListInfo& info) {
    
    //assert the list is valid
    IFBArrayList* array_list = ifb_array_list::cast_and_assert_valid(array_list_handle);
  
    //set the info
    info.element_size          = array_list->element_size;
    info.element_count_total   = array_list->element_count_total;
    info.element_count_current = array_list->element_count_current;
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBArrayList*
ifb_array_list::cast_and_assert_valid(
    const IFBDS64ArrayList array_list_handle) {

    IFBArrayList* array_list = (IFBArrayList*)array_list_handle.h64;

    //assert the pointer isn't null
    ifb_macro_assert(array_list);

    ifb::b8 is_valid = true;
    is_valid &= (array_list->start                 != 0);
    is_valid &= (array_list->size                  != 0);
    is_valid &= (array_list->element_size          != 0);
    is_valid &= (array_list->element_count_total   != 0);
    is_valid &= (array_list->element_count_current <= array_list->element_count_total);
    ifb_macro_assert(is_valid);

    return(array_list);
}

//TODO: verify
inline void
ifb_array_list::shift_down(
          IFBArrayList* array_list,
    const ifb::u32        index,
    const ifb::u32        count) {

    ifb_macro_assert(count != 0);
    ifb_macro_assert(index <= array_list->element_count_total);

    //calculate sizes
    const ifb::u32 size_element = array_list->element_size;
    const ifb::u32 size_shift   = size_element * count; 
    const ifb::u32 index_offset = size_element * index;

    //calculate the source
    const ifb::addr  shift_source_start = array_list->start + index_offset;
    ifb::byte*       shift_source       = (ifb::byte*)shift_source_start; 

    //copy the values
    for (
        ifb::u32 byte_index_destination = 0;
               byte_index_destination < size_shift;
             ++byte_index_destination) {

        //calculate source index
        const ifb::u32 byte_index_source = byte_index_destination + 1; 

        //get the source and destination
        ifb::byte& ref_byte_destination = shift_source[byte_index_destination];
        ifb::byte& ref_byte_source      = shift_source[byte_index_source];

        //copy the value    
        ref_byte_destination = ref_byte_source;
    }   
}

//TODO: verify
inline void
ifb_array_list::shift_up(
          IFBArrayList* array_list,
    const ifb::u32        index,
    const ifb::u32        count) {

    ifb_macro_assert(count != 0);
    ifb_macro_assert(index <= array_list->element_count_total);

    //calculate sizes
    const ifb::u32 size_element = array_list->element_size;
    const ifb::u32 size_shift   = size_element * count; 
    const ifb::u32 index_offset = size_element * index;

    //calculate the source
    const ifb::addr  shift_source_start = array_list->start + index_offset;
    ifb::byte*       shift_source       = (ifb::byte*)shift_source_start; 

    //copy the values
    for (
        ifb::u32 byte_index_destination  = size_shift;
               byte_index_destination  > 0;
             --byte_index_destination) {

        //calculate source index
        const ifb::u32 byte_index_source = byte_index_destination - 1; 

        //get the source and destination
        ifb::byte& ref_byte_destination = shift_source[byte_index_destination];
        ifb::byte& ref_byte_source      = shift_source[byte_index_source];

        //copy the value    
        ref_byte_destination = ref_byte_source;
    }
}