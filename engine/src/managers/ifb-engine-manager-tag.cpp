#pragma once

#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-global.hpp"
#include "ifb-engine-internal-core.hpp"

inline const IFBEngineGlobalHandleTagManager 
ifb_engine::tag_manager_create(
          IFBEngineMemory* ptr_engine_memory,
    const ifb_u32          tag_c_str_length,
    const ifb_u32          tag_count_max) {

    //globally allocate the tag manager
    IFBEngineGlobalHandleTagManager tag_manager_handle;
    ifb_engine_global_stack_push_type(tag_manager_handle,IFBEngineTagManager);

    //calculate the commit size for the arrays
    const ifb_u32 char_buffer_size = ifb_macro_size_array(ifb_char, tag_count_max);
    const ifb_u32 hash_array_size  = ifb_macro_size_array(IFBHash,  tag_count_max);
    const ifb_u32 commit_size      = char_buffer_size + hash_array_size; 

    //do the commit
    const IFBCommitId commit_id = ifb_engine::memory_commit(ptr_engine_memory,commit_size);

    //set the properties
    IFBEngineTagManager* ptr_tag_manager = (IFBEngineTagManager*)ifb_engine::global_stack_get_pointer(tag_manager_handle);
    ptr_tag_manager->commit_id                  = commit_id; 
    ptr_tag_manager->tag_c_str_length           = tag_c_str_length; 
    ptr_tag_manager->tag_count_max              = tag_count_max; 
    ptr_tag_manager->commit_offsets.char_buffer = 0; 
    ptr_tag_manager->commit_offsets.hash_array  = char_buffer_size; 

    //we're done
    return(tag_manager_handle);
}

inline const IFBTagId
ifb_engine::tag_manager_reserve_tag(
          IFBEngineTagManager* ptr_tag_manager,
    const IFBEngineMemory*     ptr_engine_memory,
    const ifb_cstr             tag_c_str) {

    //cache constants
    const ifb_u32 tag_c_str_length = ptr_tag_manager->tag_c_str_length;
    const ifb_u32 tag_count        = ptr_tag_manager->tag_count_max;

    //get the hash array
    IFBHash* ptr_tag_manager_hash_array = ifb_engine::tag_manager_get_pointer_hash_array(
        ptr_tag_manager,
        ptr_engine_memory);

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

    //get the char buffer
    const ifb_char* ptr_tag_manager_char_buffer = ifb_engine::tag_manager_get_pointer_hash_array(
        ptr_tag_manager,
        ptr_engine_memory);
    
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
          IFBEngineTagManager* ptr_tag_manager,
    const IFBEngineMemory*     ptr_engine_memory,
    const IFBTagId             tag_id) {

    //get the hash array
    IFBHash* ptr_tag_manager_hash_array = ifb_engine::tag_manager_get_pointer_hash_array(
        ptr_tag_manager,
        ptr_engine_memory);

    //clear the value
    ptr_tag_manager_hash_array[tag_id.index] = {0};
}

inline const ifb_cstr
ifb_engine::tag_manager_get_tag_c_str(
          IFBEngineTagManager* ptr_tag_manager,
    const IFBEngineMemory*     ptr_engine_memory,
    const IFBTagId             tag_id) {

    //get the char buffer
    const ifb_char* ptr_tag_manager_char_buffer = ifb_engine::tag_manager_get_pointer_hash_array(
        ptr_tag_manager,
        ptr_engine_memory);
    
    //get the start of the tag
    const ifb_cstr tag_c_str = ptr_tag_manager_char_buffer[tag_id.index * ptr_tag_manager->tag_c_str_length];

    //we're done
    return(tag_c_str);
}

inline const IFBHash
ifb_engine::tag_manager_get_hash(
          IFBEngineTagManager* ptr_tag_manager,
    const IFBEngineMemory*     ptr_engine_memory,
    const IFBTagId             tag_id) {

    //get the hash array
    IFBHash* ptr_tag_manager_hash_array = ifb_engine::tag_manager_get_pointer_hash_array(
        ptr_tag_manager,
        ptr_engine_memory);

    //get the hash
    const IFBHash tag_hash = ptr_tag_manager_hash_array[tag_id.index];

    //we're done
    return(tag_hash);
}

inline ifb_char*
ifb_engine::tag_manager_get_pointer_char_buffer(
          IFBEngineTagManager* ptr_tag_manager,
    const IFBEngineMemory*     ptr_engine_memory) {

    ifb_char* char_buffer = (ifb_char*)ifb_engine::memory_get_commit_pointer(
        ptr_engine_memory,
        ptr_tag_manager->commit_id,
        ptr_tag_manager->commit_offsets.char_buffer);
    
    return(char_buffer);
}

inline IFBHash*
ifb_engine::tag_manager_get_pointer_hash_array(
          IFBEngineTagManager* ptr_tag_manager,
    const IFBEngineMemory*     ptr_engine_memory) {

    IFBHash* hash_array = (IFBHash*)ifb_engine::memory_get_commit_pointer(
        ptr_engine_memory,
        ptr_tag_manager->commit_id,
        ptr_tag_manager->commit_offsets.hash_array);
    
    return(hash_array);
}