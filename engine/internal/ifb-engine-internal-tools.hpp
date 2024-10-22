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

struct IFBEngineToolsAssetFileBuilder {
    r_b8 open;
};

namespace ifb_engine {

    ifb_internal const ifb_b8 
    tools_asset_file_builder_render(IFBEngineToolsAssetFileBuilder& asset_file_builder_ref);
};

struct IFBEngineToolsAssets {
    IFBEngineToolsAssetFileBuilder file_builder;
};


/**********************************************************************************/
/* TOOLS WINDOW                                                                   */
/**********************************************************************************/

struct IFBEngineTools {
    IFBEngineToolsAssets assets;
};

namespace ifb_engine {

    ifb_internal const r_b8 tools_render   (IFBEngineTools& tools_ref);
    ifb_internal const r_b8 tools_menu_bar (IFBEngineTools& tools_ref);
};

#endif //IFB_ENGINE_INTERNAL_TOOLS_HPP