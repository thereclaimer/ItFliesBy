#ifndef IFB_ENGINE_INTERNAL_HPP
#define IFB_ENGINE_INTERNAL_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-tools.hpp"


namespace ifb_engine {

    const ifb_u32 
    engine_commit_pages(
              IFBEngineContext& in_context_ref, 
        const ifb_size          in_commit_size,
              ifb_u32&         out_commit_page_start_ref);
};

#endif //IFB_ENGINE_INTERNAL_HPP