#pragma once

#include "ifb-engine-internal-tables.hpp"

inline const IFBEngineTableHandleArena
ifb_engine::table_arena_create(
    const IFBEngineTableAllocatorHandle table_allocator_handle) {

     IFBEngineTableHandleArena arena_table_handle = {0};

    return(arena_table_handle);
}

inline const ifb_u32
ifb_engine::table_arena_read_page_start(
    const IFBEngineTableHandleArena arena_table_handle,
    const IFBEngineTableIndexArena  arena_index) {

    return(0);
}

inline const ifb_u32
ifb_engine::table_arena_read_page_count(
    const IFBEngineTableHandleArena arena_table_handle,
    const IFBEngineTableIndexArena  arena_index) {

    return(0);
}

inline const IFBEngineTableIndexTag
ifb_engine::table_arena_read_tag_index(
    const IFBEngineTableHandleArena arena_table_handle,
    const IFBEngineTableIndexArena  arena_index) {

    return({0});
}

inline const ifb_b8
ifb_engine::table_arena_insert(
    const IFBEngineTableHandleArena  in_arena_table_handle,
    const ifb_u32                    in_arena_page_start,
    const ifb_u32                    in_arena_page_count,
    const IFBEngineTableIndexTag     in_arena_tag_index,
            IFBEngineTableIndexArena& out_arena_table_index) {

    return(false);
}

inline IFBEngineTableArena* 
ifb_engine::table_arena(
    const IFBEngineTableHandleArena table_handle_arena) {

    return(NULL);
}