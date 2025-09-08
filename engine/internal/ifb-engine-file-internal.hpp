#pragma once

#include <sld-os.hpp>

#include "ifb-engine-file.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    struct eng_file_mngr {
        eng_mem_res_t*                 reservation;
        sld::os_file_callback_async_io os_callback_read;
        sld::os_file_callback_async_io os_callback_write;
        eng_u32                        capacity;
        struct {
            sld::os_file_handle_t* os_handle;
            sld::os_file_error_t*  os_last_error;
            eng_u32*               os_bytes_transferred;
            eng_mem_arena_t*       arena;
        } array;
    };


};