#pragma once

#include "ifb-engine-memory-internal.cpp"

using namespace sld;

namespace ifb {

    IFB_ENG_INTERNAL bool
    eng_mem_mngr_init(
        const eng_u32_t size_kb_platform_res,
        const eng_u32_t size_kb_platform_arena,
        const eng_u32_t size_kb_core_res,
        const eng_u32_t size_kb_core_arena,
        const eng_u32_t size_kb_file_res,
        const eng_u32_t size_kb_file_arena) {

        const eng_u64_t size_platform_res   = size_kilobytes (size_kb_platform_res); 
        const eng_u64_t size_platform_arena = size_kilobytes (size_kb_platform_arena); 
        const eng_u64_t size_core_res       = size_kilobytes (size_kb_core_res); 
        const eng_u64_t size_core_arena     = size_kilobytes (size_kb_core_arena); 
        const eng_u64_t size_file_res       = size_kilobytes (size_kb_file_res); 
        const eng_u64_t size_file_arena     = size_kilobytes (size_kb_file_arena);

        static eng_mem_mngr_t& mem_mngr = eng_mem_mngr_instance();
        mem_mngr.res_platform = reservation_acquire (size_platform_res, size_platform_arena);
        mem_mngr.res_core     = reservation_acquire (size_core_res,     size_core_arena);
        mem_mngr.res_file     = reservation_acquire (size_file_res,     size_file_arena);
    
        
    
    }

    IFB_ENG_INLINE eng_mem_mngr_t&
    eng_mem_mngr_instance(
        void) {

        static eng_mem_mngr_t mngr = {
            // res_core
            // res_file_mngr
        };
        return(mngr);
    }

};
