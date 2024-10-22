#ifndef IFB_ENGINE_INTERNAL_ASSET_HPP
#define IFB_ENGINE_INTERNAL_ASSET_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineAssetFile;
struct IFBEngineAssetHeader;
struct IFBEngineAssetDataBlock;

struct IFBEngineAssetTableFile;
struct IFBEngineAssetTableHeader;
struct IFBEngineAssetTableDataBlock;

/**********************************************************************************/
/* ASSET FILE                                                                     */
/**********************************************************************************/

#define IFB_ENGINE_ASSET_FILE_PATH_LENGTH   256
#define IFB_ENGINE_ASSET_FILE_INDEX_INVALID IFB_INDEX_INVALID

struct IFBEngineAssetFile {
    IFBEngineAssetTableIndexFile asset_file_table_index;
    IFBEnginePlatformFileIndex   asset_file_platform_index;
    ifb_size                     asset_file_size;
};

struct IFBEngineAssetTableFile {
    ifb_size asset_file_count;
    ifb_size asset_file_path_length;
    ifb_cstr asset_file_path_buffer;
    struct {
        IFBEnginePlatformFileIndex* ptr_asset_file_platform_index;
        ifb_size*                   ptr_asset_file_size;
    } columns; 
};

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_file_create_table(
        IFBEngineCoreMemory&      in_engine_core_memory_ref,
        IFBEngineAssetTableFile& out_asset_file_table_ref);
};

/**********************************************************************************/
/* ASSET HEADER                                                                   */
/**********************************************************************************/

#define IFB_ENGINE_ASSET_HEADER_NAME_LENGTH 32
#define IFB_ENGINE_ASSET_HEADER_INDEX_INVALID IFB_INDEX_INVALID

struct IFBEngineAssetHeader {
    struct {
        IFBEngineAssetTableIndexFile   file;
        IFBEngineAssetTableIndexHeader header;
    } asset_table_indexes;
    ifb_size                       asset_file_data_size;
    ifb_size                       asset_file_data_start;
};

struct IFBEngineAssetTableHeader {
    ifb_size asset_count;
    ifb_size asset_name_length;
    ifb_cstr asset_name_buffer;
    struct {
        IFBEngineAssetTableIndexFile* ptr_asset_file_table_index;
        ifb_size*                     ptr_asset_file_data_size;
        ifb_size*                     ptr_asset_file_data_start;
    } columns;
};

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_header_create_table(
        IFBEngineCoreMemory&        in_engine_core_memory_ref,
        IFBEngineAssetTableHeader& out_asset_table_header_ref);
}

/**********************************************************************************/
/* ASSET DATA BLOCK                                                               */
/**********************************************************************************/

#define IFB_ENGINE_ASSET_DATA_BLOCK_SIZE          r_memory_size_kilobytes(64)
#define IFB_ENGINE_ASSET_DATA_BLOCK_COUNT         1024
#define IFB_ENGINE_ASSET_DATA_BLOCK_INDEX_INVALID IFB_INDEX_INVALID

struct IFBEngineAssetDataBlock {
    IFBEngineAssetTableIndexHeader    asset_table_index_header;
    IFBEngineAssetTableIndexDataBlock asset_table_index_data_block;
    ifb_timems                        time_ms_loaded;
    ifb_timems                        time_ms_last_accessed;
    RMemoryArenaHandle                asset_data_arena_handle;
};

struct IFBEngineAssetTableDataBlock {
    RMemoryRegionHandle region_handle;
    ifb_size            data_block_count;
    struct {
        IFBEngineAssetTableIndexHeader* ptr_asset_table_index_header;
        ifb_timems*                     ptr_time_ms_loaded;
        ifb_timems*                     ptr_time_ms_last_accessed;
        RMemoryArenaHandle*             ptr_asset_data_arena_handle;
    } columns;
};

namespace ifb_engine {

    ifb_internal const ifb_b8 
    asset_data_block_create_table(
        IFBEngineCoreMemory &          in_engine_core_memory_ref,
        IFBEngineAssetTableDataBlock& out_asset_table_data_block_ref);
};

/**********************************************************************************/
/* ASSET MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineAssetManager {
    ifb_timems time_ms_initialized;
    struct {
        IFBEngineAssetTableFile      file;
        IFBEngineAssetTableHeader    header;
        IFBEngineAssetTableDataBlock data_block;
    } asset_tables;
};

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_manager_start_up(
        IFBEngineCoreMemory     in_engine_core_memory_ref,
        IFBEngineAssetManager& out_asset_manager_ref);

    const ifb_internal ifb_b8 asset_manager_shut_down (IFBEngineAssetManager& asset_manager_ref);
    const ifb_internal ifb_b8 asset_manager_update    (IFBEngineAssetManager& asset_manager_ref);
};


#endif //IFB_ENGINE_INTERNAL_ASSET_HPP