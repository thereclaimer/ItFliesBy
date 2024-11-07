#pragma once

#include "ifb-engine-internal-asset.hpp"

inline const ifb_b8
ifb_engine::asset_header_table_create(
    IFBEngineAssetMemory&       in_asset_memory_ref,
    IFBEngineAssetTableHeader& out_asset_table_header_ref) {

    ifb_b8 result = true;
    
    //get the pointers
    IFBEngineAssetMemoryTableHeaderPointers header_table_pointers;
    result &= ifb_engine::asset_memory_pointers_header_table(
        in_asset_memory_ref,
        header_table_pointers);

    //initialize table
    const ifb_size asset_name_buffer_length = IFB_ENGINE_ASSET_HEADER_NAME_LENGTH * IFBEngineAssetId_Count; 
    memset(header_table_pointers.name_buffer,0,asset_name_buffer_length);
    out_asset_table_header_ref.asset_count       = IFBEngineAssetId_Count;
    out_asset_table_header_ref.asset_name_length = IFB_ENGINE_ASSET_HEADER_NAME_LENGTH;

    //we're done
    return(result);
}