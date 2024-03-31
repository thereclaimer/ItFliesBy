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
    ItfliesbyEngineAssetsFileindex*          file_indexes,
    handle                                   file_handle,
    u32                                      file_indexes_count,
    itfliesby_engine_assets_allocator_header header_allocator,
    itfliesby_engine_assets_allocator_index  index_allocator) {

    //make sure the indexes in the file match what we expect
    u32 file_indexes_count_actual = itfliesby_engine_assets_file_header_num_indexes(file_handle);
    ITFLIESBY_ASSERT(file_indexes_count_actual == file_indexes_count);

    //read our index buffer
    memory file_index_memory = 
        itfliesby_engine_assets_file_header_allocate_and_read(
            file_handle,
            file_indexes_count,
            header_allocator
    );

    ItfliesbyEngineAssetsFileindex* current_file_index;

    for (
        u32 index = 0;
        index < file_indexes_count;
        ++index) {

        //current index
        ItfliesbyEngineAssetsFileindex* current_index = &file_indexes[index];

        //calculate the offset
        u64 offset = ITFLIESBY_ASSET_FILE_INDEX_SIZE * index;

        //tag
        memmove(
            (void*)current_index->tag,
            (void*)&file_index_memory[offset],
            32
        );

        //rest of the shit
        memmove(
            (void*)((memory)current_index + 32),
            (void*)&file_index_memory[offset + 32],
            ITFLIESBY_ASSET_FILE_INDEX_SIZE - 32
        );

        //for some reason, 5 bytes get lost in translation
        current_index->allocation_size += 5;
    }

    //destroy the index buffer and reset the allocator
    itfliesby_engine_assets_file_header_destroy(
        header_allocator,
        file_index_memory
    );
}

internal void
itfliesby_engine_asset_indexes_load_all(
    ItfliesbyEngineAssetsFileHandles*        asset_file_handles,
    ItfliesbyEngineAssetsFileIndexStore*     asset_index_store,
    itfliesby_engine_assets_allocator_index  index_allocator,
    itfliesby_engine_assets_allocator_header header_allocator) {

    handle* asset_file_handle_array = asset_file_handles->array;
    handle  asset_file_handle;

    //load shaders
    itfliesby_engine_asset_indexes_load(
        asset_index_store->shader_indexes,
        asset_file_handles->shader_asset_file,
        ITFLIESBY_ENGINE_ASSETS_SHADER_COUNT,
        header_allocator,
        index_allocator
    );
}

internal void 
itfliesby_engine_assets_init(
    ItfliesbyEngineAssets* assets,
    itfliesby_memory_arena arena) {

    *assets = {0};
    ItfliesbyEngineAssetsFileHandles* file_handles = &assets->file_handles;

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

    itfliesby_engine_assets_file_handles_load(file_handles);

    itfliesby_engine_asset_indexes_load_all(
        file_handles,
        &assets->file_index_store,
        assets->memory.index_allocator,
        assets->memory.asset_header_allocator
    );
}

internal void
itfliesby_engine_assets_update(
    ItfliesbyEngineAssets* assets) {

    ItfliesbyEngineAssetsFileHandles*    file_handles = &assets->file_handles;
    ItfliesbyEngineAssetsFileIndexStore* index_store  = &assets->file_index_store;
    ItfliesbyEngineAssetsMemory*         asset_memory = &assets->memory;


}

internal void
itfliesby_engine_assets_file_handles_load(
    ItfliesbyEngineAssetsFileHandles* file_handles) {

    //cache our stuff
    handle* file_handle_array   = file_handles->array;
    handle  current_file_handle;
    u32     missing_files_count = 0;
    s32     missing_files_array[ITFLIESBY_ASSETS_FILE_ID_COUNT];
    str     file_path;
    
    for (
        u32 file_handle_index = 0;
        file_handle_index < ITFLIESBY_ASSETS_FILE_ID_COUNT;
        ++file_handle_index) {

        //get the file path
        file_path = (str)ITFLIESBY_ENGINE_ASSETS_FILE_PATHS[file_handle_index];

        //open the file
        current_file_handle = platform_api.file_open(file_path,false);
    
        //if we have a file, we're good
        if (current_file_handle) {
            file_handle_array[file_handle_index] = current_file_handle;
            continue;
        }

        //otherwise, add this to the missing file list
        missing_files_array[missing_files_count] = file_handle_index;
        ++missing_files_count;
    }

    if (missing_files_count > 0) {
        //TODO: error message
        ITFLIESBY_PANIC();
    }
}

internal u64
itfliesby_engine_assets_index_allocation_size(
    ItfliesbyEngineAssetsFileindex* indexes,
    s32*                            index_ids,
    s32                             index_ids_count) {

    ITFLIESBY_ASSERT(
        indexes    && 
        index_ids  && 
        index_ids_count > 0);

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

    ItfliesbyEngineAssetsFileindex* shader_file_indexes = assets->file_index_store.shader_indexes;
    handle                          shader_file_handle  = assets->file_handles.shader_asset_file;
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