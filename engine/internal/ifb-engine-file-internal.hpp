#pragma once

#include <sld-os.hpp>

#include "ifb-engine-file.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    typedef sld::os_file_callback_async_io_f eng_file_os_async_callback_f;
    typedef sld::os_file_handle_t            eng_file_os_handle_t;
    typedef sld::os_file_error_t             eng_file_os_error_t;

    struct eng_file_mngr_t;    
    struct eng_file_os_context_t;

    struct eng_file_mngr_t {
        eng_mem_res_t*                 reservation;
        eng_file_os_async_callback_f   os_callback_read;
        eng_file_os_async_callback_f   os_callback_write;
        eng_u64                        buffer_size;
        eng_u64                        capacity;
        struct {
            eng_file_os_context_t* os_context;
            eng_mem_arena_t**      arena;
            eng_file_path_t*       path;
            eng_error_s32_t*       last_error;
            eng_file_u32_flags_t*  flags;
            eng_file_buffer_t*     buffer;
        } array;
    };

    eng_file_mngr_t&       eng_file_mngr_instance             (void);
    eng_void               eng_file_mngr_async_callback_read  (const eng_file_os_context_t* async_context);
    eng_void               eng_file_mngr_async_callback_write (const eng_file_os_context_t* async_context);
    eng_error_s32_t        eng_file_mngr_error_os_to_eng      (const eng_file_os_error_t          os_error);
    void                   eng_file_mngr_open_ro              (const eng_file_h32_t& handle, const eng_file_path_t& path);
    void                   eng_file_mngr_open_rw              (const eng_file_h32_t& handle, const eng_file_path_t& path);
    eng_file_os_context_t& eng_file_mngr_get_os_context       (const eng_file_mngr_t& file_mngr, const eng_file_h32_t handle);
    eng_mem_arena_t*       eng_file_mngr_get_arena            (const eng_file_mngr_t& file_mngr, const eng_file_h32_t handle);
    eng_file_path_t&       eng_file_mngr_get_path             (const eng_file_mngr_t& file_mngr, const eng_file_h32_t handle);
    eng_error_s32_t&       eng_file_mngr_get_last_error       (const eng_file_mngr_t& file_mngr, const eng_file_h32_t handle);
    eng_file_u32_flags_t&  eng_file_mngr_get_flags            (const eng_file_mngr_t& file_mngr, const eng_file_h32_t handle);
    eng_file_buffer_t&     eng_file_mngr_get_buffer           (const eng_file_mngr_t& file_mngr, const eng_file_h32_t handle);

    struct eng_file_os_context_t : sld::os_file_context_t {
        eng_file_h32_t eng_handle;        
    };
};