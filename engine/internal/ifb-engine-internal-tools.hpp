#ifndef IFB_ENGINE_INTERNAL_TOOLS_HPP
#define IFB_ENGINE_INTERNAL_TOOLS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineTools;
struct IFBEngineToolsAssets;
struct IFBEngineToolsAssetFileBuilder;

/**********************************************************************************/
/* ASSET TOOLS                                                                    */
/**********************************************************************************/


#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_SHADERS "ItFliesBy.AssetBuilder.Shaders.csv"
#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_IMAGES  "ItFliesBy.AssetBuilder.Images.csv"
#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_SOUNDS  "ItFliesBy.AssetBuilder.Sounds.csv"
#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_DIALOG  "ItFliesBy.AssetBuilder.Dialog.csv"

const ifb_cstr IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_LOOKUP_TABLE[] = {
    IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_SHADERS,
    IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_IMAGES,
    IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_SOUNDS,
    IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_PATH_DIALOG
};

#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_FILE_REGION_NAME       "ASSET BUILDER"
#define IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_FILE_REGION_ARENA_SIZE r_memory_size_megabytes(64)

struct IFBEngineToolsAssetFileBuilderTable {
    RMemoryRegionHandle        region;
    RMemoryArenaHandle         file_arena[IFBEngineAssetFileId_Count];
    IFBEnginePlatformFileIndex file_index[IFBEngineAssetFileId_Count];
};

struct IFBEngineToolsAssetFileBuilder {
    r_b8                                open;
    r_b8                                selected_file;
    IFBEngineAssetFileId                selected_file_id;
    IFBEngineToolsAssetFileBuilderTable file_table;
};

struct IFBEngineToolsAssetFileBuilderCsv {
    IFBEngineAssetFileId       asset_file_id;
    IFBEnginePlatformFileIndex csv_file_index;
    RMemoryArenaHandle         csv_file_arena;
};

namespace ifb_engine {

    inline const ifb_cstr
    tools_asset_file_builder_lookup_path(
        const IFBEngineAssetFileId file_id) {

        if (file_id >= IFBEngineAssetFileId_Count) {
            return(NULL);
        }

        const ifb_cstr path = IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_LOOKUP_TABLE[file_id];

        return(path);
    }

    ifb_internal const ifb_b8 
    tools_asset_file_builder_render(IFBEngineToolsAssetFileBuilder& asset_file_builder_ref);

    ifb_internal const ifb_b8
    tools_asset_file_builder_get_csv(
        IFBEngineToolsAssetFileBuilder&     in_asset_file_builder_ref,
        IFBEngineToolsAssetFileBuilderCsv& out_asset_file_builder_csv);

    ifb_internal const ifb_b8 
    tools_asset_file_builder_render_csv(
        IFBEngineToolsAssetFileBuilderCsv& asset_file_csv);
};

struct IFBEngineToolsAssets {
    IFBEngineToolsAssetFileBuilder file_builder;
};


/**********************************************************************************/
/* TOOLS WINDOW                                                                   */
/**********************************************************************************/

struct IFBEngineTools {
    ifb_b8               imgui_demo;
    IFBEngineToolsAssets assets;
};

namespace ifb_engine {

    ifb_internal const r_b8 tools_render   (IFBEngineTools& tools_ref);
    ifb_internal const r_b8 tools_menu_bar (IFBEngineTools& tools_ref);
};

#endif //IFB_ENGINE_INTERNAL_TOOLS_HPP