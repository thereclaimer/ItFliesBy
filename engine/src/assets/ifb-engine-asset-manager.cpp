#pragma once

#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-memory.hpp"

inline const ifb_b8 
ifb_engine::asset_manager_create(
    IFBEngineContext* engine_context) {

    const ifb_u32 asset_manager_size = ifb_engine_macro_align_size_struct(IFBEngineAssetManager);
    
    IFBEngineMemoryPageCommit page_commit;
    ifb_b8 result = ifb_engine::memory_commit_size(
        engine_context,
        asset_manager_size,
        page_commit);

    if (!result) {
        return(false);
    }

    //cast the pointer
    IFBEngineAssetManager* asset_manager_ptr = (IFBEngineAssetManager*)page_commit.memory_start;  

    //update the context
    engine_context->core.page_index_asset_manager = page_commit.page_start;

    return(result);
}
