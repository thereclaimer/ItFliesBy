#pragma once

#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-global.hpp"
#include "ifb-engine-internal-context.hpp"

inline ifb_void 
ifb_engine::tag_manager_initialize(
          IFBEngineTagManager* tag_manager_ptr,
    const ifb_u32              tag_c_str_length,
    const ifb_u32              tag_count_max) {

    //calculate the commit size for the arrays
    const ifb_u32 char_buffer_size = ifb_macro_size_array(ifb_char, tag_count_max);
    const ifb_u32 hash_array_size  = ifb_macro_size_array(IFBHash,  tag_count_max);
    const ifb_u32 commit_size      = char_buffer_size + hash_array_size; 

    //do the commit
    IFBEngineMemory* engine_memory_ptr = ifb_engine::context_handles_get_memory();
    const IFBCommitId commit_id        = ifb_engine::memory_commit(engine_memory_ptr,commit_size);
    const ifb_address commit_start     = ifb_engine::memory_get_commit_address(engine_memory_ptr, commit_id);

    //set the properties
    tag_manager_ptr->tag_c_str_length           = tag_c_str_length; 
    tag_manager_ptr->tag_count_max              = tag_count_max; 
    tag_manager_ptr->commit.id                  = commit_id; 
    tag_manager_ptr->commit.start               = commit_start; 
    tag_manager_ptr->commit.offset_char_buffer  = 0; 
    tag_manager_ptr->commit.offset_hash_array   = char_buffer_size; 
}

inline const IFBIDTag
ifb_engine::tag_manager_reserve_tag(
          IFBEngineTagManager* tag_manager_ptr,
    const ifb_cstr             tag_c_str) {

    //cache constants
    const ifb_u32 tag_c_str_length = tag_manager_ptr->tag_c_str_length;
    const ifb_u32 tag_count        = tag_manager_ptr->tag_count_max;

    //get the pointers
    IFBHash*  ptr_tag_manager_hash_array  = ifb_engine::tag_manager_get_pointer_hash_array(tag_manager_ptr);
    ifb_char* ptr_tag_manager_char_buffer = ifb_engine::tag_manager_get_pointer_hash_array(tag_manager_ptr);

    //find the next available index
    IFBTagId tag_id;
    const ifb_b8 can_create_tag = ifb_common::hash_next_clear_value(
        ptr_tag_manager_hash_array,
        tag_count,
        tag_id.index);

    //santiy check
    ifb_macro_assert(can_create_tag);

    //hash the string and update the table
    ptr_tag_manager_hash_array[tag_id.index] = ifb_common::hash_cstr(
        tag_c_str,
        tag_c_str_length);

    //get the destination address of our new tag
    ifb_char* ptr_tag_c_str_destination = &ptr_tag_manager_char_buffer[tag_id.index * tag_c_str_length];
 
    //copy the tag value
    for (
        ifb_u32 char_index = 0;
                char_index < tag_c_str_length;
              ++char_index) {

        ptr_tag_c_str_destination[char_index] = tag_c_str[char_index];
    }

    //we're done
    return(tag_id);
}

inline ifb_void
ifb_engine::tag_manager_release_tag(
          IFBEngineTagManager* tag_manager_ptr,
    const IFBIDTag             tag_id) {

    //get the hash array
    IFBHash* tag_manager_hash_array_ptr = ifb_engine::tag_manager_get_pointer_hash_array(tag_manager_ptr);

    //clear the value
    tag_manager_hash_array_ptr[tag_id.index] = {0};
}

inline const ifb_cstr
ifb_engine::tag_manager_get_tag_c_str(
          IFBEngineTagManager* tag_manager_ptr,
    const IFBIDTag             tag_id) {

    //get the context memory
    IFBEngineMemory* engine_memory_ptr = ifb_engine::context_handles_get_memory();

    //get the char buffer
    const ifb_char* ptr_tag_manager_char_buffer = ifb_engine::tag_manager_get_pointer_hash_array(tag_manager_ptr);
    
    //get the start of the tag
    const ifb_cstr tag_c_str = ptr_tag_manager_char_buffer[tag_id.index * ptr_tag_manager->tag_c_str_length];

    //we're done
    return(tag_c_str);
}

inline const IFBHash
ifb_engine::tag_manager_get_hash(
          IFBEngineTagManager* ptr_tag_manager,
    const IFBIDTag             tag_id) {

    //get the hash array
    IFBHash* ptr_tag_manager_hash_array = ifb_engine::tag_manager_get_pointer_hash_array(ptr_tag_manager);

    //get the hash
    const IFBHash tag_hash = ptr_tag_manager_hash_array[tag_id.index];

    //we're done
    return(tag_hash);
}

inline ifb_char*
ifb_engine::tag_manager_get_pointer_char_buffer(
          IFBEngineTagManager* ptr_tag_manager,
    const IFBEngineMemory*     ptr_engine_memory) {

    const ifb_address commit_address      = ptr_tag_manager->commit.start;
    const ifb_address char_buffer_address = commit_address + ptr_tag_manager->commit.offset_char_buffer;
    ifb_char*         char_buffer_ptr     = (ifb_char*)char_buffer_address;     
    
    return(char_buffer);
}

inline IFBHash*
ifb_engine::tag_manager_get_pointer_hash_array(
          IFBEngineTagManager* ptr_tag_manager,
    const IFBEngineMemory*     ptr_engine_memory) {

    const ifb_address commit_address     = ptr_tag_manager->commit.start;
    const ifb_address hash_array_address = commit_address + ptr_tag_manager->commit.offset_hash_array;
    IFBHash*          hash_array_ptr     = (IFBHash*)hash_array_address;     

    return(hash_array_ptr);
}