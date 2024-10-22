#pragma once

#include "ifb-engine-internal-tools.hpp"

ifb_internal const ifb_b8 
ifb_engine::tools_asset_file_builder_render(
    IFBEngineToolsAssetFileBuilder& asset_file_builder_ref) {

    //if the window isn't open, we're done
    if (!asset_file_builder_ref.open) {
        return(true);
    }

    //window start
    if (!ImGui::Begin("Asset File Builder",(bool*)&asset_file_builder_ref.open)) {
        return(false);
    }


    //window end
    ImGui::End();

    //we're done
    return(true);
}