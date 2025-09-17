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
        const eng_u64 size_asset_res      = size_kilobytes (IFB_ENG_MEM_SIZE_KB_ASSET_RES); 
        const eng_u64 size_asset_arena    = size_kilobytes (IFB_ENG_MEM_SIZE_KB_ASSET_ARENA);

        _mem_mngr.res.platform = reservation_acquire(size_platform_res, size_platform_arena);
        _mem_mngr.res.core     = reservation_acquire(size_core_res,     size_core_arena);
        _mem_mngr.res.file     = reservation_acquire(size_file_res,     size_file_arena);
        _mem_mngr.res.asset    = reservation_acquire(size_asset_res,    size_asset_arena);

        const eng_bool is_init = (
            _mem_mngr.res.platform != NULL &&
            _mem_mngr.res.core     != NULL &&
            _mem_mngr.res.file     != NULL
        ); 
        
        return(is_init);  
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_mngr_arena_commit_platform(
        void) {

        assert(_mem_mngr.res.platform);

        eng_mem_arena_t* arena = sld::arena_commit(_mem_mngr.res.platform);

        _mem_mngr.last_error.val = (arena != NULL)
            ? eng_mem_e32_error_success 
            : eng_mem_e32_error_failed_to_commit;
        
        return(arena);
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_mngr_arena_commit_core(
        void) {

        assert(_mem_mngr.res.core);

        eng_mem_arena_t* arena = sld::arena_commit(_mem_mngr.res.core);

        _mem_mngr.last_error.val = (arena != NULL)
            ? eng_mem_e32_error_success 
            : eng_mem_e32_error_failed_to_commit;
        
        return(arena);
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_mngr_arena_commit_file(
        void) {

        assert(_mem_mngr.res.file);

        eng_mem_arena_t* arena = sld::arena_commit(_mem_mngr.res.file);

        _mem_mngr.last_error.val = (arena != NULL)
            ? eng_mem_e32_error_success 
            : eng_mem_e32_error_failed_to_commit;
        
        return(arena);
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_mngr_arena_commit_asset(
        void) {

        assert(_mem_mngr.res.asset);

        eng_mem_arena_t* arena = sld::arena_commit(_mem_mngr.res.asset);

        _mem_mngr.last_error.val = (arena != NULL)
            ? eng_mem_e32_error_success 
            : eng_mem_e32_error_failed_to_commit;
        
        return(arena);
    }

    IFB_ENG_INTERNAL bool
    eng_mem_mngr_arena_decommit(
        eng_mem_arena_t* arena) {

        assert(arena);

        const bool is_decommitted = sld::arena_decommit(arena);

        _mem_mngr.last_error.val = (is_decommitted)
            ? eng_mem_e32_error_success 
            : eng_mem_e32_error_failed_to_decommit;
        
        return(is_decommitted);
    }
};