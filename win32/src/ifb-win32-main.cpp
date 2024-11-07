#pragma once

#include "ifb-win32.hpp"

r_internal r_s32 
ifb_win32_main(
    RWin32MainArgs& args) {

    _ifb_win32 = {0};

    //get monitor info
    r_win32::monitor_info(_ifb_win32.monitor_info);

    //configuration
    const r_size reservation_size_max              = r_mem::size_gigabytes(4);
    const r_size memory_manager_stack_size         = r_mem::size_megabytes(64);  
    const r_size platform_win32_arena_size         = r_mem::size_kilobytes(4);
    const r_size platform_win32_arena_count        = 64;
    const r_size platform_win32_window_size_width  = _ifb_win32.monitor_info.pixels_width;
    const r_size platform_win32_window_size_height = _ifb_win32.monitor_info.pixels_height;

    ifb_b8 startup_result = true;

    //create the context
    if (!r_win32::context_create(args)) {
        return(S_FALSE);
    }

    //initialize the dialog
    _ifb_win32.file_dialog_handle = r_win32::file_dialog_create(_ifb_win32.window_handle);

    //initialize the platform api
    ifb_win32::system_api_initialize(_ifb_win32.platform_api.system);
    ifb_win32::memory_api_initialize(_ifb_win32.platform_api.memory);
    ifb_win32::file_api_initialize(_ifb_win32.platform_api.file);
    ifb_win32::file_dialog_api_initialize(_ifb_win32.platform_api.file_dialog);

    //create the engine
    startup_result &= ifb_engine::engine_startup(
        _ifb_win32.imgui_context,
        _ifb_win32.platform_api);

    //create a region for our win32 systems
    startup_result &= ifb_engine::memory_arena_create_pool(
        IFB_WIN32_MEMORY_ARENA_TAG,
        IFB_WIN32_MEMORY_ARENA_SIZE_KILOBYTES,
        IFB_WIN32_MEMORY_ARENA_COUNT,
        _ifb_win32.memory.arena_pool);

    //create the window

#if 0
    _ifb_win32.window_handle = 
        r_win32::window_create_centered(
            "It Flies By",
            platform_win32_window_size_width,
            platform_win32_window_size_height,
            RColorFormat_RGBA,
            RWin32WindowUseImGui_No);
    
#else
    _ifb_win32.window_handle = 
        r_win32::window_create_centered(
            "It Flies By",
            1920,
            1080,
            RColorFormat_RGBA,
            RWin32WindowUseImGui_No);
#endif   

    if (!_ifb_win32.window_handle) {
        return(S_FALSE);
    }

    //create the opengl context
    _ifb_win32.rendering_context_handle = r_win32::rendering_create_opengl_context(_ifb_win32.window_handle); 
    if (!_ifb_win32.rendering_context_handle) {
        return(S_FALSE);
    }

    //create the imgui context
    _ifb_win32.imgui_context = r_win32::imgui_create_context(_ifb_win32.window_handle);
    if (!_ifb_win32.imgui_context) {
        return(S_FALSE);
    }

    //set the clear color
    RColor32Bit color_32 = {0};
    color_32.format = RColorFormat_RGBA;
    color_32.hex    = 0x282828FF;
    r_win32::rendering_set_clear_color(_ifb_win32.rendering_context_handle,color_32);


    //show the window
    r_win32::window_show(_ifb_win32.window_handle);

    //main window loop
    r_b8 running = true;
    while(running) {

        //start a new frame
        running &= r_win32::window_frame_start(_ifb_win32.window_handle);

        //update the engine        
        running &= ifb_engine::engine_update(_ifb_win32.engine_handle);

        //render the frame
        running &= r_win32::window_frame_render(_ifb_win32.window_handle);
    }

    //destroy the context
    if (!r_win32::context_destroy()) {
        return(S_FALSE);
    }

    //done
    return(S_OK);
}
