#pragma once

#include "ifb-data-structures.hpp" 

namespace ifb_hash_table {

    inline IFBHash* get_hash_array(const IFBHashTable* ptr_hash_table);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

const IFBU32
ifb_hash_table::memory_size(
    const IFBU32 element_count,
    const IFBU32 element_size) {

    //sanity check
    if (element_count == 0 || element_size == 0) return(0);

    //calculate sizes
    const IFBU32 size_array_hash    = ifb_macro_array_size(IFBHash, element_count);
    const IFBU32 size_array_element = element_count * element_size;
    const IFBU32 size_table         = ifb_macro_align_size_struct(IFBHashTable);
    const IFBU32 size_total         = size_array_hash + size_array_element + size_table;

    //we're done
    return(size_total);
}

const IFBU32
ifb_hash_table::commit_to_arena_relative(
    const IFBHNDArena arena_handle,
    const IFBU32      element_count,
    const IFBU32      element_size,
    const IFBU32      key_length_max) {

    //sanity check
    if (element_count == 0 || element_size == 0) return(0);

    //calculate sizes
    const IFBU32 size_table         = ifb_macro_align_size_struct(IFBHashTable);
    const IFBU32 size_array_hash    = ifb_macro_array_size(IFBHash, element_count);
    const IFBU32 size_array_element = element_count * element_size;
    const IFBU32 size_data          = size_array_hash + size_array_element; 
    const IFBU32 size_total         = size_data       + size_table;

    //do the commit, if it fails we're done
    const IFBU32 offset = ifb_memory::arena_commit_bytes_relative(arena_handle, size_total);  
    if (!ifb_memory_macro_handle_valid(offset)) return(0);

    //get the pointer, we should ALWAYS be able
    //to get a pointer to a commit we just made
    IFBHashTable* ptr_hash_table = (IFBHashTable*)ifb_memory::arena_get_pointer(arena_handle,offset);
    ifb_macro_assert(ptr_hash_table);

    //calculate starting addresses
    const IFBAddr start_address_data     = ((IFBAddr)ptr_hash_table) + size_table;
    const IFBAddr start_address_elements = start_address_data + size_array_hash; 

    //initialize the table
    ptr_hash_table->start                 = data_start;
    ptr_hash_table->size                  = size_data;
    ptr_hash_table->element_array_start   = start_address_elements;
    ptr_hash_table->element_size          = element_size;
    ptr_hash_table->element_count_max     = element_count;
    ptr_hash_table->element_count_current = 0;
    ptr_hash_table->key_length_max        = key_length_max;

    //we're done
    return(offset);
}

IFBHashTable*
ifb_hash_table::commit_to_arena_absolute(
    const IFBHNDArena arena_handle,
    const IFBU32      element_count,
    const IFBU32      element_size,
    const IFBU32      key_length_max) {

    //sanity check
    if (element_count == 0 || element_size == 0) return(0);

    //calculate sizes
    const IFBU32 size_table         = ifb_macro_align_size_struct(IFBHashTable);
    const IFBU32 size_array_hash    = ifb_macro_array_size(IFBHash, element_count);
    const IFBU32 size_array_element = element_count * element_size;
    const IFBU32 size_data          = size_array_hash + size_array_element; 
    const IFBU32 size_total         = size_data       + size_table;

    //do the commit, if it fails we're done
    IFBHashTable* ptr_hash_table = (IFBHashTable*)ifb_memory::arena_commit_bytes_absolute(arena_handle, size_total);  
    if (!ptr_hash_table) return(NULL);

    //calculate starting addresses
    const IFBAddr start_address_data     = ((IFBAddr)ptr_hash_table) + size_table;
    const IFBAddr start_address_elements = start_address_data + size_array_hash; 

    //initialize the table
    ptr_hash_table->start                 = data_start;
    ptr_hash_table->size                  = size_data;
    ptr_hash_table->element_array_start   = start_address_elements;
    ptr_hash_table->element_size          = element_size;
    ptr_hash_table->element_count_max     = element_count;
    ptr_hash_table->element_count_current = 0;
    ptr_hash_table->key_length_max        = key_length_max;

    //we're done
    return(ptr_hash_table);
}

IFBHashTable*
ifb_hash_table::load_from_arena(
    const IFBHNDArena arena_handle,
    const IFBU32      offset) {

    IFBHashTable* ptr_hash_table = (IFBHashTable*)ifb_memory::arena_get_pointer(arena_handle,offset);
    return(ptr_hash_table);
}

//operations
const IFBB8
ifb_hash_table::insert(
          IFBHashTable* ptr_hash_table,
    const IFBChar*      key,
    const IFBByte*      element) {

    //sanity check
    ifb_macro_assert(ptr_hash_table);
    IFBB8 result = true;
    result &= (key     != NULL);
    result &= (element != NULL);
    if (!result) return(false);

    //hash the key
    const IFBU32  key_lengh_max = ptr_hash_table->key_length_max;
    const IFBHash key_hash      = ifb_hash::get_hash(key,key_lengh_max);

    //if the hash doesn't have a value, we're done
    result &= !ifb_hash::hash_is_clear(key_hash);
    if (!result) return(false);

    //get the hash array info
    IFBU32 hash_index = 0;
    const IFBU32 hash_array_size = ptr_hash_table->element_count_max;
    IFBHash*     hash_array_ptr  = ifb_hash_table::get_hash_array(ptr_hash_table);
    
    //TODO(SAM): we can probably consolidate these loops

    //search for a clear value
    result &= ifb_hash::find_next_clear_value(
        hash_array_ptr,
        hash_array_size,
        hash_index);

    //if we don't have one, we're done
    return(false);

    //check for collisions
    const IFBB8 collision = ifb_hash::collision_check(
        hash_array_ptr,
        hash_array_size,  
        key_hash);

    //this should NEVER happen
    ifb_macro_assert(!collision);

    //set the hash at the index
    hash_array_ptr[hash_index] = key_hash;

    //get the element destination
    const IFBU32  element_size   = ptr_hash_table->element_size;
    const IFBU32  element_offset = element_size * hash_index;
    const IFBAddr element_start  =  ptr_hash_table->element_array_start + element_offset;
    IFBByte* element_destination = (IFBByte*)element_start; 


    //we're done
    return(result);
}

const IFBByte*
ifb_hash_table::lookup(
    const IFBHashTable* ptr_hash_table,
    const IFBChar*      key) {

}

//count
const IFBU32   ifb_hash_table::get_count_total          (const IFBHashTable* ptr_hash_table);
const IFBU32   ifb_hash_table::get_count_free           (const IFBHashTable* ptr_hash_table);
const IFBU32   ifb_hash_table::get_count_used           (const IFBHashTable* ptr_hash_table);


/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBHash*
ifb_hash::get_hash_array(
    const IFBHashTable* ptr_hash_table) {

    IFBHash* hash_array = (IFBHash*)ptr_hash_table->data_start;
    ifb_macro_assert(hash_array);
    return(hash_array);
}
