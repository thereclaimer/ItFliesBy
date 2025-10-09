#include "ifb-engine-core-internal.hpp"
#include <sld.hpp>

#define window_has_event_key_down()             (_eng_core_window.update.events.val & sld::os_window_event_e_key_down)
#define window_has_event_key_up()               (_eng_core_window.update.events.val & sld::os_window_event_e_key_up)
#define window_keyboard_count_keys_down()       _eng_core_window.update.keyboard->key_count.down
#define window_keyboard_count_keys_up()         _eng_core_window.update.keyboard->key_count.up
#define window_keyboard_get_keycode_down(index) _eng_core_window.update.keyboard->keycode_array.down[index]; 
#define window_keyboard_get_keycode_up(index)   _eng_core_window.update.keyboard->keycode_array.up[index]; 
#define window_keyboard_reset()                 sld::input_keyboard_reset(_eng_core_window.update.keyboard)

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
        _eng_core_window.update.keyboard = _eng_core_arenas.platform->push_struct<sld::input_keyboard_t>();

        bool is_mem_ok = true;
        is_mem_ok &= (_eng_core_window.update.keyboard   != NULL); 
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

        // get the window update
        _eng_core_window.last_error = sld::os_window_update(
            _eng_core_window.handle,
            _eng_core_window.update
        );

        const bool is_key_down     = window_has_event_key_down();
        const bool is_key_up       = window_has_event_key_up();
        const u32  count_keys_down = window_keyboard_count_keys_down();
        const u32  count_keys_up   = window_keyboard_count_keys_up();
        
        bool update_is_valid = true;
        update_is_valid &= (!is_key_down && count_keys_down == 0) || (is_key_down && count_keys_down > 0);
        update_is_valid &= (!is_key_up   && count_keys_up   == 0) || (is_key_up   && count_keys_up   > 0);
        assert(update_is_valid);

        if (is_key_down) {

            for (
                u32 key_index = 0;
                key_index < count_keys_down;
                ++key_index) {

                const sld::input_keycode_t keycode = window_keyboard_get_keycode_down(key_index); 

                if (keycode.val == sld::os_input_keycode_e_a) {
                    // assert(false);
                }
            }
        }

        if (is_key_up) {
            
            for (
                u32 key_index = 0;
                key_index < count_keys_up;
                ++key_index) {

                const sld::input_keycode_t keycode = window_keyboard_get_keycode_up(key_index); 
            }
        }

        window_keyboard_reset();
    }

    IFB_ENG_FUNC void
    eng_core_window_swap_buffers(
        void) {

        _eng_core_window.last_error = sld::os_window_swap_buffers(_eng_core_window.handle);
    }

    IFB_ENG_FUNC void
    eng_core_window_center_to_monitor(
        const eng_core_monitor_handle_t monitor) {

        dims_u32_size_t monitor_size;
        dims_u32_pos_t  monitor_center;
        dims_u32_pos_t  window_center;

        const bool should_reset_window = (_eng_core_window.size.width == 0 || _eng_core_window.size.height == 0); 
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

        const bool should_reset_window = (_eng_core_window.size.width == 0 || _eng_core_window.size.height == 0); 
        if (should_reset_window) {
            _eng_core_window.size.width  = ENG_CORE_WINDOW_DEFAULT_WIDTH;
            _eng_core_window.size.height = ENG_CORE_WINDOW_DEFAULT_HEIGHT;
        }

        dims_u32_size_t monitor_size;
        eng_core_monitor_get_size      (_eng_core_monitor_table.primary,     monitor_size);
        sld::dims_u32_center_a_inside_b(_eng_core_window.size, monitor_size, _eng_core_window.position);
    }

};