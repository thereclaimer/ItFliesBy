#pragma once

#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-core.hpp"

ifb_internal const ifb_b8
ifb_engine::asset_data_table_create(
    const ifb_size                  in_data_table_arena_size,
    const ifb_size                  in_data_table_arena_count,
          IFBEngineAssetDataTable& out_data_table_ref) {

    //create a region for the data table
    out_data_table_ref.region_handle = ifb_engine::core_memory_create_arena_pool(
        "ASSET DATA",
        in_data_table_arena_size,
        in_data_table_arena_count);
    
    //allocate the table columns
    out_data_table_ref.columns.arena                 = ifb_engine_core_memory_push_array(in_data_table_arena_count, RHNDMemoryArena);
    out_data_table_ref.columns.asset_id              = ifb_engine_core_memory_push_array(in_data_table_arena_count, IFBEngineAssetId); 
    out_data_table_ref.columns.time_ms_loaded        = ifb_engine_core_memory_push_array(in_data_table_arena_count, ifb_timems); 
    out_data_table_ref.columns.time_ms_last_accessed = ifb_engine_core_memory_push_array(in_data_table_arena_count, ifb_timems); 
    out_data_table_ref.columns.data_block            = ifb_engine_core_memory_push_array(in_data_table_arena_count, IFBEngineAssetDataBlock);

    //sanity check, make sure we got our memory
    const ifb_b8 result = (
        out_data_table_ref.region_handle                 != NULL ||
        out_data_table_ref.columns.arena                 != NULL ||
        out_data_table_ref.columns.asset_id              != NULL ||
        out_data_table_ref.columns.time_ms_loaded        != NULL ||
        out_data_table_ref.columns.time_ms_last_accessed != NULL ||
        out_data_table_ref.columns.data_block            != NULL);

    //we're done
    return(result);
}