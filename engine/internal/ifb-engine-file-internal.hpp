#pragma once

#include <sld-os.hpp>

#include "ifb-engine-file.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    typedef sld::os_file_callback_async_io_f eng_file_os_async_callback_f;
    typedef sld::os_file_handle_t            eng_file_os_handle_t;
    typedef sld::os_file_error_t             eng_file_os_error_t;

    struct eng_file_t;
    struct eng_file_mngr_t;
    struct eng_file_os_context_t;

    void             eng_file_mngr_init                 (void);
    eng_file_mngr_t& eng_file_mngr_get_instance         (void);
    eng_file_t*      eng_file_mngr_get_next_closed      (void);
    eng_file_t*      eng_file_mngr_get_next_open        (void);
    void             eng_file_mngr_add_closed           (eng_file_t* file);
    void             eng_file_mngr_add_open             (eng_file_t* file);
    eng_void         eng_file_mngr_async_callback_read  (const eng_file_os_context_t* async_context);
    eng_void         eng_file_mngr_async_callback_write (const eng_file_os_context_t* async_context);
    eng_error_s32_t  eng_file_mngr_error_os_to_eng      (const eng_file_os_error_t    os_error);    
    eng_file_t*      eng_file_mngr_get_file             (const eng_file_h64_t         file_handle);
    eng_file_h64_t   eng_file_mngr_get_handle           (const eng_file_t*            file);

    struct eng_file_t {
        eng_file_buffer_t      buffer;    
        eng_file_error_s32_t   last_error;
        eng_file_flags_u32_t   flags;
        eng_file_t*            next;
        eng_file_t*            prev;
        eng_file_path_t*       path;
        eng_mem_arena_t*       arena;
        eng_file_os_context_t* os_context;
    };

    struct eng_file_mngr_t {
        eng_mem_res_t*                 reservation;
        eng_file_os_async_callback_f   os_callback_read;
        eng_file_os_async_callback_f   os_callback_write;
        eng_u64                        buffer_size;
        eng_u64                        capacity;
        eng_u64                        path_size;
        struct {
            eng_file_t* opened;
            eng_file_t* closed;
        } list;
        eng_error_s32_t last_error;
    };

    struct eng_file_os_context_t : sld::os_file_context_t {
        eng_file_t* eng_file;        
    };


};