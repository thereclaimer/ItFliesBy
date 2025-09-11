#pragma once

#include "ifb-engine-memory-internal.hpp"

using namespace sld;

namespace ifb {

    static eng_mem_mngr_t _mem_mngr;

    IFB_ENG_INTERNAL bool
    eng_mem_mngr_init(
        void) {

        const eng_u64 size_platform_res   = size_kilobytes (IFB_ENG_MEM_SIZE_KB_PLATFORM_RES); 
        const eng_u64 size_platform_arena = size_kilobytes (IFB_ENG_MEM_SIZE_KB_PLATFORM_ARENA); 
        const eng_u64 size_core_res       = size_kilobytes (IFB_ENG_MEM_SIZE_KB_CORE_RES); 
        const eng_u64 size_core_arena     = size_kilobytes (IFB_ENG_MEM_SIZE_KB_CORE_ARENA); 
        const eng_u64 size_file_res       = size_kilobytes (IFB_ENG_MEM_SIZE_KB_FILE_RES); 
        const eng_u64 size_file_arena     = size_kilobytes (IFB_ENG_MEM_SIZE_KB_FILE_ARENA);

        _mem_mngr.res_platform = (eng_mem_res_platform_t*)reservation_acquire(size_platform_res, size_platform_arena);
        _mem_mngr.res_core     =     (eng_mem_res_core_t*)reservation_acquire(size_core_res,     size_core_arena);
        _mem_mngr.res_file     =     (eng_mem_res_file_t*)reservation_acquire(size_file_res,     size_file_arena);

        const eng_bool is_init = (
            _mem_mngr.res_platform != NULL &&
            _mem_mngr.res_core     != NULL &&
            _mem_mngr.res_file     != NULL
        ); 
        
        return(is_init);  
    }

    IFB_ENG_INTERNAL eng_mem_res_platform_t*
    eng_mem_mngr_get_res_platform(
        void) {

        return(_mem_mngr.res_platform);
    }

    IFB_ENG_INTERNAL eng_mem_res_core_t*
    eng_mem_mngr_get_res_core(
        void) {

        return(_mem_mngr.res_core);
    }

    IFB_ENG_INTERNAL eng_mem_res_file_t*
    eng_mem_mngr_get_res_file(
        void) {

        return(_mem_mngr.res_file);
    }
};
