#ifndef IFB_ENGINE_INTERNAL_ASSET_HPP
#define IFB_ENGINE_INTERNAL_ASSET_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* ASSET                                                                          */
/**********************************************************************************/

typedef ifb_index IFBEngineAssetDataIndex;
typedef ifb_index IFBEngineAssetIndex;
typedef ifb_index IFBEngineAssetFileIndex;

struct IFBEngineAsset {
    IFBEngineAssetId        asset_id;
    IFBEngineAssetFileId    file_id;
    ifb_size                offset;
    ifb_size                size;
    IFBEngineAssetDataIndex data_table_index;
    ifb_cstr                asset_tag;
};


/**********************************************************************************/
/* DATA TABLE                                                                     */
/**********************************************************************************/

struct IFBEngineAssetDataBlock {
    ifb_index asset_id;
    ifb_index data_index;
};

#define IFB_ENGINE_ASSET_DATA_TABLE_ID_INVALID IFBEngineAssetId_Count + 1

struct IFBEngineAssetDataTable {
    RHNDMemoryRegion region_handle;
    ifb_size         row_count;
    struct {
        RHNDMemoryArena* arena;
    } columns;
};

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_data_table_create(
        const ifb_size                  in_data_table_arena_size,
        const ifb_size                  in_data_table_arena_count,
              IFBEngineAssetDataTable& out_data_table_ref); 
};

/**********************************************************************************/
/* ASSET TABLE                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_ASSET_TAG_LENGTH 32


struct IFBEngineAssetTable {
    ifb_size row_count;
    ifb_cstr tag_buffer;
    struct {
        IFBEngineAssetFileId*    file_id;
        ifb_size*                start;
        ifb_size*                size;
        ifb_cstr*                tag;
    } columns;
};

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_table_create(IFBEngineAssetTable& asset_table_ref);
};

/**********************************************************************************/
/* FILE TABLE                                                                    */
/**********************************************************************************/

struct IFBEngineAssetFileTable {
    ifb_size         row_count;
    struct {
        ifb_handle* file_handle;
        ifb_cstr*   file_name;
        ifb_size*   asset_count;
    } columns;
};

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_file_table_create(IFBEngineAssetFileTable& file_table);
};

/**********************************************************************************/
/* ASSET MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineAssetManager {
    struct {
        IFBEngineAssetTable      asset;
        IFBEngineAssetFileTable  file;
        IFBEngineAssetDataTable  data;
    } tables;
};

namespace ifb_engine {

    ifb_internal const r_b8
    asset_manager_create(
        const ifb_size                in_asset_data_arena_size,
              IFBEngineAssetManager& out_asset_manager_ref);
};

#endif //IFB_ENGINE_INTERNAL_ASSET_HPP