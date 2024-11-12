#pragma once

#include "ifb-engine-memory.cpp"
#include "ifb-engine-core.cpp"
#include "ifb-engine-asset.cpp"
#include "ifb-engine-tools.cpp"

#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* EXTERNAL                                                                       */
/**********************************************************************************/

ifb_external const IFBEngineContext*
ifb_engine::engine_create_context(
            IFBEnginePlatformApi& platform_api,
    const ifb_memory              memory_reservation_start,
    const ifb_size                memory_page_size,
    const ifb_size                memory_page_count) {

    //validate the arguments
    ifb_b8 result = true;
    result &= memory_reservation_start;
    result &= memory_page_size >= IFB_ENGINE_MEMORY_RESERVATION_SIZE_GIGABYTES;
    result &= ifb_engine::platform_api_validate(platform_api);
    if (!result) {
        return(NULL);
    }

    //create the memory
    IFBEngineMemory* engine_memory_ptr = ifb_engine::memory_create(
        memory_reservation_start,
        memory_page_size,
        memory_page_count);
    if (!engine_memory_ptr) {
        return(NULL);
    }

    //allocate a context
    IFBEngineContext* engine_context = ifb_engine_memory_commit_struct_immediate(engine_memory_ptr,IFBEngineContext);
    if (!engine_context) {
        return(NULL);
    }

    //we're done
    return(engine_context);
}

ifb_external const ifb_b8
ifb_engine::engine_startup(
    IFBEngineContext* engine_context) {

}

ifb_external const ifb_b8
ifb_engine::engine_frame_start(
    IFBEngineContext* engine_context) {

}

ifb_external const ifb_b8
ifb_engine::engine_frame_render(
    IFBEngineContext* engine_context) {

}

ifb_external const ifb_b8
ifb_engine::engine_shutdown(
    IFBEngineContext* engine_context) {

}

ifb_external const ifb_b8
ifb_engine::engine_destroy_context(
    IFBEngineContext* engine_context) {

}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const ifb_u32
ifb_engine::engine_commit_pages(
          IFBEngineContext& in_context_ref, 
    const ifb_size          in_commit_size,
          ifb_u32&         out_commit_page_start_ref) {

    //calculate sizes
    const ifb_size commit_size_aligned = ifb_engine_macro_align_a_to_b(commit_size,in_context_ref.memory.page_size);
    const ifb_u32  commit_page_count   = commit_size_aligned / in_context_ref.memory.page_size;  
    const ifb_u32  commit_page_start   = in_context_ref.memory.page_count_used;
    const ifb_u32  commit_offset       = commit_page_number * in_context_ref.memory.page_size;

    //calculate page start
    const ifb_memory commit_start = in_context_ref.memory.start + commit_offset;

    //commit the pages
    const ifb_memory commit_result = ifb_engine::platform_memory_pages_commit(
        commit_start,
        commit_size_aligned);
    
    //if that succeeded, we return the pages committed
    const ifb_u32 result = (commit_start == commit_result) 
        ? commit_page_count
        : 0;

    //update the page start
    out_commit_page_start_ref = commit_page_start;

    //update the used pages
    in_context_ref.memory.page_count_used += result;

    //we're done
    return(result);
}

inline const ifb_memory 
ifb_engine::engine_page_to_pointer(
          IFBEngineMemory& memory_ref, 
    const ifb_u32          page_number) {

    const ifb_u32    page_offset = memory_ref.page_size * page_number;
    const ifb_memory page_memory = memory_ref.start + page_offset; 

    return(page_memory);
}

inline IFBEngineMemoryManager* 
ifb_engine::engine_core_memory_manager(
    IFBEngineContext& context_ref) {

    IFBEngineMemoryManager* memory_manager_ptr = 
        (IFBEngineMemoryManager*)ifb_engine::engine_page_to_pointer(
            context_ref.memory,
            context_ref.pages.memory_manager);
    
    return(memory_manager_ptr);
}

inline IFBEngineAssetManager*
ifb_engine::engine_core_asset_manager(
    IFBEngineContext& context_ref) {

    IFBEngineAssetManager* asset_manager_ptr = 
        (IFBEngineAssetManager*)ifb_engine::engine_page_to_pointer(
            context_ref.memory,
            context_ref.pages.asset_manager);
    
    return(memory_manager_ptr);
}

inline IFBEngineTools*
ifb_engine::engine_core_tools(
    IFBEngineContext& context_ref) {

    IFBEngineTools* tools_ptr = 
        (IFBEngineTools*)ifb_engine::engine_page_to_pointer(
            context_ref.memory,
            context_ref.pages.tools);
    
    return(tools_ptr);
}