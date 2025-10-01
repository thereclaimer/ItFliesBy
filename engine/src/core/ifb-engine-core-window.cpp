#include "ifb-engine-core-internal.hpp"
#include <sld.hpp>

namespace ifb {

 
    IFB_ENG_FUNC void
    eng_core_window_init(
        void) {

        // set the default dimensions
        _eng_core_window.size.width  = ENG_CORE_WINDOW_DEFAULT_WIDTH;
        _eng_core_window.size.height = ENG_CORE_WINDOW_DEFAULT_HEIGHT;
        _eng_core_window.position.x  = ENG_CORE_WINDOW_DEFAULT_SCREEN_X;
        _eng_core_window.position.y  = ENG_CORE_WINDOW_DEFAULT_SCREEN_Y;

        // allocate memory
        sld::os_input_queue_keyboard_t* input_queue_struct_key_up   = (sld::os_input_queue_keyboard_t*)sld::queue_init_from_arena(_eng_core_arenas.platform, ENG_CORE_WINDOW_INPUT_QUEUE_KEYBOARD_SIZE, ENG_CORE_WINDOW_INPUT_QUEUE_KEYBOARD_STRIDE); 
        sld::os_input_queue_keyboard_t* input_queue_struct_key_down = (sld::os_input_queue_keyboard_t*)sld::queue_init_from_arena(_eng_core_arenas.platform, ENG_CORE_WINDOW_INPUT_QUEUE_KEYBOARD_SIZE, ENG_CORE_WINDOW_INPUT_QUEUE_KEYBOARD_STRIDE);

        bool is_mem_ok = true;
        is_mem_ok &= (input_queue_struct_key_up   != NULL); 
        is_mem_ok &= (input_queue_struct_key_down != NULL); 
        assert(is_mem_ok);
    }

    IFB_ENG_FUNC void
    eng_core_window_open_and_show(
        void) {

        sld::color_u32_t clear_color;
        clear_color.r = 0x28;
        clear_color.g = 0x28;
        clear_color.b = 0x28;
        clear_color.a = 1.0f;

        // open the window
        _eng_core_window.last_error = sld::os_window_create(
            _eng_core_window.handle,
            ENG_CORE_WINDOW_TITLE,
            _eng_core_window.size,
            _eng_core_window.position
        );

        // intialize the viewport
        sld::os_window_set_clear_color (_eng_core_window.handle, clear_color);
        sld::os_window_set_viewport    (_eng_core_window.handle, _eng_core_window.size, _eng_core_window.position);

        // show the window
        sld::os_window_show(_eng_core_window.handle);
    }

    IFB_ENG_FUNC void
    eng_core_window_process_events(
        void) {

        _eng_core_window.last_error = sld::os_window_update(
            _eng_core_window.handle,
            _eng_core_window.update
        );
    }

    IFB_ENG_FUNC void
    eng_core_window_swap_buffers(
        void) {

        _eng_core_window.last_error = sld::os_window_swap_buffers(_eng_core_window.handle);
    }

    IFB_ENG_FUNC void
    eng_core_window_center_to_monitor(
        const eng_core_monitor_handle_t monitor) {

        eng_dims_u32_size_t monitor_size;
        eng_dims_u32_pos_t  monitor_center;
        eng_dims_u32_pos_t  window_center;

        const eng_bool should_reset_window = (_eng_core_window.size.width == 0 || _eng_core_window.size.height == 0); 
        if (should_reset_window) {
            _eng_core_window.size.width  = ENG_CORE_WINDOW_DEFAULT_WIDTH;
            _eng_core_window.size.height = ENG_CORE_WINDOW_DEFAULT_HEIGHT;
        }

        eng_core_monitor_get_size      (monitor,               monitor_size);
        sld::dims_u32_center_a_inside_b(_eng_core_window.size, monitor_size, _eng_core_window.position);
    }

    IFB_ENG_FUNC void
    eng_core_window_center_to_primary_monitor(
        void) {

        const eng_bool should_reset_window = (_eng_core_window.size.width == 0 || _eng_core_window.size.height == 0); 
        if (should_reset_window) {
            _eng_core_window.size.width  = ENG_CORE_WINDOW_DEFAULT_WIDTH;
            _eng_core_window.size.height = ENG_CORE_WINDOW_DEFAULT_HEIGHT;
        }

        eng_dims_u32_size_t monitor_size;
        eng_core_monitor_get_size      (_eng_core_monitor_table.primary,     monitor_size);
        sld::dims_u32_center_a_inside_b(_eng_core_window.size, monitor_size, _eng_core_window.position);
    }

};