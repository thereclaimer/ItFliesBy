#ifndef IFB_ENG_FILE_HPP
#define IFB_ENG_FILE_HPP

#include "ifb-engine.hpp"

#ifndef    IFB_ENG_FILE_PATH_SIZE
#   define IFB_ENG_FILE_PATH_SIZE 128
#endif
#ifndef    IFB_ENG_FILE_TABLE_CAPACITY
#   define IFB_ENG_FILE_TABLE_CAPACITY 128
#endif
#ifndef    IFB_ENG_FILE_BUFFER_SIZE_KB
#   define IFB_ENG_FILE_BUFFER_SIZE_KB 128
#endif

#define IFB_ENG_FILE_H32_INVALID 0xFFFFFFFF

namespace ifb {

    struct eng_file_h32_t       : eng_h32_t { };
    struct eng_file_u32_flags_t : eng_u32_t { };
    struct eng_file_path_t; 
    struct eng_file_buffer_t;

    IFB_ENG_API void eng_file_mngr_close      (const eng_u32 count,    const eng_h32_file_t*  handle);
    IFB_ENG_API void eng_file_mngr_open_ro    (const eng_u32 in_count, const eng_file_path_t* in_path,   eng_h32_file_t*          out_handle);
    IFB_ENG_API void eng_file_mngr_open_rw    (const eng_u32 in_count, const eng_file_path_t* in_path,   eng_h32_file_t*          out_handle);
    IFB_ENG_API void eng_file_mngr_get_size   (const eng_u32 in_count, const eng_h32_file_t*  in_handle, eng_u64*                 out_size);
    IFB_ENG_API void eng_file_mngr_get_buffer (const eng_u32 in_count, const eng_h32_file_t*  in_handle, eng_file_buffer_t*       out_buffer);
    IFB_ENG_API void eng_file_mngr_get_flags  (const eng_u32 in_count, const eng_h32_file_t*  in_handle, eng_b8_t*                out_op_pending);
    IFB_ENG_API void eng_file_mngr_read       (const eng_u32 in_count, const eng_h32_file_t*  in_handle, eng_u32* length, eng_u32* offset);
    IFB_ENG_API void eng_file_mngr_write      (const eng_u32 count,    const eng_h32_file_t*  handle,    const eng_file_buffer_t* buffer, eng_u32* offset);

    enum eng_file_e32_flag_ {
        eng_file_e32_flag_none        = 0,
        eng_file_e32_flag_error       = sld::bit_value(0),
        eng_file_e32_flag_ro          = sld::bit_value(1),
        eng_file_e32_flag_rw          = sld::bit_value(2),
        eng_file_e32_flag_io_pending  = sld::bit_value(3),
        eng_file_e32_flag_io_complete = sld::bit_value(4)
        eng_file_e32_flag_read        = sld::bit_value(5),
        eng_file_e32_flag_write       = sld::bit_value(6)
    };

    enum eng_file_e32_error_ {
        eng_file_e32_error_success               = 0x10020000,
        eng_file_e32_error_warning               = 0x00020000,
        eng_file_e32_error_failure               = 0x80020000,
        eng_file_e32_error_unknown               = 0x80020001,
        eng_file_e32_error_invalid_args          = 0x80020002,
        eng_file_e32_error_invalid_handle        = 0x80020003,
        eng_file_e32_error_invalid_disk          = 0x80020004,
        eng_file_e32_error_invalid_device        = 0x80020005,
        eng_file_e32_error_invalid_buffer        = 0x80020006,
        eng_file_e32_error_invalid_file          = 0x80020007,
        eng_file_e32_error_sharing_violation     = 0x80020008,
        eng_file_e32_error_already_exists        = 0x80020009,
        eng_file_e32_error_not_found             = 0x8002000A,
        eng_file_e32_error_access_denied         = 0x8002000B,
        eng_file_e32_error_pipe_busy             = 0x8002000C,
        eng_file_e32_error_reached_end_of_file   = 0x8002000D,
        eng_file_e32_error_broken_pipe           = 0x8002000E,
        eng_file_e32_error_no_data               = 0x8002000F,
        eng_file_e32_error_more_data             = 0x80020010,
        eng_file_e32_error_io_incomplete         = 0x80020011,
        eng_file_e32_error_io_pending            = 0x80020012,
        eng_file_e32_error_operation_aborted     = 0x80020013,
        eng_file_e32_error_disk_io_failure       = 0x80020014,
        eng_file_e32_error_disk_corrupt          = 0x80020015,
        eng_file_e32_error_device_not_ready      = 0x80020016,
        eng_file_e32_error_out_of_memory         = 0x80020017,
        eng_file_e32_error_device_failure        = 0x80020018,
        eng_file_e32_error_arena_commit_fail     = 0x80020019,
        eng_file_e32_error_buffer_alloc_fail     = 0x8002001A,
    };

    struct eng_file_path_t {
        eng_c8_t cstr[IFB_ENG_FILE_PATH_SIZE];
    };

    struct eng_file_buffer_t {
        eng_byte* data;
        eng_u32   length;
        eng_u32   offset;
    };
};

#endif  //IFB_ENGINE_FILE_HPP