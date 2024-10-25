#pragma once

#include "ifb-engine-internal-asset.hpp"

ifb_internal const ifb_b8
ifb_engine::asset_header_create_table(
    IFBEngineCoreMemory&        in_engine_core_memory_ref,
    IFBEngineAssetTableHeader& out_asset_table_header_ref) {

    //calculate sizes
    const ifb_size asset_count              = IFBEngineAssetId_Count;
    const ifb_size asset_name_length        = IFB_ENGINE_ASSET_HEADER_NAME_LENGTH;
    const ifb_size asset_name_buffer_length = asset_name_length * asset_count;

    //allocate memory
    ifb_cstr                      ptr_name_buffer = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,asset_name_buffer_length,ifb_char);
    IFBEngineAssetTableIndexFile* ptr_file_index  = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,asset_count,             IFBEngineAssetTableIndexFile);
    ifb_size*                     ptr_data_size   = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,asset_count,             ifb_size);
    ifb_size*                     ptr_data_start  = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,asset_count,             ifb_size);
    
    //sanity check
    const ifb_b8 result = (
        ptr_name_buffer &&
        ptr_file_index  &&
        ptr_data_size   &&
        ptr_data_start);

    //initialize table
    memset(ptr_name_buffer,0,asset_name_buffer_length);
    out_asset_table_header_ref.asset_count                        = asset_count;
    out_asset_table_header_ref.asset_name_length                  = asset_name_length;
    out_asset_table_header_ref.asset_name_buffer                  = ptr_name_buffer;
    out_asset_table_header_ref.columns.ptr_asset_file_table_index = ptr_file_index;
    out_asset_table_header_ref.columns.ptr_asset_file_data_size   = ptr_data_size;
    out_asset_table_header_ref.columns.ptr_asset_file_data_start  = ptr_data_start;

    //we're done
    return(result);
}