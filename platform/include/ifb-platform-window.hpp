#ifndef IFB_PLATFORM_WINDOW_HPP
#define IFB_PLATFORM_WINDOW_HPP

#include <ifb.hpp>

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/
namespace ifb::platform {

    typedef void* gl_context_t;

    enum window_flags_e {
        window_flags_e_none    = 0,
        window_flags_e_closed  = 1,
        window_flags_e_visible = 2,
        window_flags_e_resized = 3,
        window_flags_e_moved   = 4,
    };

    typedef u64 window_flags_t; 

    struct window_t {
        utf8*          title;
        window_flags_t flags;
        dimensions_t   dims;
        position_t     pos;
        struct {
            ImGuiContext* imgui;
            gl_context_t  opengl;
        } graphics_contexts;
    };
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

namespace ifb::platform {

    typedef const u32 (*api_window_size_f)           (void);
    typedef const b8  (*api_window_create_f)         (window_t* window);
    typedef const b8  (*api_window_destroy_f)        (window_t* window);
    typedef const b8  (*api_window_process_events_f) (window_t* window);
    typedef const b8  (*api_window_swap_buffers_f)   (window_t* window);
    typedef const b8  (*api_window_show_f)           (window_t* window);

    inline void     window_set_flag_closed    (window_flags_t& flags) { ifb_macro_bit_set(window_flags_e_closed,  flags); }
    inline void     window_set_flag_visible   (window_flags_t& flags) { ifb_macro_bit_set(window_flags_e_visible, flags); }
    inline void     window_set_flag_resized   (window_flags_t& flags) { ifb_macro_bit_set(window_flags_e_resized, flags); }
    inline void     window_set_flag_moved     (window_flags_t& flags) { ifb_macro_bit_set(window_flags_e_moved,   flags); }

    inline const b8 window_get_flag_closed    (window_flags_t& flags) { return(ifb_macro_bit_test(window_flags_e_closed,  flags)); }
    inline const b8 window_get_flag_visible   (window_flags_t& flags) { return(ifb_macro_bit_test(window_flags_e_visible, flags)); }
    inline const b8 window_get_flag_resized   (window_flags_t& flags) { return(ifb_macro_bit_test(window_flags_e_resized, flags)); }
    inline const b8 window_get_flag_moved     (window_flags_t& flags) { return(ifb_macro_bit_test(window_flags_e_moved,   flags)); }

    inline void     window_clear_flag_closed  (window_flags_t& flags) { ifb_macro_bit_clear(window_flags_e_closed,  flags); }
    inline void     window_clear_flag_visible (window_flags_t& flags) { ifb_macro_bit_clear(window_flags_e_visible, flags); }
    inline void     window_clear_flag_resized (window_flags_t& flags) { ifb_macro_bit_clear(window_flags_e_resized, flags); }
    inline void     window_clear_flag_moved   (window_flags_t& flags) { ifb_macro_bit_clear(window_flags_e_moved,   flags); }
};

#endif //IFB_PLATFORM_WINDOW_HPP