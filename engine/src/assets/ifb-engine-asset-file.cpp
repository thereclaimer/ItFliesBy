#pragma once

#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-platform.hpp"

inline const ifb_b8
ifb_engine::asset_file_table_create(
    IFBEngineAssetMemory&     in_asset_memory_ref,
    IFBEngineAssetTableFile& out_asset_file_table_ref) {
    
    ifb_b8 result = true;

    //get the table data
    IFBEngineAssetMemoryTableFilePointers file_table_pointers;
    result &= ifb_engine::asset_memory_pointers_file_table(
        in_asset_memory_ref,
        file_table_pointers);

    //open the files
    result &= ifb_engine::platform_file_open_read_only(IFB_ENGINE_ASSET_FILE_PATH_SHADERS, file_table_pointers.platform_index[IFBEngineAssetFileId_Shaders]);
    result &= ifb_engine::platform_file_open_read_only(IFB_ENGINE_ASSET_FILE_PATH_IMAGES,  file_table_pointers.platform_index[IFBEngineAssetFileId_Images]);
    result &= ifb_engine::platform_file_open_read_only(IFB_ENGINE_ASSET_FILE_PATH_SOUNDS,  file_table_pointers.platform_index[IFBEngineAssetFileId_Sounds]);
    result &= ifb_engine::platform_file_open_read_only(IFB_ENGINE_ASSET_FILE_PATH_DIALOG,  file_table_pointers.platform_index[IFBEngineAssetFileId_Dialog]);

    //we're done
    return(result);
}