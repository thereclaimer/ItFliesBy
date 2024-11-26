#include "ifb-engine-internal-controllers.hpp"

inline const ifb_u32 
ifb_engine::controller_arena_page_start(
    const IFBEngineArenaId arena_id) {

    //get the table
    const IFBEngineTableHandleArena table_handle_arena = ifb_engine::core_table_handle_arena();

    //get page start
    const ifb_u32 arena_page_start = ifb_engine::table_arena_read_page_start(arena_id.table_indexes.arena);

    //we're done
    return(arena_page_start);
}

inline const ifb_u32 
ifb_engine::controller_arena_page_count(
    const IFBEngineArenaId arena_id) {

    //get the table
    const IFBEngineTableHandleArena table_handle_arena = ifb_engine::core_table_handle_arena();

    //get page start
    const ifb_u32 arena_page_start = ifb_engine::table_arena_read_page_count(table_handle_arena,arena_id.table_indexes.arena); 

    //we're done
    return(page_start);
}

inline const ifb_cstr 
ifb_engine::controller_arena_tag_value(
    const IFBEngineArenaId arena_id) {

    //get the table
    const IFBEngineTableHandleTag table_handle_tag = ifb_engine::core_table_handle_tag();

    //get the tag value
    const ifb_cstr arena_tag_value = ifb_engine::table_tag_read_value(table_handle_tag,arena_id.table_indexes.tag);

    //we're done
    return(arena_tag_value);
}

inline ifb_void 
ifb_engine::controller_arena(
    IFBEngineArena& arena_ref) {

    //get the tables
    const IFBEngineTableHandleArena table_handle_arena = ifb_engine::core_table_handle_arena();
    const IFBEngineTableHandleTag   table_handle_tag   = ifb_engine::core_table_handle_tag();

    //cache the indexes
    const IFBEngineTableIndexTag     tag_index = arena_ref.arena_id.table_indexes.tag;
    const IFBEngineTableIndexArena arena_index = arena_ref.arena_id.table_indexes.arena;

    //read from the tables
    arena_ref.page_start    = ifb_engine::table_arena_read_page_start(table_handle_arena, arena_index);
    arena_ref.page_count    = ifb_engine::table_arena_read_page_count(table_handle_arena, arena_index);
    arena_ref.tag_value     = ifb_engine::table_tag_read_value       (table_handle_tag,   tag_index);
    
    //get the other info
    arena_ref.memory_size   = ifb_engine::memory_page_size (arena_ref.page_count);
    arena_ref.memory_handle = ifb_engine::memory_handle    (arena_ref.page_start,0);
}

inline const IFBEngineMemoryHandle
ifb_engine::controller_arena_handle(
    const IFBEngineArenaId arena_id,
    const ifb_u32          offset) {

    //get the table
    const IFBEngineTableHandleArena table_handle_arena = ifb_engine::core_table_handle_arena();

    //get the starting page of the arena    
    const ifb_u32 page_start = ifb_engine::table_arena_read_page_start(table_handle_arena, arena_index);

    //get the memory at the offset of the page
    const IFBEngineMemoryHandle arena_memory = ifb_engine::memory_handle(page_start,offset);

    //we're done
    return(arena_memory);
}

inline const IFBEngineArenaId 
ifb_engine::controller_arena_commit(
    const ifb_cstr             arena_tag_value,
    const ifb_u32              arena_size_minimum) {
    
    IFBEngineArenaId arena_id = {0};
    ifb_b8           result   = true;

    const IFBEngineTableHandleTag   table_handle_tag   = ifb_engine::core_table_handle_tag();
    const IFBEngineTableHandleArena table_handle_arena = ifb_engine::core_table_handle_arena();

    //get the memory manager
    IFBEngineMemoryManager* memory_manager_ptr = ifb_engine::memory_manager_pointer_from_context();

    //make sure we can commit
    result &= memory_manager_ptr->arena_count_used == memory_manager_ptr->arena_count_total;

    //do the commit
    IFBEngineMemoryCommit memory;
    result &= ifb_engine::memory_commit(in_arena_size_minimum,memory);

    //update the manager
    ++memory_manager_ptr->arena_count_used;

    //create the tag
    result &= ifb_engine::table_tag_insert(
        table_handle_tag,
        in_arena_tag_value,
        arena_id.table_indexes.tag);
    
    //create the arena
    result &= ifb_engine::table_arena_insert(
        table_handle_arena,
        memory.page_start,
        memory.page_count,
        tag_id.table_index,
        arena_id.table_indexes.arena);

    //santiy check
    ifb_macro_assert(result);

    //we're done
    return(arena_id);
}