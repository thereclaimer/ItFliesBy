#pragma once

#include "ifb-engine-internal-asset.hpp"

ifb_internal const ifb_b8 
ifb_engine::asset_data_block_table_create(
    IFBEngineAssetMemory&          in_asset_memory_ref,
    IFBEngineAssetTableDataBlock& out_asset_table_data_block_ref) {

    const ifb_size data_block_size  = IFB_ENGINE_ASSET_DATA_BLOCK_SIZE;
    const ifb_size data_block_count = IFB_ENGINE_ASSET_DATA_BLOCK_COUNT;

    //get the pointers
    IFBEngineAssetMemoryTableDataBlockPointers data_block_pointers;
    ifb_b8 result = ifb_engine::asset_memory_pointers_data_block_table(
        in_asset_memory_ref,
        data_block_pointers);

    //initialize the data
    for (
        IFBEngineAssetTableIndexDataBlock data_block_index = 0;
        data_block_index < data_block_count;
        ++data_block_index) {

        data_block_pointers.asset_table_index_header [data_block_index] = IFB_ENGINE_ASSET_HEADER_INDEX_INVALID;
        data_block_pointers.time_ms_loaded           [data_block_index] = 0;
        data_block_pointers.time_ms_last_accessed    [data_block_index] = 0;
        data_block_pointers.asset_data_arena_handle  [data_block_index] = {0};
    }
    
    //initialize the table
    out_asset_table_data_block_ref.data_block_count = data_block_count;


    //we're done
    return(result);
}