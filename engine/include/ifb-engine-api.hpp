#ifndef IFB_ENGINE_API_HPP
#define IFB_ENGINE_API_HPP

#ifdef IFB_ENGINE_INTERNAL
    #define ifb_engine_api __declspec(dllexport)
#else
    #define ifb_engine_api __declspec(dllimport)
#endif

#include <ifb-memory.hpp>

#include "ifb-engine-types.hpp"

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

namespace ifb_engine {

    // create/destroy
    ifb_engine_api const IFBHNDEngineArena 
    context_create(
        const IFBPlatformAPI* ptr_platform_api,
        const IFBByte*        ptr_stack_memory,
        const IFBU32          size_stack_memory,
        const IFBU64          reservation_size);
    
    
    ifb_engine_api const IFBB8 context_destroy      (IFBVoid);
    
    // startup/shutdown
    ifb_engine_api  IFBEngineContextUpdate* context_startup  (IFBVoid);
    ifb_engine_api const IFBB8              context_shutdown (IFBVoid);
    
    // rendering
    ifb_engine_api const IFBB8 context_render_frame (IFBEngineContextUpdate* ptr_update);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    //reset
    ifb_engine_api IFBVoid       arena_reset_all              (const IFBHNDEngineArena arena_handle);
    ifb_engine_api IFBVoid       arena_reset_committed_space  (const IFBHNDEngineArena arena_handle);
    ifb_engine_api IFBVoid       arena_reset_reserved_space   (const IFBHNDEngineArena arena_handle);
      
    //pointers
    ifb_engine_api const IFBPtr  arena_get_pointer            (const IFBHNDEngineArena arena_handle, const IFBU32  offset);
    ifb_engine_api const IFBB8   arena_get_info               (const IFBHNDEngineArena arena_handle, IFBArenaInfo* arena_info_ptr);
    ifb_engine_api const IFBAddr arena_get_start              (const IFBHNDEngineArena arena_handle);
  
    //reserve/release    
    ifb_engine_api const IFBPtr  arena_reserve_bytes_absolute (const IFBHNDEngineArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
    ifb_engine_api const IFBU32  arena_reserve_bytes_relative (const IFBHNDEngineArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
    ifb_engine_api const IFBB8   arena_release_bytes          (const IFBHNDEngineArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
      
    //commit
    ifb_engine_api const IFBPtr  arena_commit_bytes_absolute  (const IFBHNDEngineArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);
    ifb_engine_api const IFBU32  arena_commit_bytes_relative  (const IFBHNDEngineArena arena_handle, const IFBU32 size, const IFBU32  alignment = 0);

};

#endif //IFB_ENGINE_API_HPP