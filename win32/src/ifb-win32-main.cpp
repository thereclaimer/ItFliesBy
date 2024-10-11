#pragma once

#include "ifb-win32.hpp"

r_internal r_s32 
ifb_win32_main(
    RWin32MainArgs& args) {

    //configuration
    const r_size reservation_size_max              = r_mem::size_gigabytes(4);
    const r_size memory_manager_stack_size         = r_mem::size_megabytes(64);  
    const r_size platform_win32_arena_size         = r_mem::size_kilobytes(4);
    const r_size platform_win32_arena_count        = 64;
    const r_size platform_win32_window_size_width  = 1920;
    const r_size platform_win32_window_size_height = 1080;

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
    const RMemoryReservationHandle ifb_memory_reservation_handle = 
        r_mem::reserve("IT FLIES BY",reservation_size_max);
    
    if (!ifb_memory_reservation_handle) {
        return(S_FALSE);
    }

    //create a region for our win32 systems
    const RMemoryRegionHandle win32_region_handle = 
        r_mem::region_create_arena_pool(
            ifb_memory_reservation_handle,
            "WIN32 PLATFORM",
            platform_win32_arena_size,
            platform_win32_arena_count);

    //set the win32 region
    r_win32::context_set_memory_region(win32_region_handle);

    //create the window
    const RHNDWin32Window window_handle = 
        r_win32::window_create_centered(
            "It Flies By",
            platform_win32_window_size_width,
            platform_win32_window_size_height,
            RColorFormat_RGBA,
            RWin32WindowUseImGui_No);
    if (!window_handle) {
        return(S_FALSE);
    }

    //create the opengl context
    RHNDWin32RenderingContext rendering_context_handle = r_win32::rendering_create_opengl_context(window_handle); 
    if (!rendering_context_handle) {
        return(S_FALSE);
    }

    //test file
    const RWin32FileHandle file_handle = r_win32::file_create_new("test.txt");

    //set the clear color
    RColor32Bit color_32 = {0};
    color_32.format = RColorFormat_RGBA;
    color_32.hex    = 0x282828FF;
    r_win32::rendering_set_clear_color(rendering_context_handle,color_32);

    //create the engine
    const IFBEngineHandle engine_handle = ifb_engine::engine_startup(ifb_memory_reservation_handle);

    //show the window
    r_win32::window_show(window_handle);

    //main window loop
    r_b8 running = true;
    while(running) {

        //start a new frame
        running &= r_win32::window_frame_start(window_handle);
        
        //-----------------------------
        // APPLICATION LOGIC HERE!!
        //-----------------------------

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
