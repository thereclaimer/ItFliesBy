#ifndef IFB_ENGINE_INTERNAL_ASSET_HPP
#define IFB_ENGINE_INTERNAL_ASSET_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

typedef ifb_index IFBEngineAssetDataIndex;

struct IFBEngineAssetDataBlock {
    ifb_index asset_id;
    ifb_index file_index;
    ifb_index data_index;
};

struct IFBEngineAssetDataTable {
    RHNDMemoryRegion region_handle;
    ifb_size         row_count;
    struct {
        RHNDMemoryArena*         arena;
        IFBEngineAssetDataBlock* data_block;
    } columns;
};

typedef ifb_index IFBEngineAssetId;

struct IFBEngineAssetIndex {
    IFBEngineAssetId        id;
    ifb_size                offset;
    ifb_size                size;
    IFBEngineAssetDataIndex data_table_index;
};

struct IFBEngineAssetIndexTable {
    ifb_size row_count;
    struct {
        IFBEngineAssetId*        id;
        ifb_size*                offset;
        ifb_size*                size;
        IFBEngineAssetDataIndex* data_table_index;
    } columns;
};

struct IFBEngineAssetFileTable {
    RHNDMemoryRegion region_handle;
    ifb_size         row_count;
    struct {
        RHNDMemoryArena*          arena_handle;
        ifb_handle*               file_handle;
        IFBEngineAssetIndexTable* index_table;
    } columns;
};

struct IFBEngineAssetManager {
    IFBEngineAssetDataTable asset_data_table;
    IFBEngineAssetFileTable asset_file_table;
};



namespace ifb_egine {

    ifb_internal const r_b8
    asset_manager_create(
        const ifb_size asset_file_arena_size,
        const ifb_size asset_data_arena_size);

};

#endif //IFB_ENGINE_INTERNAL_ASSET_HPP