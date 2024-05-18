#ifndef ITFLIESBY_ENGINE_DEVTOOLS_HPP
#define ITFLIESBY_ENGINE_DEVTOOLS_HPP

#include "itfliesby-engine.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_core.h>

struct ItfliesbyEngineDevtools {
    ImGuiContext* imgui_context;
    ImGuiIO*      imgui_io;
};


#endif //ITFLIESBY_ENGINE_DEVTOOLS_HPP