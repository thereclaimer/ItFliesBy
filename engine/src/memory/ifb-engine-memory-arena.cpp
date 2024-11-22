#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-tables.hpp"
#include "ifb-engine-internal-controllers.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::memory_arena_commit(
    const ifb_cstr             in_arena_tag,
    const ifb_u32              in_arena_size_minimum,
            IFBEngineArenaId& out_arena_id_ref) {

    //get the memory manager
    IFBEngineMemoryManager* memory_manager_ptr = ifb_engine::memory_manager_pointer_from_context();

    //make sure we can commit
    if (memory_manager_ptr->arena_count_used == memory_manager_ptr->arena_count_total) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    }

    //get the memory manager
    const ifb_u32 arena_index = memory_manager_ptr->arena_count_used;
    
    //create the tag
    IFBEngineTagId arena_tag_id;
    if (!ifb_engine::tag_create(in_arena_tag,arena_tag_id)) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    } 

    //do the commit
    const ifb_u32 arena_page_count = ifb_engine::memory_page_count(in_arena_size_minimum);
    const ifb_u32 arena_page_start = ifb_engine::memory_page_commit(arena_page_count);

    //sanity check
    if (arena_page_start == 0) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    }

    //get the arena table
    IFBEngineTableArena arena_table;
    ifb_engine::table_arena(arena_table);
    

    //update the table
    arena_table.column_ptrs.page_start [arena_index] = arena_page_start;
    arena_table.column_ptrs.page_count [arena_index] = arena_page_count;
    arena_table.column_ptrs.tag_id     [arena_index] = arena_tag_id;

    //update the manager
    ++memory_manager_ptr->arena_count_used;

    //update the id
    out_arena_id_ref.arena_table_index = arena_index;

    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::memory_arena_valid(
    const IFBEngineArenaId arena_id) {

    return(arena_id.arena_table_index < IFB_ENGINE_MEMORY_ARENA_COUNT_MAX);
}

ifb_api const ifb_u32
ifb_engine::memory_arena_handle(
    const IFBEngineArenaId arena_id,
    const ifb_u32          offset) {

    //get the arena table
    IFBEngineTableArena arena_table;
    ifb_engine::table_arena(arena_table);

    //get the page info
    const ifb_u32 page_start = arena_table.column_ptrs.page_start[arena_id.arena_table_index]; 
    const ifb_u32 page_count = arena_table.column_ptrs.page_count[arena_id.arena_table_index]; 

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
    const IFBEngineArenaId arena_id) {

    //get the arena table
    IFBEngineTableArena arena_table;
    ifb_engine::table_arena(arena_table);

    const ifb_u32 page_start = arena_table.column_ptrs.page_start[arena_id.arena_table_index]; 

    return(page_start);
}

ifb_api const ifb_u32 
ifb_engine::memory_arena_page_count(
    const IFBEngineArenaId arena_id) {

    //get the arena table
    IFBEngineTableArena arena_table;
    ifb_engine::table_arena(arena_table);

    const ifb_u32 page_count = arena_table.column_ptrs.page_count[arena_id.arena_table_index]; 

    return(page_count);
}

ifb_api const IFBEngineTagId
ifb_engine::memory_arena_tag_id(
    const IFBEngineArenaId arena_id) {

    //get the arena table
    IFBEngineTableArena arena_table;
    ifb_engine::table_arena(arena_table);

    const IFBEngineTagId tag_id = arena_table.column_ptrs.tag_id[arena_id.arena_table_index]; 

    return(tag_id);
}

ifb_api const ifb_cstr 
ifb_engine::memory_arena_tag_value(
    const IFBEngineArenaId arena_id) {

    //get the tables
    IFBEngineTableArena arena_table;
    IFBEngineTableTag   tag_table;
    ifb_engine::table_arena(arena_table);
    ifb_engine::table_tag  (tag_table);

    //get the tag index    
    const IFBEngineTagId tag_id = arena_table.column_ptrs.tag_id[arena_id.arena_table_index];

    //get the tag value
    const ifb_cstr tag_cstr = ifb_engine::controller_tag_cstr_value(tag_id); 

    //we're done
    return(tag_cstr);
}