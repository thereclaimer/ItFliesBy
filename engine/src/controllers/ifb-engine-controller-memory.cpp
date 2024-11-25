#include "ifb-engine-internal-controllers.hpp"

const ifb_u32 
ifb_engine::controller_memory_arena_page_start(
    const IFBEngineArenaId arena_id) {

}
const ifb_u32 
ifb_engine::controller_memory_arena_page_count(
    const IFBEngineArenaId arena_id) {

}
const IFBEngineTagId 
ifb_engine::controller_memory_arena_tag_id(
    const IFBEngineArenaId arena_id) {

}

const ifb_b8 
ifb_engine::controller_memory_arena_create(
    const ifb_cstr             in_arena_tag_value,
    const ifb_u32              in_arena_size_minimum,
          IFBEngineArenaId&   out_arena_id) {
    
    IFBEngineTagId   tag_id   = {0};
    IFBEngineArenaId arena_id = {0};
    ifb_b8           result   = true;

    const IFBEngineTableHandleTag   table_handle_tag = ifb_engine::core_table_handle_tag();
    const IFBEngineTableHandleArena table_handle_tag = ifb_engine::core_table_handle_arena();

    result &= ifb_engine::table_tag_insert(table_handle_tag,in_arena_tag_value,tag_id);
    result &= ifb_engine::table_arena


}