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
    
    const ifb_b8  engine_commit_core_pages (IFBEngineContext& context_ref);
    
    const ifb_memory engine_page_to_pointer(IFBEngineMemory& memory_ref, const ifb_u32 page_number);

    IFBEngineMemoryManager* engine_core_memory_manager (IFBEngineContext& context_ref); 
    IFBEngineAssetManager*  engine_core_asset_manager  (IFBEngineContext& context_ref); 
    IFBEngineTools*         engine_core_tools          (IFBEngineContext& context_ref); 
};

#endif //IFB_ENGINE_INTERNAL_HPP