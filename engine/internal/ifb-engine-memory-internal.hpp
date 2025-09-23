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

    IFB_ENG_FUNC bool              eng_mem_mngr_init             (void);
    IFB_ENG_FUNC eng_mem_arena_t*  eng_mem_arena_commit_platform (void);   
    IFB_ENG_FUNC eng_mem_arena_t*  eng_mem_arena_commit_core     (void);   
    IFB_ENG_FUNC eng_mem_arena_t*  eng_mem_arena_commit_file     (void);   
    IFB_ENG_FUNC eng_mem_arena_t*  eng_mem_arena_commit_asset    (void);   
    IFB_ENG_FUNC bool              eng_mem_arena_decommit        (eng_mem_arena_t* arena);

    IFB_ENG_INLINE eng_byte* eng_mem_arena_push_bytes    (eng_mem_arena_t* arena, const eng_u64 size, const eng_u64 alignment = 0) { return(sld::arena_push_bytes    (arena, size, alignment)); }
    IFB_ENG_INLINE eng_bool  eng_mem_arena_pull_bytes    (eng_mem_arena_t* arena, const eng_u64 size, const eng_u64 alignment = 0) { return(sld::arena_pull_bytes    (arena, size, alignment)); }
    IFB_ENG_INLINE eng_bool  eng_mem_arena_reset         (eng_mem_arena_t* arena)                                                  { return(sld::arena_reset         (arena));                  }
    IFB_ENG_INLINE eng_bool  eng_mem_arena_roll_back     (eng_mem_arena_t* arena)                                                  { return(sld::arena_roll_back     (arena));                  }
    IFB_ENG_INLINE eng_bool  eng_mem_arena_save_position (eng_mem_arena_t* arena)                                                  { return(sld::arena_save_position (arena));                  }
    IFB_ENG_INLINE eng_u64   eng_mem_arena_size_total    (eng_mem_arena_t* arena)                                                  { return(sld::arena_size_total    (arena));                  }
    IFB_ENG_INLINE eng_u64   eng_mem_arena_size_free     (eng_mem_arena_t* arena)                                                  { return(sld::arena_size_free     (arena));                  }
    IFB_ENG_INLINE eng_u64   eng_mem_arena_size_used     (eng_mem_arena_t* arena)                                                  { return(sld::arena_size_used     (arena));                  }
};

#define eng_mem_arena_push_struct(arena, struct)              (struct*)sld::arena_push_bytes(arena, sizeof(struct))
#define eng_mem_arena_pull_struct(arena, struct)                       sld::arena_pull_bytes(arena, sizeof(struct))
#define eng_mem_arena_push_struct_array(arena, count, struct) (struct*)sld::arena_push_bytes(arena, (count * sizeof(struct)))
#define eng_mem_arena_pull_struct_array(arena, count, struct)          sld::arena_pull_bytes(arena, (count * sizeof(struct)))

#endif // IFB_ENGINE_MEMORY_INTERNAL_HPP