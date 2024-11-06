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
};

struct IFBEngineAssetTableFilePointers {
    ifb_char*                   path_buffer;
    IFBEnginePlatformFileIndex* platform_index;
    ifb_size*                   size;
};

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_file_create_table(
        IFBEngineCoreMemory&      in_core_memory_ref,
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
        IFBEngineAssetTableIndexFile* asset_file_table_index;
        ifb_size*                     asset_file_data_size;
        ifb_size*                     asset_file_data_start;
    } column_ptr;
};

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_header_create_table(
        IFBEngineCoreMemory&        in_core_memory_ref,
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
    IFBEngineMemoryArenaHandle        asset_data_arena_handle;
};

struct IFBEngineAssetTableDataBlock {
    ifb_size data_block_count;
    struct {
        IFBEngineAssetTableIndexDataBlock* asset_table_index_header; 
        ifb_timems*                        time_ms_loaded;           
        ifb_timems*                        time_ms_last_accessed;    
        IFBEngineMemoryArenaHandle*        asset_data_arena_handle;  
    } column_ptr;
};


namespace ifb_engine {

    ifb_internal const ifb_b8 
    asset_data_block_create_table(
        IFBEngineCoreMemory&           in_core_memory_ref,
        IFBEngineAssetTableDataBlock& out_asset_table_data_block_ref);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineAssetMemoryTableFile {
    IFBEngineMemoryHandle path;
    IFBEngineMemoryHandle platform_file_index;
    IFBEngineMemoryHandle size;
};

struct IFBEngineAssetMemoryTableHeader {
    IFBEngineMemoryHandle name_buffer;
    IFBEngineMemoryHandle file_table_index;
    IFBEngineMemoryHandle file_data_size;
    IFBEngineMemoryHandle file_data_start;
};

struct IFBEngineAssetMemoryTableDataBlock {
    IFBEngineMemoryHandle asset_table_index_header;
    IFBEngineMemoryHandle time_ms_loaded;
    IFBEngineMemoryHandle time_ms_last_accessed;
    IFBEngineMemoryHandle asset_data_arena_handle;
};

struct IFBEngineAssetMemory {
    struct {
        IFBEngineAssetMemoryTableFile      table_file;
        IFBEngineAssetMemoryTableHeader    table_header;
        IFBEngineAssetMemoryTableDataBlock table_data_block;
    } system_arena_handles;
};

namespace ifb_engine {

    const ifb_b8 
    asset_memory_reserve(
        IFBEngineCoreMemory&   in_core_memory_ref,
        IFBEngineAssetMemory& out_asset_memory_ref);

    const ifb_b8
    asset_memory_pointers_file_table(
        IFBEngineAssetMemory&             in_asset_memory_ref,
        IFBEngineAssetTableFilePointers& out_asset_file_table_pointers_ref);
};

/**********************************************************************************/
/* ASSET MANAGER                                                                  */
/**********************************************************************************/


struct IFBEngineAssetManager {
    IFBEngineAssetMemory memory;
    struct {
        IFBEngineAssetTableFile      file;
        IFBEngineAssetTableHeader    header;
        IFBEngineAssetTableDataBlock data_block;
    } asset_tables;
    ifb_timems time_ms_initialized;
};

namespace ifb_engine {

    ifb_internal const ifb_b8
    asset_manager_start_up(
        IFBEngineMemoryArenaHandle& in_engine_core_memory_arena_handle_ref,
        IFBEngineAssetManager&     out_asset_manager_ref);

    const ifb_internal ifb_b8 asset_manager_shut_down (IFBEngineAssetManager& asset_manager_ref);
    const ifb_internal ifb_b8 asset_manager_update    (IFBEngineAssetManager& asset_manager_ref);
};


#endif //IFB_ENGINE_INTERNAL_ASSET_HPP