#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal.hpp"


/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    inline const ifb_u32 context_memory_page_size        (ifb_void) { return(_engine_context->memory.page_size);        }
    inline const ifb_u32 context_memory_page_count_total (ifb_void) { return(_engine_context->memory.page_count_total); }
    inline const ifb_u32 context_memory_page_count_used  (ifb_void) { return(_engine_context->memory.page_count_used);  }
};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP