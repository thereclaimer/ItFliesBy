#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_u32 
ifb_engine::memory_arena_commit(
    const ifb_cstr arena_tag,
    const ifb_u32  arena_size_minimum) {

    //get the memory manager
    IFBEngineMemoryManager* memory_manager_ptr = ifb_engine::memory_manager_pointer_from_context();

    //make sure we can commit
    if (memory_manager_ptr->arena_count_used == memory_manager_ptr->arena_count_total) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    }

    //get the arena table
    IFBEngineTableArena arena_table;
    if (!ifb_engine::table_arena(arena_table)) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    }


    //get the arena index
    const ifb_u32 arena_index = arena_table_ptr->arena_count_used;
    
    //create the tag
    ifb_u32 arena_tag_index;
    if (!ifb_engine::tag_create(arena_tag,arena_tag_index)) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    } 

    //do the commit
    const ifb_u32 arena_page_count = ifb_engine::memory_page_count(arena_size_minimum);
    const ifb_u32 arena_page_start = ifb_engine::memory_page_commit(arena_page_count);


    //sanity check
    if (arena_page_start == 0) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    }

    //update the table
    ifb_engine::arena_table_update_arena(
        arena_table_ptr,
        arena_index,
        arena_tag_index,
        arena_page_start,
        arena_page_count);

    //we're done
    return(arena_index);
}

ifb_api const ifb_b8
ifb_engine::memory_arena_valid(
    const ifb_u32 arena_index) {

    return(arena_index < IFB_ENGINE_MEMORY_ARENA_COUNT_MAX);
}

ifb_api const ifb_u32
ifb_engine::memory_arena_handle(
    const ifb_u32 arena_index,
    const ifb_u32 offset) {

    //get the table
    IFBEngineArenaTable* arena_table_ptr = ifb_engine::memory_manager_get_arena_table();

    //get the column memory    
    const ifb_u32* page_start_ptr = ifb_engine::arena_table_column_memory_page_start(arena_table_ptr);
    const ifb_u32* page_count_ptr = ifb_engine::arena_table_column_memory_page_count(arena_table_ptr);

    //get the page info
    const ifb_u32  page_start     = page_start_ptr[arena_index]; 
    const ifb_u32  page_count     = page_count_ptr[arena_index]; 

    //get the arena size
    const ifb_u32 arena_size = ifb_engine::memory_page_size(page_count); 

    //if the offset is within the arena, return the handle
    //if not, we return invalid handle
    const ifb_u32 arena_memory_handle = 
        (offset < arena_size) 
            ? ifb_engine::memory_handle(page_start,offset)
            : IFB_ENGINE_MEMORY_HANDLE_INVALID;

    //we're done
    return(arena_memory_handle);
}

ifb_api const ifb_u32 
ifb_engine::memory_arena_page_start(
    const ifb_u32 arena_index) {

    IFBEngineArenaTable* arena_table_ptr = ifb_engine::memory_manager_get_arena_table();

    const ifb_u32* page_start_ptr = ifb_engine::arena_table_column_memory_page_start(arena_table_ptr);
    const ifb_u32  page_start     = page_start_ptr[arena_index]; 

    return(page_start);
}

ifb_api const ifb_u32 
ifb_engine::memory_arena_page_count(
    const ifb_u32 arena_index) {

    IFBEngineArenaTable* arena_table_ptr = ifb_engine::memory_manager_get_arena_table();

    const ifb_u32* page_count_ptr = ifb_engine::arena_table_column_memory_page_count(arena_table_ptr);
    const ifb_u32  page_count     = page_count_ptr[arena_index]; 

    return(page_count);
}

ifb_api const ifb_u32
ifb_engine::memory_arena_tag_index(
    const ifb_u32 arena_index) {

    IFBEngineArenaTable* arena_table_ptr = ifb_engine::memory_manager_get_arena_table();
    
    const ifb_u32* tag_index_ptr = ifb_engine::arena_table_column_memory_tag(arena_table_ptr);
    const ifb_u32  tag_index     = tag_index_ptr[arena_index];

    return(tag_index);
}

ifb_api const ifb_cstr 
ifb_engine::memory_arena_tag_value(
    const ifb_u32 arena_index) {

    IFBEngineArenaTable* arena_table_ptr = ifb_engine::memory_manager_get_arena_table();
    
    const ifb_u32* tag_index_ptr = ifb_engine::arena_table_column_memory_tag(arena_table_ptr);
    const ifb_u32  tag_index     = tag_index_ptr[arena_index];

    const ifb_cstr tag_value = ifb_engine::tag_value(tag_index);

    return(tag_value);
}