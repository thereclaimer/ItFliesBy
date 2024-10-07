#ifndef IFB_ENGINE_INTERNAL_ASSET_HPP
#define IFB_ENGINE_INTERNAL_ASSET_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* ASSET                                                                          */
/**********************************************************************************/

typedef ifb_index IFBEngineAssetId;
typedef ifb_index IFBEngineAssetDataIndex;
typedef ifb_index IFBEngineAssetIndex;
typedef ifb_index IFBEngineAssetFileIndex;

struct IFBEngineAsset {
    IFBEngineAssetId        id;
    IFBEngineAssetFileIndex file;
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

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_index_table_create();

};

/**********************************************************************************/
/* FILE TABLE                                                                    */
/**********************************************************************************/

struct IFBEngineAssetFileTable {
    RHNDMemoryRegion region_handle;
    ifb_size         row_count;
    struct {
        RHNDMemoryArena*          arena_handle;
        ifb_handle*               file_handle;
    } columns;
};

/**********************************************************************************/
/* ASSET MANAGER                                                                  */
/**********************************************************************************/


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