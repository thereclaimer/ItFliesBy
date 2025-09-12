#ifndef IFB_ENGINE_MEMORY_INTERNAL_HPP
#define IFB_ENGINE_MEMORY_INTERNAL_HPP

#include <sld-memory.hpp>
#include "ifb-engine-memory.hpp"

namespace ifb {

    typedef eng_error_s32_t    eng_mem_error_s32_t;
    typedef sld::reservation_t eng_mem_res_t;
    typedef sld::arena_t       eng_mem_arena_t;

    struct eng_mem_mngr_t {
        struct {
            eng_mem_res_t* platform;
            eng_mem_res_t* core;
            eng_mem_res_t* file;
            eng_mem_res_t* asset;
        } res;
        eng_mem_error_s32_t last_error;
    };

    bool              eng_mem_mngr_init                  (void);
    eng_mem_arena_t*  eng_mem_mngr_arena_commit_platform (void);   
    eng_mem_arena_t*  eng_mem_mngr_arena_commit_core     (void);   
    eng_mem_arena_t*  eng_mem_mngr_arena_commit_file     (void);   
    eng_mem_arena_t*  eng_mem_mngr_arena_commit_asset    (void);   
    bool              eng_mem_mngr_arena_decommit        (eng_mem_arena_t* arena);

};

#endif // IFB_ENGINE_MEMORY_INTERNAL_HPP