#pragma once

#include "ifb-engine-table-manager.cpp"

inline IFBEngineTableArena*
ifb_engine::table_arena(
    const IFBEngineTableHandleArena table_handle_arena) {

    const IFBEngineTableArena* arena_table_ptr = ifb_engine::memory_pointer_from_handle(table_handle_arena);

    return(arena_table_ptr);
}


inline IFBEngineTableTag*
ifb_engine::table_tag(
    const IFBEngineTableHandleTag table_handle_tag) {

    const IFBEngineTableTag* tag_table_ptr = ifb_engine::memory_pointer_from_handle(table_handle_tag);

    return(tag_table_ptr);
}
