#pragma once

#include "ifb-engine-internal-asset.hpp"

ifb_internal const ifb_b8
ifb_engine::asset_file_create_table(
    IFBEngineCoreMemory&      in_engine_core_memory_ref,
    IFBEngineAssetTableFile& out_asset_file_table_ref) {

    const ifb_size file_count            = IFBEngineAssetFileId_Count;
    const ifb_size file_path_length      = IFB_ENGINE_ASSET_FILE_PATH_LENGTH;
    const ifb_size file_path_buffer_size = file_path_length * IFBEngineAssetFileId_Count;

    ifb_cstr                    ptr_file_path_buffer    = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,file_path_buffer_size,ifb_char);
    IFBEnginePlatformFileIndex* ptr_file_platform_index = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,file_count,           IFBEnginePlatformFileIndex);
    ifb_size*                   ptr_file_size           = ifb_engine_core_memory_ref_push_array(in_engine_core_memory_ref,file_count,           ifb_size);

    const ifb_b8 result = (
        ptr_file_path_buffer    &&
        ptr_file_platform_index &&
        ptr_file_size);

    out_asset_file_table_ref.asset_file_count                       = file_count;
    out_asset_file_table_ref.asset_file_path_length                 = file_path_length;
    out_asset_file_table_ref.asset_file_path_buffer                 = ptr_file_path_buffer;
    out_asset_file_table_ref.columns.ptr_asset_file_platform_index  = ptr_file_platform_index;
    out_asset_file_table_ref.columns.ptr_asset_file_size            = ptr_file_size;

    return(result);
}