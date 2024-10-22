#pragma once

#include "ifb-engine-internal-asset.hpp"

ifb_internal const ifb_b8 
ifb_engine::asset_data_block_create_table(
    IFBEngineCoreMemory&           in_engine_core_memory_ref,
    IFBEngineAssetTableDataBlock& out_asset_table_data_block_ref) {

    const ifb_size data_block_size  = IFB_ENGINE_ASSET_DATA_BLOCK_SIZE;
    const ifb_size data_block_count = IFB_ENGINE_ASSET_DATA_BLOCK_COUNT;

    //create the region
    const RMemoryRegionHandle region_handle = 
        ifb_engine::core_memory_create_arena_pool(
            in_engine_core_memory_ref,
            "ASSET DATA BLOCK",
            data_block_size,
            data_block_count);

    //allocate the memory
    IFBEngineAssetTableIndexHeader* ptr_header_index  = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,data_block_count,IFBEngineAssetTableIndexHeader);
    ifb_timems*                     ptr_time_loaded   = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,data_block_count,ifb_timems);
    ifb_timems*                     ptr_time_accessed = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,data_block_count,ifb_timems);
    RMemoryArenaHandle*             ptr_arena_handle  = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,data_block_count,RMemoryArenaHandle);
    
    //sanity check
    const ifb_b8 result = (
        region_handle     &&
        ptr_header_index  &&
        ptr_time_loaded   &&
        ptr_time_accessed &&
        ptr_arena_handle);

    //initialize the data
    for (
        IFBEngineAssetTableIndexDataBlock data_block_index = 0;
        data_block_index < data_block_count;
        ++data_block_index) {

        ptr_header_index [data_block_index] = IFB_ENGINE_ASSET_HEADER_INDEX_INVALID;
        ptr_time_loaded  [data_block_index] = 0;
        ptr_time_accessed[data_block_index] = 0;
        ptr_arena_handle [data_block_index] = NULL;
    }

    //initialize the table
    out_asset_table_data_block_ref.region_handle                        = region_handle;
    out_asset_table_data_block_ref.data_block_count                     = data_block_count;
    out_asset_table_data_block_ref.columns.ptr_asset_table_index_header = ptr_header_index;
    out_asset_table_data_block_ref.columns.ptr_time_ms_loaded           = ptr_time_loaded;
    out_asset_table_data_block_ref.columns.ptr_time_ms_last_accessed    = ptr_time_accessed;
    out_asset_table_data_block_ref.columns.ptr_asset_data_arena_handle  = ptr_arena_handle;

    //we're done
    return(result);
}