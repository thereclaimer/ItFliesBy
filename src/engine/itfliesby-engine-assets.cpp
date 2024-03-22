#pragma once

#include "itfliesby-engine.hpp"

internal void
itfliesby_engine_assets_init(
    ItfliesbyEngineAssets* assets) {

    *assets = {0};
    ItfliesbyEngineAssetsFileHandles* file_handles = &assets->file_handles;

    //the assets are starting out in the unloaded state
    for (
        s32 file_index = 0;
        file_index < ITFLIESBY_ASSETS_FILE_ID_COUNT;
        ++file_index
    ) {
        file_handles->unloaded_files[file_index] = (ItfliesbyEngineAssetsFileId)file_index;
        ++file_handles->unloaded_files_count;
    }
}

internal void
itfliesby_engine_assets_update(
    ItfliesbyEngineAssets* assets) {

    itfliesby_engine_assets_file_handles_load(&assets->file_handles);
}

internal void
itfliesby_engine_assets_file_handles_load(
    ItfliesbyEngineAssetsFileHandles* file_handles) {

    //cache the stuff we'll need
    ItfliesbyEngineAssetsFileId* unloaded_files = file_handles->unloaded_files;
    ItfliesbyEngineAssetsFileId* missing_files  = file_handles->missing_files;
    handle* file_handle_array             = file_handles->array;
    u32 unloaded_files_count              = file_handles->unloaded_files_count;
    u32 missing_files_count               = 0;

    ItfliesbyEngineAssetsFileId asset_id_to_load;
    for (
        u32 unloaded_file_index = 0;
        unloaded_file_index < unloaded_files_count;
        ++unloaded_file_index) {

        //get the next asset id
        asset_id_to_load = unloaded_files[unloaded_file_index];

        //get the file handle
        file_handle_array[asset_id_to_load] = 
            platform_api.file_open(
                (str)ITFLIESBY_ENGINE_ASSETS_FILE_PATHS[asset_id_to_load],
                false
            );
        
        //if the file failed to load, add it to the missing files table
        if (!file_handle_array[asset_id_to_load]) {
            missing_files[missing_files_count];
            ++missing_files_count;
        }
    }

    file_handles->unloaded_files_count = 0;
    file_handles->missing_files_count  = missing_files_count;

    if (missing_files_count > 0) {
        //TODO: error message
        ITFLIESBY_PANIC();
    }
}