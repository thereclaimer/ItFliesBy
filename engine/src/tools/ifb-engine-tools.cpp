#pragma once

#include "ifb-engine-internal-tools.hpp"

#include "ifb-engine-tools-asset-file-builder.cpp"
#include "ifb-engine-tools-memory.cpp"

ifb_internal const r_b8 
ifb_engine_tools::tools_start_up(
    IFBEngineCoreMemory& in_core_memory,
    IFBEngineTools&     out_tools_ref) {

    ifb_b8 result = true;

    //reserve the memory
    result &= ifb_engine_tools::memory_reserve(
        in_core_memory,
        out_tools_ref.memory);

    //we're done
    return(result);
}

ifb_internal const r_b8 
ifb_engine_tools::tools_render_all(
    IFBEngineTools& tools_ref) {

    ifb_b8 result = true;

    //render the menu bar
    result &= ifb_engine_tools::tools_menu_bar(tools_ref);

    //render the other windows
    result &= ifb_engine_tools::asset_file_builder_render(tools_ref.assets.file_builder);

    if (tools_ref.imgui_demo) {
        ImGui::ShowDemoWindow((bool*)&tools_ref.imgui_demo);
    }

    return(result);
}

ifb_internal const r_b8 
ifb_engine_tools::tools_menu_bar(
    IFBEngineTools& tools_ref) {

    //menu bar start
    if (!ImGui::BeginMainMenuBar()) {
        return(false);
    }

    //assets
    if (ImGui::BeginMenu("Assets")) {

        //asset file builder
        ImGui::MenuItem("Asset File Builder",NULL,(bool*)&tools_ref.assets.file_builder.open);        
        ImGui::EndMenu();
    }

    //imgui
    if (ImGui::BeginMenu("ImGui")) {

        //asset file builder
        ImGui::MenuItem("ImGui Demo",NULL,(bool*)&tools_ref.imgui_demo);        
        ImGui::EndMenu();
    }

    //menu bar end
    ImGui::EndMainMenuBar();

    return(true);
}
