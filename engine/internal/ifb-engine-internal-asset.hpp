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
    IFBEngineAssetId        id;
    IFBEngineAssetFileId    file;
    IFBEngineAssetIndex     index;
    IFBEngineAssetDataIndex data;
};


/**********************************************************************************/
/* DATA TABLE                                                                     */
/**********************************************************************************/

struct IFBEngineAssetDataBlock {
    ifb_index asset_id;
    ifb_index file_index;
    ifb_index data_index;
};

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
        const ifb_size data_table_arena_size); 

};

/**********************************************************************************/
/* INDEX TABLE                                                                    */
/**********************************************************************************/

struct IFBEngineAssetIndexInfo {
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

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_index_table_create();

};

/**********************************************************************************/
/* FILE TABLE                                                                    */
/**********************************************************************************/

struct IFBEngineAssetFileTable {
    ifb_size         row_count;
    struct {
        ifb_handle* file_handle;
        ifb_cstr*   file_name;
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
        IFBEngineAssetFileTable  file;
        IFBEngineAssetIndexTable index;
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