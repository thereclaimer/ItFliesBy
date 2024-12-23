#pragma once

#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-platform.hpp"

inline ifb_void 
ifb_engine::graphics_manger_initialize(
    IFBEngineGraphicsManager* graphics_manager_ptr,
    IFBEngineMemory*          memory_ptr) {

    //sanity check
    ifb_macro_assert(graphics_manager_ptr);
    ifb_macro_assert(memory_ptr);

    //first, we need to get the number of monitors the platform has available
    graphics_manager_ptr->monitor_count = ifb_engine::platform_monitor_count();
    ifb_macro_assert(graphics_manager_ptr->monitor_count > 0);

    //commit memory for the manager
    ifb_engine::graphics_manager_commit_memory(
        graphics_manager_ptr->memory,
        memory_ptr,
        graphics_manager_ptr->monitor_count);

    //get the monitor array
    IFBMonitor* monitor_array_pointer = ifb_engine::graphics_manager_get_monitor_array_pointer(graphics_manager_ptr->memory);
    ifb_macro_assert(monitor_array_pointer);

    //get the monitor information from the platform
    ifb_engine::platform_monitor_info(
        graphics_manager_ptr->monitor_count,
        monitor_array_pointer);
}

inline ifb_void
ifb_engine::graphics_manager_commit_memory(
          IFBEngineGraphicsManagerMemory& graphics_manager_memory,
          IFBEngineMemory*                memory_ptr,
    const ifb_u32                         monitor_count) {
    
    //calculate the size of the monitor array and other structures
    const ifb_u16 window_size        = ifb_macro_align_size_struct(IFBWindow); 
    const ifb_u16 viewport_size      = ifb_macro_align_size_struct(IFBGLViewport);
    const ifb_u16 monitor_array_size = ifb_macro_size_array(IFBMonitor, monitor_count);

    //total commit size
    const ifb_u32 commit_size = 
        window_size        + 
        viewport_size      +
        monitor_array_size;

    //commit memory
    const IFBIDCommit commit_id            = ifb_engine::memory_commit(memory_ptr,commit_size);
    const ifb_address commit_start         = ifb_engine::memory_get_commit_address(memory_ptr,commit_id);
    const ifb_u16     offset_window        = 0;
    const ifb_u16     offset_viewport      = window_size;
    const ifb_u16     offset_monitor_array = viewport_size;

    //set memory properties
    graphics_manager_memory.start                = commit_start;
    graphics_manager_memory.offset_window        = offset_window;
    graphics_manager_memory.offset_viewport      = offset_viewport;
    graphics_manager_memory.offset_monitor_array = offset_monitor_array;
    graphics_manager_memory.commit_id            = commit_id;
}

inline ifb_void 
ifb_engine::graphics_manager_create_window (
          IFBEngineGraphicsManager* graphics_manager_ptr,
    const ifb_cstr                  window_title,
    const IFBWindowFlags            window_flags) {
    
    //get the monitor array and find the primary monitor
    const IFBMonitor* monitor_array_ptr   = ifb_engine::graphics_manager_get_monitor_array_pointer(graphics_manager_ptr->memory); 
    const IFBMonitor* monitor_primary_ptr = ifb_graphics::monitor_find_primary(graphics_manager_ptr->monitor_count,monitor_array_ptr); 
    ifb_macro_assert(monitor_primary_ptr);

    //get the monitor and window
    IFBWindow* window_ptr = ifb_engine::graphics_manager_get_window_pointer(graphics_manager_ptr->memory);

    //set the flags and monitor id
    window_ptr->flags      = window_flags;
    window_ptr->monitor_id = monitor_primary_ptr->id;

    //set window properties based on the monitor
    ifb_graphics::window_set_resolution_based_on_monitor_aspect_ratio(window_ptr, monitor_primary_ptr);
    ifb_graphics::window_set_position_to_monitor_center              (window_ptr, monitor_primary_ptr);

    //result of platform window initialization
    ifb_b8 result = true;

    //instruct the platform to create a window handle
    result &= ifb_engine::platform_window_create(
        window_title,
        window_ptr->resolution.width,
        window_ptr->resolution.height,
        window_ptr->position.x,
        window_ptr->position.y);

    //process flags
    result &= ifb_graphics::window_flags_use_opengl(window_flags) ? ifb_engine::platform_window_opengl_init() : true;
    result &= ifb_graphics::window_flags_is_visible(window_flags) ? ifb_engine::platform_window_show()        : true;
    
    if (ifb_graphics::window_flags_use_imgui (window_flags)) {

        ImGuiContext* imgui_context = ifb_engine::platform_window_imgui_init();
        ImGui::SetCurrentContext(imgui_context);
        result &= imgui_context != NULL;
    }

    //sanity check, and we're done
    ifb_macro_assert(result);
}

inline ifb_void 
ifb_engine::graphics_manager_create_viewport (
    IFBEngineGraphicsManager* graphics_manager_ptr) {

    //get the window and viewport
    IFBWindow*     window_ptr   = ifb_engine::graphics_manager_get_window_pointer(graphics_manager_ptr->memory);
    IFBGLViewport* viewport_ptr = ifb_engine::graphics_manager_get_viewport      (graphics_manager_ptr->memory);

    //sanity check
    ifb_macro_assert(window_ptr);
    ifb_macro_assert(viewport_ptr);

    //make sure we can create the viewport
    const ifb_b8 can_create_viewport = 
        ifb_graphics::window_flags_is_visible(window_ptr->flags) &&
        ifb_graphics::window_flags_use_opengl(window_ptr->flags);
    ifb_macro_assert(can_create_viewport);

    //the position is at the window's origin, but matches its dimensions
    viewport_ptr->position.x        = 0;
    viewport_ptr->position.y        = 0;
    viewport_ptr->dimensions.width  = window_ptr->resolution.width;
    viewport_ptr->dimensions.height = window_ptr->resolution.height;

    //set the clear color, for now its hardcoded as gray
    viewport_ptr->clear_color.red   = ifb_macro_color_normalize_byte(0x28);
    viewport_ptr->clear_color.green = ifb_macro_color_normalize_byte(0x28);
    viewport_ptr->clear_color.blue  = ifb_macro_color_normalize_byte(0x28);
    viewport_ptr->clear_color.alpha = ifb_macro_color_normalize_byte(0xFF);

    //initialize the viewport
    ifb_gl::viewport_initialize(viewport_ptr);
}

inline ifb_void 
ifb_engine::graphics_manager_style_imgui(
    IFBEngineGraphicsManager* graphics_manager_ptr) {

    //get the window
    IFBWindow* window_ptr = ifb_engine::graphics_manager_get_window_pointer(graphics_manager_ptr->memory);

    //sanity check, do we have imgui
    ImGuiContext* imgui_context = ImGui::GetCurrentContext();
    const ifb_b8  imgui_is_used = ifb_graphics::window_flags_use_imgui(window_ptr->flags);
    ifb_macro_assert(imgui_is_used && imgui_context);

    //get our local font buffer
    const ifb_char* font_buffer = ifb_graphics::font_segoeui_data();
    ifb_macro_assert(font_buffer);

    //load the font
    ImGuiIO& imgui_io = ImGui::GetIO();
    ImFont* imgui_font = imgui_io.Fonts->AddFontFromMemoryCompressedBase85TTF(
        font_buffer,
        14.0f,
        NULL,
        NULL);

    //default style dark
    ImGui::StyleColorsDark();
}

inline ifb_void 
ifb_engine::graphics_manager_frame_start(
    IFBEngineGraphicsManager* graphics_manager_ptr) {

    //start a new frame
    const ifb_b8 result = ifb_engine::platform_window_frame_start();
    ifb_macro_assert(result);

    //clear the viewport
    IFBGLViewport* viewport = ifb_engine::graphics_manager_get_viewport(graphics_manager_ptr->memory);
    ifb_gl::viewport_clear(viewport);
}

inline ifb_void 
ifb_engine::graphics_manager_frame_render(
    IFBEngineGraphicsManager* graphics_manager_ptr) {

    const ifb_b8 result = ifb_engine::platform_window_frame_render();
    ifb_macro_assert(result);
}

inline const IFBMonitor*
ifb_engine::graphics_manager_get_monitor(
    const IFBEngineGraphicsManager* graphics_manager_ptr, 
    const ifb_u32                   monitor_index) {

    //sanity check
    ifb_macro_assert(monitor_index < graphics_manager_ptr->monitor_count);

    //get the monitor array
    const IFBMonitor* monitor_array_ptr = ifb_engine::graphics_manager_get_monitor_array_pointer(graphics_manager_ptr->memory);

    //get the monitor info at the index
    const IFBMonitor* monitor_ptr = &monitor_array_ptr[monitor_index];

    //we're done
    return(monitor_ptr);
}

inline IFBWindow*  
ifb_engine::graphics_manager_get_window_pointer(
    const IFBEngineGraphicsManagerMemory& graphics_manager_memory_ref) {

    //get the address
    const ifb_address memory_start   = graphics_manager_memory_ref.start;
    const ifb_address window_address = memory_start + graphics_manager_memory_ref.offset_window;

    //cast to a pointer
    IFBWindow* window_pointer = (IFBWindow*)window_address;

    //we're done
    return(window_pointer);
}

inline IFBMonitor*
ifb_engine::graphics_manager_get_monitor_array_pointer(
    const IFBEngineGraphicsManagerMemory& graphics_manager_memory_ref) {

    //get the address
    const ifb_address memory_start          = graphics_manager_memory_ref.start;
    const ifb_address monitor_array_address = memory_start + graphics_manager_memory_ref.offset_monitor_array;

    //cast to a pointer
    IFBMonitor* monitor_array_pointer = (IFBMonitor*)monitor_array_address;

    //we're done
    return(monitor_array_pointer);
}

inline IFBGLViewport* 
ifb_engine::graphics_manager_get_viewport(
    const IFBEngineGraphicsManagerMemory& graphics_manager_memory_ref) {

    //get the address
    const ifb_address memory_start     = graphics_manager_memory_ref.start;
    const ifb_address viewport_address = memory_start + graphics_manager_memory_ref.offset_viewport;

    //cast to a pointer
    IFBGLViewport* viewport_pointer = (IFBGLViewport*)viewport_address;

    //we're done
    return(viewport_pointer);
}
