#pragma once

#include "itfliesby-engine.hpp"

internal u32
itfliesby_engine_assets_file_header_num_indexes(
    const handle asset_handle) {
    
    char header_buffer[7] = {0};

    platform_api.file_read(
        asset_handle,
        0,
        8,
        (memory)header_buffer
    );

    ITFLIESBY_ASSERT(
        header_buffer[0] == 'I' &&
        header_buffer[1] == 'F' &&
        header_buffer[2] == 'B'
    );

    u16 num_indexes = *(u32*)&header_buffer[3];

    return(num_indexes);
}

internal memory
itfliesby_engine_assets_file_header_allocate_and_read(
    const handle                             asset_handle,
    const u32                                asset_header_num_indexes,
    itfliesby_engine_assets_allocator_header asset_header_allocator) {

    //calculate the index buffer suze
    u64 asset_data_size = ITFLIESBY_ASSET_FILE_INDEX_SIZE_TOTAL(asset_header_num_indexes);

    //allocate space for the index buffer
    memory asset_index_data = 
        itfliesby_memory_allocator_linear_allocate(
            asset_header_allocator,
            asset_data_size
    );
    ITFLIESBY_ASSERT(asset_index_data);

    //read the indexes into the buffer
    platform_api.file_read(
        asset_handle,
        7,
        asset_data_size,
        asset_index_data
    );

    return(asset_index_data);
}

internal void
itfliesby_engine_assets_file_header_destroy(
    itfliesby_engine_assets_allocator_header asset_header_allocator,
    memory                                   asset_header_memory) {

    itfliesby_memory_allocator_linear_reset(asset_header_allocator);
    asset_header_memory = NULL;
}

internal void
itfliesby_engine_asset_indexes_load(
    ItfliesbyEngineAssetsFileHandles*        asset_file_handles,
    ItfliesbyEngineAssetsFileIndexStore*     asset_index_store,
    itfliesby_engine_assets_allocator_index  index_allocator,
    itfliesby_engine_assets_allocator_header header_allocator) {

    handle*                                   asset_file_handle_array = asset_file_handles->handles.array;
    ItfliesbyEngineAssetsFileIndexCollection* index_collection;
    handle                                    asset_file_handle;

    for (
        s32 file_index = 0;
        file_index < ITFLIESBY_ASSETS_FILE_ID_COUNT;
        ++file_index) {

        //initialize our stuff
        asset_file_handle = asset_file_handle_array[file_index]; 
        index_collection  = &asset_index_store->array[file_index];

        //get the number of indexes
        u32 asset_num_indexes = 
            itfliesby_engine_assets_file_header_num_indexes(asset_file_handle);
    
        //read our index buffer
        memory asset_index_memory = 
            itfliesby_engine_assets_file_header_allocate_and_read(
                asset_file_handle,
                asset_num_indexes,
                header_allocator
        );
        ITFLIESBY_ASSERT(asset_index_memory);

        //we got the data, now we need to allocate for our index structures
        index_collection->indexes       = (ItfliesbyEngineAssetsFileindex*)itfliesby_memory_allocator_block_allocate(index_allocator);
        ITFLIESBY_ASSERT(index_collection->indexes);
        index_collection->indexes_count = asset_num_indexes;

        for (
            u32 index = 0;
            index < index_collection->indexes_count;
            ++index) {

            //current index
            ItfliesbyEngineAssetsFileindex* current_index = &index_collection->indexes[index];

            u64 offset = ITFLIESBY_ASSET_FILE_INDEX_SIZE * index;

            //tag
            memmove(
                (void*)current_index->tag,
                (void*)&asset_index_memory[offset],
                32
            );

            //rest of the shit
            memmove(
                (void*)((memory)current_index + 32),
                (void*)&asset_index_memory[offset + 32],
                ITFLIESBY_ASSET_FILE_INDEX_SIZE - 32
            );
        }

        //destroy the index buffer and reset the allocator
        itfliesby_engine_assets_file_header_destroy(
            header_allocator,
            asset_index_memory
        );
    }
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
    assets->memory.index_allocator        = itfliesby_memory_allocator_block_create(assets->memory.partition,"ASSET INDEX ALCTR",ITFLIESBY_ENGINE_ASSETS_MEMORY_BLOCK_SIZE_INDEX,     ITFLIESBY_ASSETS_FILE_ID_COUNT);
    assets->memory.asset_data_allocator   = itfliesby_memory_allocator_block_create(assets->memory.partition,"ASSET DATA ALCTR", ITFLIESBY_ENGINE_ASSETS_MEMORY_BLOCK_SIZE_ASSET_DATA,ITFLIESBY_ASSETS_FILE_ID_COUNT);
    assets->memory.asset_header_allocator = itfliesby_memory_allocator_linear_create(assets->memory.partition,"ASSET HEADER ALCTR",ITFLIESBY_ENGINE_ASSETS_MEMORY_ALLOCATOR_HEADER_SIZE);
    ITFLIESBY_ASSERT(assets->memory.index_allocator);    
    ITFLIESBY_ASSERT(assets->memory.asset_data_allocator);    
    ITFLIESBY_ASSERT(assets->memory.asset_header_allocator);    
}

internal void
itfliesby_engine_assets_update(
    ItfliesbyEngineAssets* assets) {

    ItfliesbyEngineAssetsFileHandles*    file_handles = &assets->file_handles;
    ItfliesbyEngineAssetsFileIndexStore* index_store  = &assets->file_index_store;
    ItfliesbyEngineAssetsMemory*         asset_memory = &assets->memory;

    itfliesby_engine_assets_file_handles_load(file_handles);

    itfliesby_engine_asset_indexes_load(
        file_handles,
        index_store,
        asset_memory->index_allocator,
        asset_memory->asset_header_allocator
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

internal u64
itfliesby_engine_assets_index_allocation_size(
    ItfliesbyEngineAssetsFileIndexCollection* index_collection,
    s32*                                      index_ids,
    s32                                       index_ids_count) {

    ITFLIESBY_ASSERT(
        index_collection    && 
        index_ids           && 
        index_ids_count > 0 &&
        index_ids_count < index_collection->indexes_count);

    ItfliesbyEngineAssetsFileindex* indexes = index_collection->indexes;
    ItfliesbyEngineAssetsFileindex current_index;
    u64 index_memory_size = 0;
    u32 current_index_id;

    for (
        u32 index = 0;
        index < index_ids_count;
        ++index) {

        //get the index size
        current_index_id = index_ids[index];
        current_index     = indexes[current_index_id];
        index_memory_size += current_index.allocation_size;
    }

    return(index_memory_size);
}

internal void
itfliesby_engine_assets_load_asset_from_index(
    ItfliesbyEngineAssetsFileindex asset_file_index,
    handle                         asset_file_handle,
    memory                         asset_file_memory) {

    platform_api.file_read(
        asset_file_handle,
        asset_file_index.offset,
        asset_file_index.allocation_size,
        asset_file_memory   
    );
}

internal void
itfliesby_engine_assets_load_shaders(
    ItfliesbyEngineAssets* assets,
    s32*                   shader_index_ids,
    memory                 shader_memory,
    u64*                   shader_offsets,
    u32                    shader_count) {

    ITFLIESBY_ASSERT(
        assets && 
        shader_memory &&
        shader_count > 0);

    //NOTE: we are assuming here you have allocated the memory
    //fuck around and find out

    ItfliesbyEngineAssetsFileindex* shader_file_indexes = assets->file_index_store.collections.shader_indexes.indexes;
    handle                          shader_file_handle  = assets->file_handles.handles.shader_asset_file;
    ItfliesbyEngineAssetsFileindex  current_shader_file_index;
    memory                          current_shader_memory;
    u64                             current_shader_offset = 0;

    for (
        u32 shader_index = 0;
        shader_index < shader_count;
        ++shader_index) {

        //get info for the current shader
        current_shader_memory     = &shader_memory[current_shader_offset];
        current_shader_file_index = shader_file_indexes[shader_index];

        //load the shader
        itfliesby_engine_assets_load_asset_from_index(
            current_shader_file_index,
            shader_file_handle,
            current_shader_memory
        );
    
        //update the offsets
        shader_offsets[shader_index] = current_shader_offset;
        current_shader_offset       += current_shader_file_index.allocation_size;
    }

}