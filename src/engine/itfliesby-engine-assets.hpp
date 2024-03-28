#ifndef ITFLIESBY_ENGINE_ASSETS_HPP
#define ITFLIESBY_ENGINE_ASSETS_HPP

#include "itfliesby-engine.hpp"
#include "itfliesby-engine-globals.hpp"


#define ITFLIESBY_ENGINE_ASSETS_MEMORY_PARTITION_SIZE         ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_ENGINE_ASSETS_MEMORY_BLOCK_SIZE_INDEX       ITFLIESBY_MATH_KILOBYTES(1)
#define ITFLIESBY_ENGINE_ASSETS_MEMORY_BLOCK_SIZE_ASSET_DATA  ITFLIESBY_MATH_MEGABYTES(8)

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

typedef itfliesby_memory_allocator_block itfliesby_engine_assets_allocator_index;
typedef itfliesby_memory_allocator_block itfliesby_engine_assets_allocator_data;

struct ItfliesbyEngineAssetsMemory {
    itfliesby_memory_partition               partition;
    itfliesby_engine_assets_allocator_index  index_allocator;
    itfliesby_engine_assets_allocator_data   asset_data_allocator;
};

struct ItfliesbyEngineAssetsFileindex {
    char tag[32];         // plaintext identifier for the entity the asset belongs to
    u32  file_size;       // size of the data is stored in the file
    u32  allocation_size; // the size of the space we need to allocate when storing the asset data in memory
    u32  offset;          // the index of the first byte of asset data in the file
};

struct ItfliesbyEngineAssetsFileIndexCollection {
    union {
        ItfliesbyEngineAssetsFileindex* indexes;
        memory                          index_memory;
    };
    u32 index_count;
};

struct ItfliesbyEngineAssetsFileIndexStore {
    union {
        struct {
            ItfliesbyEngineAssetsFileIndexCollection shader_indexes;
        } collections;
        ItfliesbyEngineAssetsFileIndexCollection array[ITFLIESBY_ASSETS_FILE_ID_COUNT];
    };
};

const char* ITFLIESBY_ENGINE_ASSETS_FILE_PATHS[] = {
    "ItFliesBy.Assets.Shaders.ifb"
};

struct ItfliesbyEngineAssetsFileHandles {
    union {
        struct {
            handle shader_asset_file;
        };
        handle array[ITFLIESBY_ASSETS_FILE_ID_COUNT];
    } handles; 
    ItfliesbyEngineAssetsFileId unloaded_files[ITFLIESBY_ASSETS_FILE_ID_COUNT];
    ItfliesbyEngineAssetsFileId missing_files[ITFLIESBY_ASSETS_FILE_ID_COUNT];
    u32                         unloaded_files_count;
    u32                         missing_files_count;

};

struct ItfliesbyEngineAssets {
    ItfliesbyEngineAssetsMemory         memory;
    ItfliesbyEngineAssetsFileHandles    file_handles;
    ItfliesbyEngineAssetsFileIndexStore file_index_store;
};

void
itfliesby_engine_assets_init(
    ItfliesbyEngineAssets* assets,
    itfliesby_memory_arena arena
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
