#pragma once

#include "itfliesby-engine-devtools.hpp"

internal ItfliesbyEngineDevtools
itfliesby_engine_devtools_create_and_init() {

    ItfliesbyEngineDevtools dev_tools = {0};

    glewInit();

    dev_tools.imgui_context = (ImGuiContext*)platform_api.imgui_init(platform_api.window);
    ImGui::SetCurrentContext(dev_tools.imgui_context);

    return(dev_tools);
}

internal void
itfliesby_engine_devtools_update(
    ItfliesbyEngine* engine) {

    handle platform_window_handle = platform_api.window;

    //start frame
    platform_api.imgui_frame_start(platform_window_handle);

    ImGui::ShowDemoWindow();

    //end frame
    platform_api.imgui_frame_end(platform_window_handle); 
}
