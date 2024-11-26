#pragma once

#include "ifb-engine-internal-core.hpp"

inline IFBEngineTableTag*
ifb_engine::core_table_tag(
    const IFBEngineCore* engine_core_ptr) {

    IFBEngineTableTag* tag_table_ptr = ifb_engine::table_tag(engine_core_ptr->tables.tag);

    return(tag_table_ptr);
}

inline IFBEngineTableArena*
ifb_engine::core_table_arena(
    const IFBEngineCore* engine_core_ptr) {

    IFBEngineTableArena* arena_table_ptr = ifb_engine::table_arena(engine_core_ptr->tables.arena);
    
    return(arena_table_ptr);
}
