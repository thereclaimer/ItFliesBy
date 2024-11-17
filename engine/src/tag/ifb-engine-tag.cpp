#pragma once

#include "ifb-engine-internal-tag.hpp"
#include "ifb-engine-internal.hpp"

ifb_api const ifb_b8
ifb_engine::tag_create(
    const ifb_cstr  in_tag_value, 
          ifb_u32& out_tag_index_ref) {

    //sanity check
    if (!in_tag_value) {
        return(false);
    }
    
    ifb_b8 result = true;

    //hash the value
    IFBEngineHashValue tag_hash;
    const ifb_u32 tag_length = ifb_engine::hash_cstr(in_tag_value,IFB_ENGINE_TAG_LENGTH,tag_hash);
    if (tag_length == 0) {
        return(false);
    }

    //get the table
    const ifb_u32        tag_manager_handle = ifb_engine::core_manager_handle_tag();
    IFBEngineTagManager* tag_manager_ptr    = ifb_engine::tag_manager_from_handle(tag_manager_handle); 

    //get the hash memory
    IFBEngineHashValue* tag_hash_array_ptr = ifb_engine::tag_manager_memory_hashes(tag_manager_ptr);

    //collision check
    if(
        ifb_engine::hash_collision_check(
            tag_hash,
            tag_hash_array_ptr,
            IFB_ENGINE_TAG_COUNT_MAX)) {

        //if we have a collision, we're done
        return(false);
    }

    //find the next available index
    ifb_u32 tag_index;
    if (
        !ifb_engine::hash_next_clear_value(
            tag_hash_array_ptr,
            IFB_ENGINE_TAG_COUNT_MAX,
            tag_index)) {

        //if we don't have an available index, we're done
        return(false);
    }

    //get the value memory
    ifb_char* tag_value_array_ptr = ifb_engine::tag_manager_memory_values(tag_manager_ptr);

    //copy the tag value
    const ifb_u32 tag_value_array_index = tag_index * IFB_ENGINE_TAG_LENGTH;
    for (
        ifb_u32 char_index = 0;
                char_index < tag_length;
              ++char_index) {

        tag_value_array_ptr[tag_value_array_index + char_index] = in_tag_value[char_index]; 
    }

    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::tag_index(
    const ifb_cstr  in_tag_value, 
          ifb_u32& out_tag_index_ref) {

    //get the table
    IFBEngineTagManager* tag_manager_ptr = ifb_engine::tag_manager_from_context();

    //get the hash values
    const IFBEngineHashValue* tag_hash_value_ptr = ifb_engine::tag_manager_memory_hashes(tag_manager_ptr);

    //hash the input value
    IFBEngineHashValue hash_value;
    const ifb_u32 hash_value_length = ifb_engine::hash_cstr(
        in_tag_value,
        IFB_ENGINE_TAG_LENGTH,
        hash_value);

    //if that didn't work, we're done
    if (hash_value_length == 0) {
        return(false);
    }

    //search for the index
    ifb_b8 result = ifb_engine::hash_search(
        hash_value,
        tag_hash_value_ptr,
        IFB_ENGINE_TAG_COUNT_MAX,
        out_tag_index_ref);

    //we're done
    return(result);
}

ifb_api const ifb_b8
ifb_engine::tag_destroy(
    const ifb_u32 tag_index) {

    //sanity check
    if (tag_index >= IFB_ENGINE_TAG_COUNT_MAX) {
        return(NULL);
    }

    //get the table
    IFBEngineTagManager* tag_manager_ptr = ifb_engine::tag_manager_from_context();

    //get the table memory
    ifb_char*           tag_values_ptr  = ifb_engine::tag_manager_memory_values(tag_manager_ptr);
    IFBEngineHashValue* hash_values_ptr = ifb_engine::tag_manager_memory_hashes(tag_manager_ptr);

    //clear the hash value
    hash_values_ptr[tag_index].h1 = 0;
    hash_values_ptr[tag_index].h2 = 0;
    hash_values_ptr[tag_index].h3 = 0;
    hash_values_ptr[tag_index].h4 = 0;

    //clear the tag value
    const ifb_u32 char_index_start = tag_index        * IFB_ENGINE_TAG_LENGTH;
    const ifb_u32 char_index_end   = char_index_start + IFB_ENGINE_TAG_LENGTH;
    for (
        ifb_u32 char_index = char_index_start;
                char_index < char_index_end;
              ++char_index) {

        tag_values_ptr[char_index] = 0;
    }

    //we're done
    return(true);
}

ifb_api const ifb_cstr
ifb_engine::tag_value(
    const ifb_u32 tag_index) {

    //sanity check
    if (tag_index >= IFB_ENGINE_TAG_COUNT_MAX) {
        return(NULL);
    }

    //get the table
    IFBEngineTagManager* tag_manager_ptr = ifb_engine::tag_manager_from_context();

    //get the values
    const ifb_char* tag_values_ptr = ifb_engine::tag_manager_memory_values(tag_manager_ptr);

    //calculate the starting index for this tag
    const ifb_u32 tag_char_index = tag_index * IFB_ENGINE_TAG_LENGTH;

    //get the pointer to this tag value
    const ifb_cstr tag_value = (const ifb_cstr)&tag_values_ptr[tag_char_index]; 

    //we're done
    return(tag_value);
}

inline IFBEngineTagManager* 
ifb_engine::tag_manager_from_handle(
    const ifb_u32 tag_manager_handle) {

    IFBEngineTagManager* tag_manager_ptr = (IFBEngineTagManager*)ifb_engine::memory_pointer_from_handle(tag_manager_handle);

    return(tag_manager_ptr);
}

inline IFBEngineTagManager* 
ifb_engine::tag_manager_from_context(
    ifb_void) {

    const ifb_u32 tag_manager_handle = ifb_engine::core_manager_handle_tag();

    IFBEngineTagManager* tag_manager_ptr = (IFBEngineTagManager*)ifb_engine::memory_pointer_from_handle(tag_manager_handle);

    return(tag_manager_ptr);
}

inline ifb_char* 
ifb_engine::tag_manager_memory_values(
    IFBEngineTagManager* tag_manager_ptr) {

    ifb_char* tag_values_ptr = (ifb_char*)ifb_engine::memory_pointer_from_handle(tag_manager_ptr->handle_tag_buffer);

    return(tag_values_ptr);
}

inline IFBEngineHashValue* 
ifb_engine::tag_manager_memory_hashes(
    IFBEngineTagManager* tag_manager_ptr) {

    IFBEngineHashValue* hash_values_ptr = (IFBEngineHashValue*)ifb_engine::memory_pointer_from_handle(tag_manager_ptr->handle_hash_values);

    return(hash_values_ptr);
}

inline const ifb_u32 
ifb_engine::tag_manager_create(
    ifb_void) {

    //calculate sizes
    const ifb_u32 tag_count_max         = IFB_ENGINE_TAG_COUNT_MAX;
    const ifb_u32 tag_value_size        = IFB_ENGINE_TAG_LENGTH;
    const ifb_u32 tag_hash_size         = sizeof(IFBEngineHashValue);
    const ifb_u32 tag_manager_size        = ifb_engine_macro_align_size_struct(IFBEngineTagManager);
    const ifb_u32 tag_value_buffer_size = tag_value_size * tag_count_max;
    const ifb_u32 tag_hash_buffer_size  = tag_hash_size  * tag_count_max;  

    //calculate page counts
    const ifb_u32 page_count_tag_manager        = ifb_engine::memory_page_count(tag_manager_size);
    const ifb_u32 page_count_tag_value_buffer = ifb_engine::memory_page_count(tag_value_buffer_size);
    const ifb_u32 page_count_tag_hash_buffer  = ifb_engine::memory_page_count(tag_hash_buffer_size);

    //commit pages
    const ifb_u32 page_start_tag_manager        = ifb_engine::memory_page_commit(page_count_tag_manager);
    const ifb_u32 page_start_tag_value_buffer = ifb_engine::memory_page_commit(page_count_tag_value_buffer);
    const ifb_u32 page_start_tag_hash_buffer  = ifb_engine::memory_page_commit(page_count_tag_hash_buffer);

    //create handles
    const ifb_u32 handle_tag_manager        = ifb_engine::memory_handle(page_start_tag_manager,       0); 
    const ifb_u32 handle_tag_value_buffer = ifb_engine::memory_handle(page_start_tag_value_buffer,0); 
    const ifb_u32 handle_tag_hash_buffer  = ifb_engine::memory_handle(page_start_tag_hash_buffer, 0); 

    //initialize the table
    IFBEngineTagManager* tag_manager_ptr = ifb_engine::tag_manager_from_handle(handle_tag_manager);
    tag_manager_ptr->tag_count_max      = tag_count_max;
    tag_manager_ptr->handle_tag_buffer  = handle_tag_value_buffer;
    tag_manager_ptr->handle_hash_values = handle_tag_hash_buffer;

    //clear all the memory
    ifb_char*           tag_manager_memory_values_ptr = ifb_engine::tag_manager_memory_values(tag_manager_ptr);
    IFBEngineHashValue* tag_manager_memory_hashes_ptr = ifb_engine::tag_manager_memory_hashes(tag_manager_ptr);

    for (
        ifb_u32 tag_index = 0;
        tag_index < tag_count_max;
        ++tag_index) {

        //clear the hash value
        tag_manager_memory_hashes_ptr[tag_index].h1 = 0;
        tag_manager_memory_hashes_ptr[tag_index].h2 = 0;
        tag_manager_memory_hashes_ptr[tag_index].h3 = 0;
        tag_manager_memory_hashes_ptr[tag_index].h4 = 0;

        //clear the tag
        const ifb_u32 value_start = tag_value_size * tag_index; 
        const ifb_u32 value_end   = value_start + tag_value_size;
        for (
            ifb_u32 char_index = value_start;
            char_index < value_end; 
            ++char_index) {

            tag_manager_memory_values_ptr[char_index] = 0;
        }
    }

    //we're done
    return(handle_tag_manager);
}