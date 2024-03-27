#pragma once

#include "itfliesby-engine.hpp"

internal void
itfliesby_engine_assets_indexes_load(
    const handle                                  asset_file_handle,
    const ItfliesbyEngineAssetsFileindex*         indexes,
    const u32                                     indexes_count,
    const itfliesby_engine_assets_allocator_index index_allocator) {
    
    ITFLIESBY_ASSERT(asset_file_handle);
    
    //get the next block for our indexes
    memory index_memory = itfliesby_memory_allocator_block_allocate(index_allocator);
    ITFLIESBY_ASSERT(index_memory);

    //read the asset header data 
    itfliesby_engine_assets_file_header_read(
        asset_file_handle,
        index_memory
    );

    ITFLIESBY_NOP();

}

internal void
itfliesby_engine_assets_init(
    ItfliesbyEngineAssets* assets,
    itfliesby_memory_arena arena) {

    *assets = {0};
    ItfliesbyEngineAssetsFileHandles* file_handles = &assets->file_handles;

    //the assets are starting out in the unloaded state
    for (
        s32 file_index = 0;
        file_index < ITFLIESBY_ASSETS_FILE_ID_COUNT;
        ++file_index) {

        file_handles->unloaded_files[file_index] = (ItfliesbyEngineAssetsFileId)file_index;
        ++file_handles->unloaded_files_count;
    }

    //initialize memory
    assets->memory.partition = itfliesby_memory_partition_create(arena,"ENGINE ASSETS PRTN",  ITFLIESBY_ENGINE_ASSETS_MEMORY_PARTITION_SIZE);
    ITFLIESBY_ASSERT(assets->memory.partition);    

    //allocators
    assets->memory.index_allocator      = itfliesby_memory_allocator_block_create(assets->memory.partition,"ASSET INDEX ALCTR",ITFLIESBY_ENGINE_ASSETS_MEMORY_BLOCK_SIZE_INDEX,     ITFLIESBY_ASSETS_FILE_ID_COUNT);
    assets->memory.asset_data_allocator = itfliesby_memory_allocator_block_create(assets->memory.partition,"ASSET DATA ALCTR", ITFLIESBY_ENGINE_ASSETS_MEMORY_BLOCK_SIZE_ASSET_DATA,ITFLIESBY_ASSETS_FILE_ID_COUNT);
    ITFLIESBY_ASSERT(assets->memory.index_allocator);    
    ITFLIESBY_ASSERT(assets->memory.asset_data_allocator);    
    
}

internal void
itfliesby_engine_assets_update(
    ItfliesbyEngineAssets* assets) {

    itfliesby_engine_assets_file_handles_load(&assets->file_handles);

    itfliesby_engine_assets_indexes_load(
        assets->file_handles.handles.shader_asset_file,
        assets->file_index_store.shader_indexes,
        ITFLIESBY_ENGINE_ASSETS_SHADER_COUNT,
        assets->memory.index_allocator
    );
}

internal void
itfliesby_engine_assets_file_handles_load(
    ItfliesbyEngineAssetsFileHandles* file_handles) {

    //cache the stuff we'll need
    ItfliesbyEngineAssetsFileId* unloaded_files = file_handles->unloaded_files;
    ItfliesbyEngineAssetsFileId* missing_files  = file_handles->missing_files;
    handle* file_handle_array                   = file_handles->handles.array;
    u32 unloaded_files_count                    = file_handles->unloaded_files_count;
    u32 missing_files_count                     = 0;

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