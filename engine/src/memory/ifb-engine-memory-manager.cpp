#pragma once

#include "ifb-engine-memory-internal.hpp"

using namespace sld;

namespace ifb {

    static eng_mem_mngr_t _mem_mngr;

    IFB_ENG_INTERNAL bool
    eng_mem_mngr_startup(
        void) {

        bool is_init = true;
        is_init &= _mem_mngr.res.core.acquire_system_memory  (ENG_MEM_SIZE_RES_CORE,  ENG_MEM_SIZE_ARENA_CORE);
        is_init &= _mem_mngr.res.file.acquire_system_memory  (ENG_MEM_SIZE_RES_FILE,  ENG_MEM_SIZE_ARENA_FILE);
        is_init &= _mem_mngr.res.asset.acquire_system_memory (ENG_MEM_SIZE_RES_ASSET, ENG_MEM_SIZE_ARENA_ASSET);
        is_init &= _mem_mngr.res.gui.acquire_system_memory   (ENG_MEM_SIZE_RES_GUI,   ENG_MEM_SIZE_ARENA_GUI);
        return(is_init);  
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_arena_commit_core(
        void) {

        eng_mem_arena_t* arena = _mem_mngr.res.core.commit_arena();  

        _mem_mngr.last_error.val = (arena != NULL)
            ? eng_mem_e32_error_success 
            : eng_mem_e32_error_failed_to_commit;
        
        return(arena);
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_arena_commit_file(
        void) {

        eng_mem_arena_t* arena = _mem_mngr.res.file.commit_arena();  

        _mem_mngr.last_error.val = (arena != NULL)
            ? eng_mem_e32_error_success 
            : eng_mem_e32_error_failed_to_commit;
        
        return(arena);
    }

    IFB_ENG_INTERNAL eng_mem_arena_t*
    eng_mem_arena_commit_asset(
        void) {

        eng_mem_arena_t* arena = _mem_mngr.res.asset.commit_arena();  

        _mem_mngr.last_error.val = (arena != NULL)
            ? eng_mem_e32_error_success 
            : eng_mem_e32_error_failed_to_commit;
        
        return(arena);
    }

    IFB_ENG_INTERNAL bool
    eng_mem_arena_decommit(
        eng_mem_arena_t* arena) {

        assert(arena);

        const bool is_decommitted = arena->decommit(); 

        _mem_mngr.last_error.val = (is_decommitted)
            ? eng_mem_e32_error_success 
            : eng_mem_e32_error_failed_to_decommit;
        
        return(is_decommitted);
    }
};