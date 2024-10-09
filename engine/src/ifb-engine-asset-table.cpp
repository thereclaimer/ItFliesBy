#pragma once

#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-core.hpp"

ifb_internal const ifb_b8
ifb_engine::asset_table_create(IFBEngineAssetTable& asset_table_ref) {

    ifb_b8 result = true;

    //the index count is the same as the asset count
    //there is one for each asset
    asset_table_ref.row_count = IFBEngineAssetId_Count;

    //allocate the tag buffer
    const ifb_size tag_buffer_size = sizeof(ifb_char) * IFB_ENGINE_ASSET_TAG_LENGTH;
    asset_table_ref.tag_buffer = ifb_engine_core_memory_push_array(tag_buffer_size, ifb_char);

    //allocate space for the columns
    asset_table_ref.columns.file_id = ifb_engine_core_memory_push_array(asset_table_ref.row_count, IFBEngineAssetFileId);
    asset_table_ref.columns.start   = ifb_engine_core_memory_push_array(asset_table_ref.row_count, ifb_size);
    asset_table_ref.columns.size    = ifb_engine_core_memory_push_array(asset_table_ref.row_count, ifb_size);
    asset_table_ref.columns.tag     = ifb_engine_core_memory_push_array(asset_table_ref.row_count, ifb_cstr);

    //sanity check, make sure we got our memory
    result = (
        asset_table_ref.tag_buffer      != NULL &&
        asset_table_ref.columns.file_id != NULL &&
        asset_table_ref.columns.start   != NULL &&
        asset_table_ref.columns.size    != NULL &&
        asset_table_ref.columns.tag     != NULL);

    //we're done
    return(result);
}