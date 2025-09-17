#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine.hpp"

#ifndef    IFB_ENG_MEM_SIZE_KB_PLATFORM_RES  
#   define IFB_ENG_MEM_SIZE_KB_PLATFORM_RES   64000   // 64 MB
#endif
#ifndef    IFB_ENG_MEM_SIZE_KB_PLATFORM_ARENA
#   define IFB_ENG_MEM_SIZE_KB_PLATFORM_ARENA 64      // 64 KB
#endif
#ifndef    IFB_ENG_MEM_SIZE_KB_CORE_RES 
#   define IFB_ENG_MEM_SIZE_KB_CORE_RES       64000   // 64 MB
#endif
#ifndef    IFB_ENG_MEM_SIZE_KB_CORE_ARENA
#   define IFB_ENG_MEM_SIZE_KB_CORE_ARENA     64      // 64 KB
#endif
#ifndef    IFB_ENG_MEM_SIZE_KB_FILE_RES 
#   define IFB_ENG_MEM_SIZE_KB_FILE_RES       1000000 // 1 GB
#endif
#ifndef    IFB_ENG_MEM_SIZE_KB_FILE_ARENA
#   define IFB_ENG_MEM_SIZE_KB_FILE_ARENA     1000    // 1 MB
#endif
#ifndef    IFB_ENG_MEM_SIZE_KB_ASSET_RES 
#   define IFB_ENG_MEM_SIZE_KB_ASSET_RES      1000000 // 1 GB
#endif
#ifndef    IFB_ENG_MEM_SIZE_KB_ASSET_ARENA
#   define IFB_ENG_MEM_SIZE_KB_ASSET_ARENA    64000   // 64 MB
#endif

namespace ifb {

    // primitive types
    struct eng_mem_h32_arena_t;
    struct eng_mem_h32_alctr_block_t;
    struct eng_mem_h32_alctr_stack_t;
    struct eng_mem_h32_alctr_heap_t;
    struct eng_mem_u32_res_type_t;

    // structured types
    struct eng_mem_res_info_t;
    struct eng_mem_arena_info_t;
    struct eng_mem_alctr_block_info_t;
    struct eng_mem_alctr_stack_info_t;
    struct eng_mem_alctr_heap_info_t;

    IFB_ENG_API const eng_error_s32_t           eng_mem_last_error             (void);
    
    IFB_ENG_API eng_bool                        eng_mem_res_get_info           (const eng_mem_u32_res_type_t in_res, eng_mem_res_info_t& out_info);

    IFB_ENG_API const eng_mem_h32_arena_t       eng_mem_arena_commit           (const eng_mem_u32_res_type_t res);
    IFB_ENG_API eng_bool                        eng_mem_arena_decommit         (const eng_mem_h32_arena_t arena_hnd);
    IFB_ENG_API eng_byte*                       eng_mem_arena_get_ptr          (const eng_mem_h32_arena_t arena_hnd, const eng_u32 offset);    
    IFB_ENG_API eng_byte*                       eng_mem_arena_push_bytes_abs   (const eng_mem_h32_arena_t arena_hnd, const eng_u32 size, const eng_u32 align = 0);
    IFB_ENG_API eng_u32                         eng_mem_arena_push_bytes_rel   (const eng_mem_h32_arena_t arena_hnd, const eng_u32 size, const eng_u32 align = 0);
    IFB_ENG_API eng_bool                        eng_mem_arena_pull_bytes       (const eng_mem_h32_arena_t arena_hnd, const eng_u32 size, const eng_u32 align = 0);
    IFB_ENG_API const eng_mem_h32_alctr_block_t eng_mem_arena_push_alctr_block (const eng_mem_h32_arena_t arena_hnd, const eng_u32 block_size, const eng_u32 block_count);
    IFB_ENG_API const eng_mem_h32_alctr_stack_t eng_mem_arena_push_alctr_stack (const eng_mem_h32_arena_t arena_hnd, const eng_u32 stack_size);
    IFB_ENG_API const eng_mem_h32_alctr_heap_t  eng_mem_arena_push_alctr_heap  (const eng_mem_h32_arena_t arena_hnd, const eng_u32 heap_size, const eng_u32 alloc_size_min, const eng_u32 alloc_size_max);
    IFB_ENG_API eng_bool                        eng_mem_arena_get_info         (const eng_mem_h32_arena_t in_arena_hnd, eng_mem_arena_info_t& out_info);

    IFB_ENG_API eng_byte*                       eng_mem_alctr_block_alctr_abs  (const eng_mem_h32_alctr_block_t b_alctr_hnd);
    IFB_ENG_API eng_byte*                       eng_mem_alctr_block_alctr_rel  (const eng_mem_h32_alctr_block_t b_alctr_hnd);
    IFB_ENG_API eng_bool                        eng_mem_alctr_block_free       (const eng_mem_h32_alctr_block_t b_alctr_hnd, const eng_byte* mem);

    IFB_ENG_API eng_byte*                       eng_mem_alctr_stack_push_abs   (const eng_mem_h32_alctr_block_t b_alctr_hnd);
    IFB_ENG_API eng_byte*                       eng_mem_alctr_stack_push_rel   (const eng_mem_h32_alctr_block_t b_alctr_hnd);
    IFB_ENG_API eng_bool                        eng_mem_alctr_stack_pull       (const eng_mem_h32_alctr_block_t b_alctr_hnd, const eng_byte* mem);

    IFB_ENG_API eng_byte*                       eng_mem_alctr_heap_alctr_abs   (const eng_mem_h32_alctr_block_t b_alctr_hnd);
    IFB_ENG_API eng_byte*                       eng_mem_alctr_heap_alctr_rel   (const eng_mem_h32_alctr_block_t b_alctr_hnd);
    IFB_ENG_API eng_bool                        eng_mem_alctr_heap_free        (const eng_mem_h32_alctr_block_t b_alctr_hnd, const eng_byte* mem);

    enum eng_mem_e32_error_ {
        eng_mem_e32_error_success            = 0x10020000,
        eng_mem_e32_error_warning            = 0x00020000,
        eng_mem_e32_error_failure            = 0x80020000,
        eng_mem_e32_error_failed_to_reserve  = 0x80020001,
        eng_mem_e32_error_failed_to_release  = 0x80020002,
        eng_mem_e32_error_failed_to_commit   = 0x80020003,
        eng_mem_e32_error_failed_to_decommit = 0x80020004,
    };

    enum eng_mem_e32_res_type_ {
        eng_mem_e32_res_type_platform = 0,
        eng_mem_e32_res_type_core     = 1,
        eng_mem_e32_res_type_file     = 2,
        eng_mem_e32_res_type_asset    = 3
    };

    struct eng_mem_h32_arena_t       : eng_h32_t { };
    struct eng_mem_h32_alctr_block_t : eng_h32_t { };
    struct eng_mem_h32_alctr_stack_t : eng_h32_t { };
    struct eng_mem_h32_alctr_heap_t  : eng_h32_t { };
    struct eng_mem_u32_res_type_t    : eng_u32_t { };

    struct eng_mem_res_info_t {
        eng_addr               start;
        eng_u32                size_kb_total;
        eng_u32                size_kb_used;
        eng_u32                size_kb_free;
        eng_u32                size_kb_arena;
    };

    struct eng_mem_arena_info_t {
        eng_addr               start;
        eng_mem_u32_res_type_t res_type;
        eng_mem_h32_arena_t    handle;
        eng_u32_t              size_kb_total;
        eng_u32_t              size_kb_free;
        eng_u32_t              size_kb_used;
        eng_error_s32_t        last_error;
    };

};

#endif //IFB_ENGINE_MEMORY_HPP