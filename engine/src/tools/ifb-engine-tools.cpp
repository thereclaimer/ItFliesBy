#pragma once

#include "ifb-engine-internal-tools.hpp"

#include "ifb-engine-tools-asset-file-builder.cpp"

ifb_internal const r_b8 
ifb_engine::tools_render(
    IFBEngineTools& tools_ref) {

    //tools window start
    if (!ImGui::Begin("IFBEngine Tools",NULL,ImGuiWindowFlags_MenuBar)) {
        return(false);
    }

    ifb_b8 result = true;

    //render the menu bar
    result &= ifb_engine::tools_menu_bar(tools_ref);

    //render the other windows
    result &= ifb_engine::tools_asset_file_builder_render(tools_ref.assets.file_builder);

    //tools window end
    ImGui::End();

    return(result);
}

ifb_internal const r_b8 
ifb_engine::tools_menu_bar(
    IFBEngineTools& tools_ref) {

    //menu bar start
    if (!ImGui::BeginMenuBar()) {
        return(false);
    }

    //assets
    if (ImGui::BeginMenu("Assets")) {

        //asset file builder
        ImGui::MenuItem("Asset File Builder",NULL,(bool*)&tools_ref.assets.file_builder.open);        
        ImGui::EndMenu();
    }

    //menu bar end
    ImGui::EndMenuBar();

    return(true);
}
