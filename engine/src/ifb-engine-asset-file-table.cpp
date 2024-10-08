#pragma once

#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-core.hpp"

ifb_internal const ifb_b8
ifb_engine::asset_file_table_create(
    IFBEngineAssetFileTable& file_table) {


    const r_size asset_file_count = IFBEngineAssetFileId_Count;
    
    //allocate and initialize the file table
    file_table.row_count           = asset_file_count; 
    file_table.columns.file_handle = ifb_engine_core_memory_push_array(ifb_handle,asset_file_count);
    file_table.columns.file_name   = ifb_engine_core_memory_push_array(ifb_cstr,  asset_file_count);

    //sanity check
    if (
        !file_table.columns.file_handle ||
        !file_table.columns.file_name) {

        return(false);
    }

    //set the file names
    file_table.columns.file_name[IFBEngineAssetFileId_Shaders] = ifb_engine::core_system_memory_push_cstring(IFB_ENGINE_ASSET_FILE_PATH_SHADERS);
    file_table.columns.file_name[IFBEngineAssetFileId_Images]  = ifb_engine::core_system_memory_push_cstring(IFB_ENGINE_ASSET_FILE_PATH_IMAGES);

    //sanity check
    ifb_b8 result = (
        file_table.columns.file_name[IFBEngineAssetFileId_Shaders] &&
        file_table.columns.file_name[IFBEngineAssetFileId_Images]);

    //we're done
    return(result);
}