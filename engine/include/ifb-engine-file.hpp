#ifndef IFB_ENG_FILE_HPP
#define IFB_ENG_FILE_HPP

#include "ifb-engine.hpp"

#ifndef    IFB_ENG_FILE_PATH_SIZE
#   define IFB_ENG_FILE_PATH_SIZE 128
#endif

#define IFB_ENG_FILE_H32_INVALID 0xFFFFFFFF

namespace ifb {

    struct eng_file_h32_t       : eng_h32_t { };
    struct eng_file_u32_flags_t : eng_u32_t { };
    struct eng_file_path_t; 
    struct eng_file_buffer_t;

    IFB_ENG_API void eng_file_close      (const eng_u32_t count,    const eng_h32_file_t*  handle);
    IFB_ENG_API void eng_file_open_ro    (const eng_u32_t in_count, const eng_file_path_t* in_path,   eng_h32_file_t*          out_handle);
    IFB_ENG_API void eng_file_open_rw    (const eng_u32_t in_count, const eng_file_path_t* in_path,   eng_h32_file_t*          out_handle);
    IFB_ENG_API void eng_file_get_size   (const eng_u32_t in_count, const eng_h32_file_t*  in_handle, eng_u32_t*               out_size);
    IFB_ENG_API void eng_file_get_buffer (const eng_u32_t in_count, const eng_h32_file_t*  in_handle, eng_file_buffer_t*       out_buffer);
    IFB_ENG_API void eng_file_get_flags  (const eng_u32_t in_count, const eng_h32_file_t*  in_handle, eng_b8_t*                out_op_pending);
    IFB_ENG_API void eng_file_read       (const eng_u32_t in_count, const eng_h32_file_t*  in_handle, eng_file_buffer_t*       out_buffer);
    IFB_ENG_API void eng_file_write      (const eng_u32_t count,    const eng_h32_file_t*  handle,    const eng_file_buffer_t* buffer);

    enum eng_file_e32_flag_ {
        eng_file_e32_flag_none    = 0,
        eng_file_e32_flag_ro      = sld::bit_value(0),
        eng_file_e32_flag_rw      = sld::bit_value(1),
        eng_file_e32_flag_pending = sld::bit_value(2),
        eng_file_e32_flag_read    = sld::bit_value(3),
        eng_file_e32_flag_write   = sld::bit_value(4),

    };

    struct eng_file_path_t {
        eng_c8_t cstr[IFB_ENG_FILE_PATH_SIZE];
    };
};

#endif  //IFB_ENGINE_FILE_HPP