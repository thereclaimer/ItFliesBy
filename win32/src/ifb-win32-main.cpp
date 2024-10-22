#pragma once

#include "ifb-win32.hpp"

r_internal r_s32 
ifb_win32_main(
    RWin32MainArgs& args) {

    _ifb_win32 = {0};

    //get monitor info
    RWin32MonitorInfo win32_monitor_info;
    r_win32::monitor_info(win32_monitor_info);

    //configuration
    const r_size reservation_size_max              = r_mem::size_gigabytes(4);
    const r_size memory_manager_stack_size         = r_mem::size_megabytes(64);  
    const r_size platform_win32_arena_size         = r_mem::size_kilobytes(4);
    const r_size platform_win32_arena_count        = 64;
    const r_size platform_win32_window_size_width  = win32_monitor_info.pixels_width;
    const r_size platform_win32_window_size_height = win32_monitor_info.pixels_height;

    //create the context
    if (!r_win32::context_create(args)) {
        return(S_FALSE);
    }

    //create the memory manager
    if (!r_mem::memory_manager_create_win32(
        reservation_size_max,
        memory_manager_stack_size)) {

        return(S_FALSE);
    }

    //create the reservation
    _ifb_win32.memory_reservation = r_mem::reserve("IT FLIES BY",reservation_size_max);
    if (!_ifb_win32.memory_reservation) {
        return(S_FALSE);
    }

    //create a region for our win32 systems
    _ifb_win32.win32_region = 
        r_mem::region_create_arena_pool(
            _ifb_win32.memory_reservation,
            "WIN32 PLATFORM",
            platform_win32_arena_size,
            platform_win32_arena_count);

    //set the win32 region
    r_win32::context_set_memory_region(_ifb_win32.win32_region);

    //create the window

#if 0
    const RWin32WindowHandle window_handle = 
        r_win32::window_create_centered(
            "It Flies By",
            platform_win32_window_size_width,
            platform_win32_window_size_height,
            RColorFormat_RGBA,
            RWin32WindowUseImGui_No);
    
#else
    const RWin32WindowHandle window_handle = 
        r_win32::window_create_centered(
            "It Flies By",
            1920,
            1080,
            RColorFormat_RGBA,
            RWin32WindowUseImGui_No);
#endif   

    if (!window_handle) {
        return(S_FALSE);
    }

    //create the opengl context
    RWin32RenderingContextHandle rendering_context_handle = r_win32::rendering_create_opengl_context(window_handle); 
    if (!rendering_context_handle) {
        return(S_FALSE);
    }

    //create the imgui context
    ImGuiContext* imgui_context = r_win32::imgui_create_context(window_handle);
    if (!imgui_context) {
        return(S_FALSE);
    }

    //test file
    const RWin32FileHandle file_handle = r_win32::file_create_new("test.txt");

    //set the clear color
    RColor32Bit color_32 = {0};
    color_32.format = RColorFormat_RGBA;
    color_32.hex    = 0x282828FF;
    r_win32::rendering_set_clear_color(rendering_context_handle,color_32);


    //initialize the platform api
    IFBEnginePlatformApi platform_api;
    platform_api.file.open_read_only  = ifb_win32::file_open_read_only;
    platform_api.file.open_read_write = ifb_win32::file_open_read_write;
    platform_api.file.close           = ifb_win32::file_close;
    platform_api.file.size            = ifb_win32::file_size;
    platform_api.file.read            = ifb_win32::file_read;
    platform_api.file.write           = ifb_win32::file_write;

    //create the engine
    const IFBEngineHandle engine_handle = 
        ifb_engine::engine_startup(
            _ifb_win32.memory_reservation,
            imgui_context,
            platform_api);

    //show the window
    r_win32::window_show(window_handle);

    //main window loop
    r_b8 running = true;
    while(running) {

        //start a new frame
        running &= r_win32::window_frame_start(window_handle);

        //update the engine        
        running &= ifb_engine::engine_update(engine_handle);

        //render the frame
        running &= r_win32::window_frame_render(window_handle);
    }

    //destroy the context
    if (!r_win32::context_destroy()) {
        return(S_FALSE);
    }

    //done
    return(S_OK);
}
