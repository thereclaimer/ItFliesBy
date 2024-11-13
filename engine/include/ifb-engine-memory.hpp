#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    ifb_api const ifb_memory 
    memory_pointer(
        const ifb_u32 page_number,
        const ifb_u32 page_offset);

    ifb_api const ifb_u32 memory_size_page_aligned (const ifb_u32 size);
    ifb_api const ifb_u32 memory_page_count        (const ifb_u32 size);
    ifb_api const ifb_u32 memory_page_size         (const ifb_u32 page_count);
    ifb_api const ifb_u32 memory_page_commit       (const ifb_u32 page_count);

};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/


struct IFBEngineMemoryArena {
    ifb_u32 arena_index;
    ifb_u32 page_start;
    ifb_u32 page_count;
};

namespace ifb_engine {

    ifb_api const ifb_b8 
    memory_arena_commit(
        const ifb_u32   in_arena_size_minimum,
              ifb_u32& out_arena_index_ref); 
};



#endif //IFB_ENGINE_MEMORY_HPP