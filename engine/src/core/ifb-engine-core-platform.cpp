#pragma once

#include "ifb-engine-core-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // WINDOW
    //-------------------------------------------------------------------

    IFB_ENG_FUNC void
    eng_core_platform_window_open_and_show(
        void) {

        // set the default dimensions
        _eng_core_platform_window.default_size.width        = ENG_CORE_PLATFORM_WINDOW_DEFAULT_WIDTH;
        _eng_core_platform_window.default_size.height       = ENG_CORE_PLATFORM_WINDOW_DEFAULT_HEIGHT;
        _eng_core_platform_window.default_position.screen_x = ENG_CORE_PLATFORM_WINDOW_DEFAULT_SCREEN_X;
        _eng_core_platform_window.default_position.screen_y = ENG_CORE_PLATFORM_WINDOW_DEFAULT_SCREEN_Y;

        // open the window
        _eng_core_platform_window.last_error = sld::os_window_create(
            _eng_core_platform_window.handle,
            ENG_CORE_PLATFORM_WINDOW_TITLE,
            _eng_core_platform_window.default_size,
            _eng_core_platform_window.default_position
        );

        // show the window
        sld::os_window_show(_eng_core_platform_window.handle);
    }

    IFB_ENG_FUNC void
    eng_core_platform_window_process_events(
        void) {

        _eng_core_platform_window.last_error = sld::os_window_update(
            _eng_core_platform_window.handle,
            _eng_core_platform_window.update
        );
    }

    IFB_ENG_FUNC void
    eng_core_platform_window_swap_buffers(
        void) {

        _eng_core_platform_window.last_error = sld::os_window_swap_buffers(_eng_core_platform_window.handle);
    }

    //-------------------------------------------------------------------
    // MONITOR
    //-------------------------------------------------------------------

    IFB_ENG_FUNC void
    eng_core_platform_monitor_table_init(
        void) {

        // get the monitor info and working area
        sld::os_monitor_working_area_t working_area;
        sld::os_monitor_info_t         info_array[ENG_CORE_PLATFORM_MONITOR_COUNT_MAX];
        sld::os_monitor_working_area (working_area);
        sld::os_monitor_info         (info_array);

        // initialize the table
        _eng_core_platform_monitor_table.count               = working_area.monitor_count;
        _eng_core_platform_monitor_table.virtual_size.width  = working_area.virtual_pixel_height;
        _eng_core_platform_monitor_table.virtual_size.height = working_area.virtual_pixel_width;
        _eng_core_platform_monitor_table.array.position_x    = eng_core_platform_arena_push_struct_array (ENG_CORE_PLATFORM_MONITOR_COUNT_MAX,        eng_u32);
        _eng_core_platform_monitor_table.array.position_y    = eng_core_platform_arena_push_struct_array (ENG_CORE_PLATFORM_MONITOR_COUNT_MAX,        eng_u32);
        _eng_core_platform_monitor_table.array.width         = eng_core_platform_arena_push_struct_array (ENG_CORE_PLATFORM_MONITOR_COUNT_MAX,        eng_u32);
        _eng_core_platform_monitor_table.array.height        = eng_core_platform_arena_push_struct_array (ENG_CORE_PLATFORM_MONITOR_COUNT_MAX,        eng_u32);
        _eng_core_platform_monitor_table.array.name          = eng_core_platform_arena_push_struct_array (ENG_CORE_PLATFORM_MONITOR_NAME_BUFFER_SIZE, eng_cchar);
        _eng_core_platform_monitor_table.array.os_handle     = eng_core_platform_arena_push_struct_array (ENG_CORE_PLATFORM_MONITOR_COUNT_MAX,        eng_core_monitor_os_handle_t);

        // check the table
        bool is_init = true;
        is_init &= (_eng_core_platform_monitor_table.count               != 0);
        is_init &= (_eng_core_platform_monitor_table.virtual_size.width  != 0);
        is_init &= (_eng_core_platform_monitor_table.virtual_size.height != 0);
        is_init &= (_eng_core_platform_monitor_table.array.position_x    != NULL);
        is_init &= (_eng_core_platform_monitor_table.array.position_y    != NULL);
        is_init &= (_eng_core_platform_monitor_table.array.width         != NULL);
        is_init &= (_eng_core_platform_monitor_table.array.height        != NULL);
        is_init &= (_eng_core_platform_monitor_table.array.name          != NULL);
        is_init &= (_eng_core_platform_monitor_table.array.os_handle     != NULL);        
        assert(is_init);        
        
        cstr_t monitor_name_cstr_src = { NULL, sld::OS_MONITOR_NAME_WIDTH};
        cstr_t monitor_name_cstr_dst = { NULL, sld::OS_MONITOR_NAME_WIDTH};

        // add the monitors to the table
        for (
            eng_u32 monitor = 0;
            monitor < working_area.monitor_count;
            ++monitor) {

            sld::os_monitor_info_t& info = info_array[monitor];

            bool is_monitor_valid = true;
            is_monitor_valid = (info.handle.val   != NULL);
            is_monitor_valid = (info.index        < working_area.monitor_count);
            is_monitor_valid = (info.pixel_width  > 0);
            is_monitor_valid = (info.pixel_height > 0);
            is_monitor_valid = (info.pixel_width  <= working_area.virtual_pixel_width);
            is_monitor_valid = (info.pixel_height <= working_area.virtual_pixel_height);
            is_monitor_valid = (info.position_x   <= working_area.virtual_pixel_width);
            is_monitor_valid = (info.position_y   <= working_area.virtual_pixel_height);
            assert(is_monitor_valid);

            _eng_core_platform_monitor_table.array.position_x [monitor] = info.position_x;    
            _eng_core_platform_monitor_table.array.position_y [monitor] = info.position_y;    
            _eng_core_platform_monitor_table.array.width      [monitor] = info.pixel_width;         
            _eng_core_platform_monitor_table.array.height     [monitor] = info.pixel_height;        
            _eng_core_platform_monitor_table.array.os_handle  [monitor] = info.handle;

            const eng_u32 name_str_offset = monitor * sld::OS_MONITOR_NAME_WIDTH; 
            monitor_name_cstr_src.chars = &info.name_cstr                              [name_str_offset];
            monitor_name_cstr_dst.chars = &_eng_core_platform_monitor_table.array.name [name_str_offset];
            (void)sld::cstr_copy(monitor_name_cstr_dst, monitor_name_cstr_src);          
        }
    }
};