#pragma once

#include "ifb-engine-core-internal.hpp"

namespace ifb {

    SLD_FUNC void
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

    SLD_FUNC void
    eng_core_platform_window_process_events(
        void) {

        _eng_core_platform_window.last_error = sld::os_window_update(
            _eng_core_platform_window.handle,
            _eng_core_platform_window.update
        );
    }

    SLD_FUNC void
    eng_core_platform_window_swap_buffers(
        void) {

        _eng_core_platform_window.last_error = sld::os_window_swap_buffers(_eng_core_platform_window.handle);
    }
};