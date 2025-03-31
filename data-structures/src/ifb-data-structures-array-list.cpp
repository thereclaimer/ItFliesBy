#pragma once

#include "ifb-data-structures.hpp"
#include "ifb-data-structures-internal.cpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

const u32
array_list::size(
    const u32 element_size,
    const u32 element_count) {

    const u32 array_list_size_struct = STRUCT_SIZE_ARRAY_LIST;
    const u32 array_list_size_data   = element_size * element_count;
    const u32 array_list_size_total  = array_list_size_struct + array_list_size_data; 

    return(array_list_size_total);
}

array_list_t*
array_list::create(
    array_list_args_t& args) {

    //validate the args
    b8 args_are_valid = true;
    args_are_valid &= (args.memory_ptr    != NULL);
    args_are_valid &= (args.memory_size   != 0);
    args_are_valid &= (args.element_size  != 0);
    args_are_valid &= (args.element_count != 0);
    ifb_macro_assert(args_are_valid);

    //sizes
    const u32 array_list_size_data        = args.element_size * args.element_count;
    const u32 array_list_size_struct      = STRUCT_SIZE_ARRAY_LIST;

    //cast the pointer
    const addr array_list_start_struct    = (addr)args.memory_ptr;
    const addr array_list_start_data      = array_list_start_struct + array_list_size_struct; 
    array_list_t* array_list_ptr          = (array_list_t*)array_list_start_struct;

    //intialize the array list
    array_list_ptr->start                 = array_list_start_data;
    array_list_ptr->size                  = array_list_size_data;    
    array_list_ptr->element_size          = args.element_size;
    array_list_ptr->element_count_total   = args.element_count;
    array_list_ptr->element_count_current = 0;

    //we're done
    return(array_list_ptr);
}

/**********************************************************************************/
/* OPERATIONS                                                                     */
/**********************************************************************************/

void
array_list::reset(
    array_list_t* array_list) {

    //assert the list is valid
    array_list::assert_valid(array_list);
    
    //reset the current count
    array_list->element_count_current = 0;
}

const b8
array_list::remove(
    array_list_t* array_list,
    const u32     index) {

    //assert the list is valid
    array_list::assert_valid(array_list);

    //get the counts
    const u32 count_current = array_list->element_count_current;
    const u32 count_new     = count_current - 1; 

    //make sure we can do the removal
    b8 can_remove = true;                // we can remove IF...
    can_remove &= (count_current != 0);     //...we have a non-zero count AND
    can_remove &= (index <= count_current); //...the index is less than the count
    if (!can_remove) return(false);         // if we can't remove, we're done

    //shift the memory down
    array_list::shift_down(array_list,index,1);

    //update the count
    array_list->element_count_current = count_new;    

    return(true);
}

const b8
array_list::add_to_front(
    array_list_t* array_list,
    const ptr           element_ptr) {

    //assert the list is valid
    array_list::assert_valid(array_list);

    //get the counts
    const u32 count_max     = array_list->element_count_total;
    const u32 count_current = array_list->element_count_current;
    const u32 count_new     = count_current + 1; 

    //make sure we can do the add
    b8 can_add = count_current <= count_max;
    
    // if we can't add, we're done
    if (!can_add) return(false);       

    //shift everything up by the current count
    array_list::shift_up(array_list,0,count_current);

    //add the new element to the front
    const u32   element_size = array_list->element_size;
    const byte* source       = (byte*)element_ptr; 
    byte*       destination  = (byte*)array_list->start; 

    for (
        u32 byte_index = 0;
               byte_index < element_size;
             ++byte_index) {

        destination[byte_index] = source[byte_index];
    }

    return(true);
}

const b8
array_list::add_to_end(
    array_list_t* array_list,
    const ptr           element_ptr) {

    //assert the list is valid
    array_list::assert_valid(array_list);

    //get the counts
    const u32 count_max     = array_list->element_count_total;
    const u32 count_current = array_list->element_count_current;
    const u32 count_new     = count_current + 1; 

    //make sure we can do the add
    b8 can_add = count_current <= count_max;
    
    // if we can't add, we're done
    if (!can_add) return(false);       

    //no need to shift, just calculate the start and size
    const u32   element_size       = array_list->element_size;
    const u32   destination_offset = element_size * count_current; 
    const addr  destination_start  = array_list->start + destination_offset;
    const byte* source             = (byte*)element_ptr;
    byte*       destination        = (byte*)destination_start; 

    for (
        u32 byte_index = 0;
               byte_index < element_size;
             ++byte_index) {

        destination[byte_index] = source[byte_index];
    }

    return(true);
}

const b8
array_list::insert(
    array_list_t* array_list,
    const u32     index,
    const ptr     element_ptr) {

    //assert the list is valid
    array_list::assert_valid(array_list);

    //if the index is at the front or the end, 
    //just call the corresponding method
    const b8 is_at_front = (index == 0);
    const b8 is_at_end   = (index == array_list->element_count_current);
    if (is_at_front || is_at_end) {

        //call the corresponding method
        const b8 result = is_at_front 
            ? array_list::add_to_front (array_list, element_ptr)
            : array_list::add_to_end   (array_list, element_ptr);

        //we're done
        return(result);
    }

    //get the counts
    const u32 count_max     = array_list->element_count_total;
    const u32 count_current = array_list->element_count_current;
    const u32 count_new     = count_current + 1; 
    const u32 count_shift   = count_current - index;

    //make sure we can do the insert
    b8 can_insert = true;
    can_insert &= (index        < count_current);
    can_insert &= (count_new   <= count_max);
    can_insert &= (count_shift  >  0);
    if (!can_insert) return(false);

    //shift the memory up
    array_list::shift_up(array_list,index, count_shift);

    //copy everything over
    const u32   element_size       = array_list->element_size;
    const u32   destination_offset = element_size * index; 
    const addr  destination_start  = array_list->start + destination_offset;
    const byte* source             = (byte*)element_ptr;
    byte*       destination        = (byte*)destination_start; 

    for (
        u32 byte_index = 0;
               byte_index < element_size;
             ++byte_index) {

        destination[byte_index] = source[byte_index];
    }

    //we're done
    return(true);
}


const ptr
array_list::first(
    array_list_t* array_list) {

    //assert the list is valid
    array_list::assert_valid(array_list);

    //check if the list is empty
    const b8 list_is_empty = (array_list->element_count_current == 0); 

    //if the list is empty, just return null
    //otherwise, cast the data start
    const ptr element = list_is_empty
        ? NULL
        : (ptr)array_list->start;

    //we're done
    return(element);
}

const ptr
array_list::last(
    array_list_t* array_list) {

    //assert the list is valid
    array_list::assert_valid(array_list);

    //get the offset of the last element
    const u32 element_count  = array_list->element_count_current;
    const u32 element_size   = array_list->element_size;
    const u32 element_offset = element_count * element_size;

    //get the address, if we have a valid offset
    const addr element_address = element_offset 
        ? array_list->start + element_offset
        : 0;

    //cast the element
    const ptr element = (ptr)element_address; 

    //we're done
    return(element);
}

const ptr
array_list::index(
    array_list_t* array_list,
    const u32     index) {

    //assert the list is valid
    array_list::assert_valid(array_list);

    //get the offset of the last index
    const u32 element_size   = array_list->element_size;
    const u32 element_offset = index * element_size;

    //get the address, if we have a valid index
    const addr element_address = element_offset
        ? index < array_list->element_count_current
        : 0;

    //cast the element
    const ptr element = (ptr)element_address; 

    //we're done
    return(element);
}


/**********************************************************************************/
/* SIZE
/**********************************************************************************/

void 
array_list::info(
    array_list_t*      array_list,
    array_list_info_t& info) {
    
    //assert the list is valid
    array_list::assert_valid(array_list);

    //set the info
    info.element_size          = array_list->element_size;
    info.element_count_total   = array_list->element_count_total;
    info.element_count_current = array_list->element_count_current;
}