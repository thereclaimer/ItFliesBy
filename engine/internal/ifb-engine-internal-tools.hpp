#ifndef IFB_ENGINE_INTERNAL_TOOLS_HPP
#define IFB_ENGINE_INTERNAL_TOOLS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineTools;
struct IFBEngineToolsMemory;
struct IFBEngineToolsAssets;
struct IFBEngineToolsAssetFileBuilder;

/**********************************************************************************/
/* TOOLS MEMORY                                                                   */
/**********************************************************************************/

struct IFBEngineToolsMemoryAssets {
    ifb_u32 asset_builder_arena_pool_handle;
};

struct IFBEngineToolsMemory {
    ifb_u32 tools_arena_pool_handle;
};

namespace ifb_engine_tools {

    // const ifb_b8 
    // memory_reserve(
    //     IFBEngineMemory*            in_memory_ptr,
    //     IFBEngineToolsMemory&       out_memory_tools_ref);
};

/**********************************************************************************/
/* ASSET TOOLS                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_SHADERS "Shaders"
#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_IMAGES  "Images"
#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_SOUNDS  "Sounds"
#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_DIALOG  "Dialog"

const ifb_cstr IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_LOOKUP[] = {
    IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_SHADERS, // IFBEngineAssetFileId_Shaders
    IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_IMAGES,  // IFBEngineAssetFileId_Images
    IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_SOUNDS,  // IFBEngineAssetFileId_Sounds
    IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_DIALOG   // IFBEngineAssetFileId_Dialog
};

#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_LENGTH_MAX 256

namespace ifb_engine_tools {

    inline const ifb_cstr 
    asset_file_builder_table_name_lookup(
        const IFBEngineAssetFileId file_id) {

        const ifb_cstr asset_table_name = 
            (file_id >= IFBEngineAssetFileId_Count)
            ? NULL 
            : IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_TABLE_NAME_LOOKUP[file_id];

        return(asset_table_name);
    }
};

struct IFBEngineToolsAssetFileBuilder {
    ifb_b8                     open;
    ifb_b8                     selected_file;
    IFBEngineAssetFileId       selected_file_id;
    ifb_u32                    file_arena_csv;
    ifb_u32                    file_arena_asset;
    ifb_char                   file_path_csv   [IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_LENGTH_MAX];
    ifb_char                   file_path_asset [IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_LENGTH_MAX];    
};

namespace ifb_engine_tools {

    ifb_internal const ifb_b8 asset_file_builder_render         (IFBEngineToolsAssetFileBuilder& asset_file_builder_ref);
    ifb_internal const ifb_b8 asset_file_builder_combo          (IFBEngineToolsAssetFileBuilder& asset_file_builder_ref);
    ifb_internal const ifb_b8 asset_file_builder_file_selection (IFBEngineToolsAssetFileBuilder& asset_file_builder_ref);

};

struct IFBEngineToolsAssets {
    IFBEngineToolsAssetFileBuilder file_builder;
};


/**********************************************************************************/
/* TOOLS WINDOW                                                                   */
/**********************************************************************************/

#define IFB_ENGINE_TOOLS_MEMORY_ARENA_POOL_NAME "ENGINE TOOLS"
#define IFB_ENGINE_TOOLS_MEMORY_ARENA_SIZE  r_memory_size_kilobytes(64)
#define IFB_ENGINE_TOOLS_MEMORY_ARENA_COUNT 1024  

struct IFBEngineTools {
    IFBEngineToolsMemory memory;
    IFBEngineToolsAssets assets;
    ifb_b8               imgui_demo;
};

namespace ifb_engine_tools {

    // ifb_internal const r_b8 
    // tools_start_up(
    //     IFBEngineMemory* in_memory_ptr,
    //     IFBEngineTools&     out_tools_ref);
    
    ifb_internal const ifb_b8 tools_render_all (IFBEngineTools& tools_ref);
    ifb_internal const ifb_b8 tools_menu_bar   (IFBEngineTools& tools_ref);
};

#endif //IFB_ENGINE_INTERNAL_TOOLS_HPP