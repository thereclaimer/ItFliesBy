#ifndef IFB_PLATFORM_WINDOW_HPP
#define IFB_PLATFORM_WINDOW_HPP

#include <ifb.hpp>

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/
namespace ifb {

    typedef void* gl_context_t;

    enum platform_window_flags_e {
        platform_window_flags_e_none    = 0,
        platform_window_flags_e_closed  = 1,
        platform_window_flags_e_visible = 2,
        platform_window_flags_e_resized = 3,
        platform_window_flags_e_moved   = 4,
    };

    typedef u64 platform_window_flags_t; 

    struct platform_window_t {
        utf8*                   title;
        platform_window_flags_t flags;
        dimensions_t            dims;
        position_t              pos;
        struct {
            ImGuiContext* imgui;
            gl_context_t  opengl;
        } graphics_contexts;
    };
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

namespace ifb {

    typedef const u32 (*platform_api_window_size_f)           (void);
    typedef const b8  (*platform_api_window_create_f)         (platform_window_t* window);
    typedef const b8  (*platform_api_window_destroy_f)        (platform_window_t* window);
    typedef const b8  (*platform_api_window_process_events_f) (platform_window_t* window);
    typedef const b8  (*platform_api_window_swap_buffers_f)   (platform_window_t* window);
    typedef const b8  (*platform_api_window_show_f)           (platform_window_t* window);
};

namespace ifb::platform {

    inline void     window_set_flag_closed    (platform_window_flags_t& flags) { ifb_macro_bit_set(platform_window_flags_e_closed,  flags); }
    inline void     window_set_flag_visible   (platform_window_flags_t& flags) { ifb_macro_bit_set(platform_window_flags_e_visible, flags); }
    inline void     window_set_flag_resized   (platform_window_flags_t& flags) { ifb_macro_bit_set(platform_window_flags_e_resized, flags); }
    inline void     window_set_flag_moved     (platform_window_flags_t& flags) { ifb_macro_bit_set(platform_window_flags_e_moved,   flags); }

    inline const b8 window_get_flag_closed    (platform_window_flags_t& flags) { return(ifb_macro_bit_test(platform_window_flags_e_closed,  flags)); }
    inline const b8 window_get_flag_visible   (platform_window_flags_t& flags) { return(ifb_macro_bit_test(platform_window_flags_e_visible, flags)); }
    inline const b8 window_get_flag_resized   (platform_window_flags_t& flags) { return(ifb_macro_bit_test(platform_window_flags_e_resized, flags)); }
    inline const b8 window_get_flag_moved     (platform_window_flags_t& flags) { return(ifb_macro_bit_test(platform_window_flags_e_moved,   flags)); }

    inline void     window_clear_flag_closed  (platform_window_flags_t& flags) { ifb_macro_bit_clear(platform_window_flags_e_closed,  flags); }
    inline void     window_clear_flag_visible (platform_window_flags_t& flags) { ifb_macro_bit_clear(platform_window_flags_e_visible, flags); }
    inline void     window_clear_flag_resized (platform_window_flags_t& flags) { ifb_macro_bit_clear(platform_window_flags_e_resized, flags); }
    inline void     window_clear_flag_moved   (platform_window_flags_t& flags) { ifb_macro_bit_clear(platform_window_flags_e_moved,   flags); }
};

#endif //IFB_PLATFORM_WINDOW_HPP