#ifndef IFB_ENGINE_ARENA_HPP
#define IFB_ENGINE_ARENA_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"
#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

#define IFB_ENGINE_ARENA_SIZE_MINIMUM ifb_engine_macro_size_kilobytes(4)

struct IFBEngineArena {
    ifb_u32 page_start;
    ifb_u32 page_count;
};

namespace ifb_engine {

    ifb_api const ifb_b8 
    arena_commit(
        const ifb_u32          in_arena_size_minimum,
              IFBEngineArena& out_arena_ref);
};

#endif //IFB_ENGINE_ARENA_HPP