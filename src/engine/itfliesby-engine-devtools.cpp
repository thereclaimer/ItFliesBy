#pragma once

#include "itfliesby-engine-devtools.hpp"

internal ItfliesbyEngineDevtools
itfliesby_engine_devtools_create_and_init() {

    ItfliesbyEngineDevtools dev_tools = {0};

    glewInit();

    dev_tools.imgui_context = (ImGuiContext*)platform_api.imgui_init(platform_api.window);

    return(dev_tools);
}

internal void
itfliesby_engine_devtools_update(
    ItfliesbyEngine* engine) {

    //TODO: tools aren't displaying, but they aren't necessary right now

    ItfliesbyEngineDevtools* dev_tools = &engine->dev_tools;

    itfliesby_engine_devtools_frame_start(
        dev_tools->imgui_context
    );
    
    ImGui::ShowDemoWindow();

    itfliesby_engine_devtools_frame_end();
}
