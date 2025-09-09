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

#define IFB_ENG_FILE_H64_INVALID 0

namespace ifb {

    typedef eng_error_s32_t eng_file_error_s32_t;

    struct eng_file_h64_t       : eng_h64_t             { };
    struct eng_file_flags_u32_t : eng_u32_t             { };
    struct eng_file_buffer_t    : sld::os_file_buffer_t { }; 
    struct eng_file_path_t;

    IFB_ENG_API const eng_file_h64_t eng_file_mngr_open_ro   (const eng_c8*         file_path);
    IFB_ENG_API const eng_file_h64_t eng_file_mngr_open_rw   (const eng_c8*         file_path);
    IFB_ENG_API bool                 eng_file_mngr_close     (const eng_file_h64_t  file_handle);
    IFB_ENG_API bool                 eng_file_mngr_get_size  (const eng_file_h64_t  file_handle, eng_u64&                 size);
    IFB_ENG_API bool                 eng_file_mngr_get_flags (const eng_file_h64_t  file_handle, eng_file_flags_u32_t&    flags);
    IFB_ENG_API bool                 eng_file_mngr_get_path  (const eng_file_h64_t  file_handle, eng_file_path_t&         path);
    IFB_ENG_API void                 eng_file_mngr_read      (const eng_file_h64_t  file_handle, eng_file_buffer_t&       file_buffer);
    IFB_ENG_API void                 eng_file_mngr_write     (const eng_file_h64_t  file_handle, const eng_file_buffer_t& file_buffer);

    enum eng_file_flag_e32_ {
        eng_file_flag_e32_none        = 0,
        eng_file_flag_e32_error       = sld::bit_value(0),
        eng_file_flag_e32_ro          = sld::bit_value(1),
        eng_file_flag_e32_rw          = sld::bit_value(2),
        eng_file_flag_e32_io_pending  = sld::bit_value(3),
        eng_file_flag_e32_io_complete = sld::bit_value(4)
        eng_file_flag_e32_read        = sld::bit_value(5),
        eng_file_flag_e32_write       = sld::bit_value(6)
    };

    enum eng_file_error_e32_ {
        eng_file_error_e32_success               = 0x10020000,
        eng_file_error_e32_warning               = 0x00020000,
        eng_file_error_e32_failure               = 0x80020000,
        eng_file_error_e32_unknown               = 0x80020001,
        eng_file_error_e32_invalid_args          = 0x80020002,
        eng_file_error_e32_invalid_handle        = 0x80020003,
        eng_file_error_e32_invalid_disk          = 0x80020004,
        eng_file_error_e32_invalid_device        = 0x80020005,
        eng_file_error_e32_invalid_buffer        = 0x80020006,
        eng_file_error_e32_invalid_file          = 0x80020007,
        eng_file_error_e32_sharing_violation     = 0x80020008,
        eng_file_error_e32_already_exists        = 0x80020009,
        eng_file_error_e32_not_found             = 0x8002000A,
        eng_file_error_e32_access_denied         = 0x8002000B,
        eng_file_error_e32_pipe_busy             = 0x8002000C,
        eng_file_error_e32_reached_end_of_file   = 0x8002000D,
        eng_file_error_e32_broken_pipe           = 0x8002000E,
        eng_file_error_e32_no_data               = 0x8002000F,
        eng_file_error_e32_more_data             = 0x80020010,
        eng_file_error_e32_io_incomplete         = 0x80020011,
        eng_file_error_e32_io_pending            = 0x80020012,
        eng_file_error_e32_operation_aborted     = 0x80020013,
        eng_file_error_e32_disk_io_failure       = 0x80020014,
        eng_file_error_e32_disk_corrupt          = 0x80020015,
        eng_file_error_e32_device_not_ready      = 0x80020016,
        eng_file_error_e32_out_of_memory         = 0x80020017,
        eng_file_error_e32_device_failure        = 0x80020018,
        eng_file_error_e32_arena_commit_fail     = 0x80020019,
        eng_file_error_e32_buffer_alloc_fail     = 0x8002001A,
    };

    struct eng_file_path_t {
        eng_c8* cstr;
    };
};

#endif  //IFB_ENGINE_FILE_HPP