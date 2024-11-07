#pragma once

#include "ifb-engine-memory.cpp"
#include "ifb-engine-core.cpp"
#include "ifb-engine-asset.cpp"
#include "ifb-engine-tools.cpp"


#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/
namespace ifb_engine {

    const ifb_b8 engine_imgui_validate(ImGuiContext* imgui_context);
};

/**********************************************************************************/
/* EXTERNAL                                                                       */
/**********************************************************************************/

ifb_external const ifb_b8 
ifb_engine::engine_startup(
    ImGuiContext*            imgui_context,
    IFBEnginePlatformApi     platform_api) {

    ifb_b8 result = true;

    //platform api
    result &= ifb_engine::platform_api_validate(platform_api);

    //memory manager
    result &= ifb_engine::memory_manager_start_up(_ifb_engine.memory_manager);
    
    //engine core
    result &= ifb_engine::core_initialize(_ifb_engine.core);
    
    //imgui
    result &= ifb_engine::engine_imgui_validate(imgui_context);
    

    //asset manager
    result &= ifb_engine::asset_manager_start_up(
        _ifb_engine.core.memory,
        _ifb_engine.asset_manager);

    //debug tools
    result &= ifb_engine_tools::tools_start_up(
        _ifb_engine.core.memory,
        _ifb_engine.tools);

    //we're done
    return(result);
}

ifb_external const ifb_b8
ifb_engine::engine_update(
    const IFBEngineHandle ifb_engine_handle) {

    if (!ifb_engine_handle) {
        return(false);
    }

    IFBEngine* engine_ptr = (IFBEngine*)ifb_engine_handle;

    ifb_engine_tools::tools_render_all(engine_ptr->tools);

    return(true);
}


ifb_external const ifb_b8
ifb_engine::engine_shutdown(
    const IFBEngineHandle ifb_engine_handle) {

    //TODO(SAM)

    return(true);
}

/**********************************************************************************/
/* INLINE                                                                         */
/**********************************************************************************/

inline const ifb_b8 
ifb_engine::engine_imgui_validate(
    ImGuiContext* imgui_context) {

    if (!imgui_context) {
        return(false);
    }

    //set the imgui context
    ImGui::SetCurrentContext(imgui_context);

    //set the imgui font
    ImGuiIO& imgui_io_ref   = ImGui::GetIO();
    ImFont*  imgui_font_ptr = imgui_io_ref.Fonts->AddFontFromMemoryCompressedBase85TTF(IFB_ENGINE_FONT_UI_SEGOEUI,18.0f);

    return (imgui_font_ptr != NULL);
}
