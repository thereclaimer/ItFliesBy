#ifndef ITFLIESBY_ENGINE_ASSETS_HPP
#define ITFLIESBY_ENGINE_ASSETS_HPP

#include "itfliesby-engine.hpp"

struct ItfliesbyEngineAssetsMemory {
    itfliesby_memory_partition        partition;
    itfliesby_memory_allocator_linear index_allocator;
};

struct ItfliesbyEngineAssetsFileindex {
    char tag[32];         // plaintext identifier for the entity the asset belongs to
    u32  file_size;       // size of the data is stored in the file
    u32  allocation_size; // the size of the space we need to allocate when storing the asset data in memory
    u32  offset;          // the index of the first byte of asset data in the file
};

struct ItfliesbyEngineAssetsFileIndexStore {
    ItfliesbyEngineAssetsFileindex* shader_indexes;
    u32                      num_shader_indexes;
};

const char* ITFLIESBY_ENGINE_ASSETS_FILE_PATHS[] = {
    "ItFliesBy.Assets.Shaders.ifb"
};

enum ItfliesbyEngineAssetsFileId : s32 {
    ITFLIESBY_ASSETS_FILE_ID_INVALID = -1,
    ITFLIESBY_ASSETS_FILE_ID_SHADERS = 0,
    ITFLIESBY_ASSETS_FILE_ID_COUNT   = 1
};

//these have to match the order of the indexes in assets-shader-table.csv
enum ItfliesbyEngineAssetsShader : s32 {
    ITFLIESBY_ENGINE_ASSETS_SHADER_INVALID                       = -1,
    ITFLIESBY_ENGINE_ASSETS_SHADER_TEXTURED_QUAD_VERTEX_SHADER   = 0,
    ITFLIESBY_ENGINE_ASSETS_SHADER_TEXTURED_QUAD_FRAGMENT_SHADER = 1,
    ITFLIESBY_ENGINE_ASSETS_SHADER_COUNT                         = 2,
};  

struct ItfliesbyEngineAssetsFileHandles {
    union {
        struct {
            handle shader_asset_file;
        };
        handle array[ITFLIESBY_ASSETS_FILE_ID_COUNT];
    };
    ItfliesbyEngineAssetsFileId unloaded_files[ITFLIESBY_ASSETS_FILE_ID_COUNT];
    ItfliesbyEngineAssetsFileId missing_files[ITFLIESBY_ASSETS_FILE_ID_COUNT];
    u32                   unloaded_files_count;
    u32                   missing_files_count;

};

struct ItfliesbyEngineAssets {
    ItfliesbyEngineAssetsFileHandles    file_handles;
    ItfliesbyEngineAssetsFileIndexStore file_index_store;
};


void
itfliesby_engine_assets_init(
    ItfliesbyEngineAssets* assets
);

internal void
itfliesby_engine_assets_update(
    ItfliesbyEngineAssets* assets
);

void
itfliesby_engine_assets_file_handles_load(
    ItfliesbyEngineAssetsFileHandles* assets
);

#endif //ITFLIESBY_ENGINE_ASSETS_HPP
