#include "ifb-engine-internal-controllers.hpp"
#include "ifb-engine-internal-tables.hpp"

inline const ifb_u32 
ifb_engine::controller_arena_page_start(
          IFBEngineCore*   engine_core_ptr,
    const IFBEngineArenaId arena_id) {

    //get the table
    IFBEngineTableArena* arena_table = ifb_engine::core_table_arena(engine_core_ptr);

    //get page start
    const ifb_u32 arena_page_start = ifb_engine::table_arena_read_page_start(arena_table,arena_id.table_indexes.arena);

    //we're done
    return(arena_page_start);
}

inline const ifb_u32 
ifb_engine::controller_arena_page_count(
          IFBEngineCore*   engine_core_ptr,
    const IFBEngineArenaId arena_id) {

    //get the table
    IFBEngineTableArena* arena_table = ifb_engine::core_table_arena(engine_core_ptr);

    //get page count
    const ifb_u32 arena_page_count = ifb_engine::table_arena_read_page_count(arena_table,arena_id.table_indexes.arena);

    //we're done
    return(arena_page_count);
}

inline const ifb_cstr 
ifb_engine::controller_arena_tag_value(
          IFBEngineCore*   engine_core_ptr,
    const IFBEngineArenaId arena_id) {

    //get the table
    IFBEngineTableTag* tag_table = ifb_engine::core_table_tag(engine_core_ptr);

    //get the tag value
    const ifb_cstr arena_tag_value = ifb_engine::table_tag_read_value(tag_table,arena_id.table_indexes.tag);

    //we're done
    return(arena_tag_value);
}

inline ifb_void 
ifb_engine::controller_arena(
    IFBEngineCore*  engine_core_ptr,
    IFBEngineArena& arena_ref) {

    //get the tables
    IFBEngineTableArena* arena_table = ifb_engine::core_table_arena(engine_core_ptr);
    IFBEngineTableTag*   tag_table   = ifb_engine::core_table_tag(engine_core_ptr);

    //cache the indexes
    const IFBEngineTableIndexTag     tag_index = arena_ref.arena_id.table_indexes.tag;
    const IFBEngineTableIndexArena arena_index = arena_ref.arena_id.table_indexes.arena;

    //read from the tables
    arena_ref.page_start = ifb_engine::table_arena_read_page_start(arena_table, arena_index);
    arena_ref.page_count = ifb_engine::table_arena_read_page_count(arena_table, arena_index);
    arena_ref.tag_value  = ifb_engine::table_tag_read_value       (tag_table,   tag_index);
    
    //get the other info
    arena_ref.memory_size   = ifb_engine::memory_page_size (arena_ref.page_count);
    arena_ref.memory_handle = ifb_engine::memory_handle    (arena_ref.page_start,0);
}

inline const IFBEngineMemoryHandle
ifb_engine::controller_arena_handle(
          IFBEngineCore*   engine_core_ptr,
    const IFBEngineArenaId arena_id,
    const ifb_u32          offset) {

    //get the table
    IFBEngineTableArena* arena_table = ifb_engine::core_table_arena(engine_core_ptr);

    //get the starting page of the arena    
    const ifb_u32 page_start = ifb_engine::table_arena_read_page_start(arena_table, arena_id.table_indexes.arena);

    //get the memory at the offset of the page
    const IFBEngineMemoryHandle arena_memory = ifb_engine::memory_handle(page_start,offset);

    //we're done
    return(arena_memory);
}

inline const IFBEngineArenaId 
ifb_engine::controller_arena_commit(
          IFBEngineCore* engine_core_ptr,
    const ifb_cstr       arena_tag_value,
    const ifb_u32        arena_size_minimum) {
    
    IFBEngineArenaId arena_id = {0};
    ifb_b8           result   = true;

    //get the tables
    IFBEngineTableArena* arena_table = ifb_engine::core_table_arena(engine_core_ptr);
    IFBEngineTableTag*   tag_table   = ifb_engine::core_table_tag(engine_core_ptr);

    //do the commit
    const IFBEngineMemoryCommit memory = ifb_engine::memory_commit(arena_size_minimum);

    //create the tag
    arena_id.table_indexes.tag = ifb_engine::table_tag_insert(
        tag_table,
        arena_tag_value);
    
    //create the arena
    arena_id.table_indexes.arena = ifb_engine::table_arena_insert(
        arena_table,
        memory.page_start,
        memory.page_count,
        arena_id.table_indexes.tag);

    //we're done
    return(arena_id);
}