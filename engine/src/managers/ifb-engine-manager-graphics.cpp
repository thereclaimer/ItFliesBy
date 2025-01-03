#pragma once

#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-platform.hpp"

inline ifb_void 
ifb_engine::graphics_manager_create_window (
          IFBEngineManagerGraphics* graphics_manager_ptr,
    const ifb_cstr                  window_title,
    const IFBWindowFlags            window_flags) {

    //get window and monitors
    IFBEngineManagerGraphicsData graphics_data;
    graphics_data.query = (
        IFBEngineMangerGraphicsQuery_Window |
        IFBEngineMangerGraphicsQuery_Monitors);

    ifb_engine::graphics_manager_data_query(
        graphics_manager_ptr,
        graphics_data);


    //find the primary monitor
    const IFBMonitor* monitor_primary_ptr = ifb_graphics::monitor_find_primary(
        graphics_manager_ptr->monitor_count,
        graphics_data.monitors);
    ifb_macro_assert(monitor_primary_ptr);

    //set the flags and monitor id in the window
    graphics_data.window->flags      = window_flags;
    graphics_data.window->monitor_id = monitor_primary_ptr->id;

    //set window properties based on the monitor
    ifb_graphics::window_set_resolution_based_on_monitor_aspect_ratio(window_ptr, monitor_primary_ptr);
    ifb_graphics::window_set_position_to_monitor_center              (window_ptr, monitor_primary_ptr);

    //result of platform window initialization
    ifb_b8 result = true;

    //instruct the platform to create a window handle
    result &= ifb_engine::platform_window_create(
        window_title,
        graphics_data.window->resolution.width,
        graphics_data.window->resolution.height,
        graphics_data.window->position.x,
        graphics_data.window->position.y);

    //process flags
    result &= ifb_graphics::window_flags_use_opengl(window_flags) ? ifb_engine::platform_window_opengl_init() : true;
    result &= ifb_graphics::window_flags_is_visible(window_flags) ? ifb_engine::platform_window_show()        : true;
    
    if (ifb_graphics::window_flags_use_imgui(window_flags)) {

        ImGuiContext* imgui_context = ifb_engine::platform_window_imgui_init();
        ImGui::SetCurrentContext(imgui_context);
        result &= imgui_context != NULL;
    }

    //sanity check, and we're done
    ifb_macro_assert(result);
}

inline ifb_void 
ifb_engine::graphics_manager_create_viewport (
    IFBEngineManagerGraphics* graphics_manager_ptr) {

    //get the window and viewport
    IFBEngineManagerGraphicsData graphics_data;
    graphics_data.query = (
        IFBEngineMangerGraphicsQuery_Window |
        IFBEngineMangerGraphicsQuery_Viewport);

    ifb_engine::graphics_manager_data_query(
        graphics_manager_ptr,
        graphics_data);

    //make sure we can create the viewport
    const ifb_b8 can_create_viewport = 
        ifb_graphics::window_flags_is_visible(graphics_data.window->flags) &&
        ifb_graphics::window_flags_use_opengl(graphics_data.window->flags);
    ifb_macro_assert(can_create_viewport);

    //the position is at the window's origin, but matches its dimensions
    graphics_data.viewport->position.x        = 0;
    graphics_data.viewport->position.y        = 0;
    graphics_data.viewport->dimensions.width  = graphics_data.window->resolution.width;
    graphics_data.viewport->dimensions.height = graphics_data.window->resolution.height;

    //set the clear color, for now its hardcoded as gray
    viewport_ptr->clear_color.red   = ifb_macro_color_normalize_byte(0x28);
    viewport_ptr->clear_color.green = ifb_macro_color_normalize_byte(0x28);
    viewport_ptr->clear_color.blue  = ifb_macro_color_normalize_byte(0x28);
    viewport_ptr->clear_color.alpha = ifb_macro_color_normalize_byte(0xFF);

    //initialize the viewport
    ifb_gl::viewport_initialize(graphics_data.viewport);
}

inline ifb_void 
ifb_engine::graphics_manager_style_imgui(
    IFBEngineManagerGraphics* graphics_manager_ptr) {

    //get the window
    IFBEngineManagerGraphicsData graphics_data;
    graphics_data.query = IFBEngineMangerGraphicsQuery_Window;

    ifb_engine::graphics_manager_data_query(
        graphics_manager_ptr,
        graphics_data);

    //sanity check, do we have imgui
    ImGuiContext* imgui_context = ImGui::GetCurrentContext();
    const ifb_b8  imgui_is_used = ifb_graphics::window_flags_use_imgui(graphics_data.window->flags);
    ifb_macro_assert(imgui_is_used && imgui_context);

    //get our local font buffer
    const ifb_char* font_buffer = ifb_graphics::font_segoeui_data();
    ifb_macro_assert(font_buffer);

    //load the font
    ImGuiIO& imgui_io = ImGui::GetIO();
    ImFont* imgui_font = imgui_io.Fonts->AddFontFromMemoryCompressedBase85TTF(
        font_buffer,
        18.0f,
        NULL,
        NULL);

    //default style dark
    ImGui::StyleColorsDark();
}

inline ifb_void 
ifb_engine::graphics_manager_frame_start(
    IFBEngineManagerGraphics* graphics_manager_ptr) {

    //start a new frame
    const ifb_b8 result = ifb_engine::platform_window_frame_start();
    ifb_macro_assert(result);

    //get the viewport
    IFBEngineManagerGraphicsData graphics_data;
    graphics_data.query = IFBEngineMangerGraphicsQuery_Viewport;

    ifb_engine::graphics_manager_data_query(
        graphics_manager_ptr,
        graphics_data);

    //clear the viewport
    ifb_gl::viewport_clear(graphics_data.viewport);
}

inline ifb_void 
ifb_engine::graphics_manager_frame_render(
    IFBEngineManagerGraphics* graphics_manager_ptr) {

    const ifb_b8 result = ifb_engine::platform_window_frame_render();
    ifb_macro_assert(result);
}

inline const IFBMonitor*
ifb_engine::graphics_manager_get_monitor(
    const IFBEngineManagerGraphics* graphics_manager_ptr, 
    const ifb_u32                   monitor_index) {

    //sanity check
    ifb_macro_assert(monitor_index < graphics_manager_ptr->monitor_count);

    //get the monitors
    IFBEngineManagerGraphicsData graphics_data;
    graphics_data.query = IFBEngineMangerGraphicsQuery_Monitors;

    ifb_engine::graphics_manager_data_query(
        graphics_manager_ptr,
        graphics_data);

    //get the monitor info at the index
    const IFBMonitor* monitor_ptr = &graphics_data.monitors[monitor_index]; 

    //we're done
    return(monitor_ptr);
}

inline ifb_void 
ifb_engine::graphics_manager_data_query(
    const IFBEngineManagerGraphics*     graphics_manager_ptr,
          IFBEngineManagerGraphicsData& graphics_manager_data_ref) {

    //get the data start and query
    const ifb_address                  data_start = graphics_manager_ptr->memory_start;
    const IFBEngineMangerGraphicsQuery data_query = graphics_manager_data_ref.query;

    //get the addresses of our requested data
    const ifb_address address_window   = (data_query & IFBEngineMangerGraphicsQuery_Window)   ? (data_start + graphics_manager_data_ref.offset_window)        : 0;
    const ifb_address address_viewport = (data_query & IFBEngineMangerGraphicsQuery_Monitors) ? (data_start + graphics_manager_data_ref.offset_viewport)      : 0;
    const ifb_address address_monitors = (data_query & IFBEngineMangerGraphicsQuery_Viewport) ? (data_start + graphics_manager_data_ref.offset_monitor_array) : 0;

    //cast the pointers
    graphics_manager_data_ref.window   =     (IFBWindow*)address_window;
    graphics_manager_data_ref.viewport = (IFBGLViewport*)address_viewport;
    graphics_manager_data_ref.monitors =    (IFBMonitor*)address_monitors;
}