#ifndef IFB_ENGINE_ARENA_HPP
#define IFB_ENGINE_ARENA_HPP

#include <ifb-common.hpp>

#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM ifb_macro_size_kilobytes(4)
#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX    4096
#define IFB_ENGINE_MEMORY_ARENA_INVALID      4096

namespace ifb_engine {

    ifb_api const ifb_u32    arena_page_start    (const IFBArenaId arena_id);
    ifb_api const ifb_u32    arena_page_count    (const IFBArenaId arena_id);
    ifb_api const ifb_cstr   arena_tag           (const IFBArenaId arena_id);
    ifb_api const ifb_memory arena_memory_start  (const IFBArenaId arena_id);
    ifb_api const ifb_memory arena_memory_offset (const IFBArenaId arena_id, const ifb_u32 offset);
};

#endif //IFB_ENGINE_ARENA_HPP