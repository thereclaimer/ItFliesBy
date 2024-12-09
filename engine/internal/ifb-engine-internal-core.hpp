#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-managers.hpp"

/**********************************************************************************/
/* CORE MANAGERS                                                                  */
/**********************************************************************************/

struct IFBEngineCoreManagers {
    struct {
        IFBEngineGlobalHandleTagManager    tag;
        IFBEngineGlobalHandleArenaManager  arena;
    } global_handles;
};

namespace ifb_engine {

    ifb_void 
    core_managers_create_all(
              IFBEngineCoreManagers& ref_core_managers, 
        const IFBEngineMemory*       ptr_memory);
    
    IFBEngineMemoryManager* core_managers_get_pointer_memory_manager (const IFBEngineCoreManagers& ref_core_managers);
    IFBEngineTagManager*    core_managers_get_pointer_tag_manager    (const IFBEngineCoreManagers& ref_core_managers);
    IFBEngineArenaManager*  core_managers_get_pointer_arena_manager  (const IFBEngineCoreManagers& ref_core_managers);
};

/**********************************************************************************/
/* CORE                                                                           */
/**********************************************************************************/

struct IFBEngineGlobalHandleCore : IFBEngineGlobalHandle;

struct IFBEngineCore {
    IFBEngineCoreManagers managers;
};

namespace ifb_engine {

    const IFBEngineGlobalHandleCore core_create (IFBEngineMemory* ptr_memory);

    IFBEngineCore* core_get_pointer (const IFBEngineGlobalHandleCore core_handle);
};

/**********************************************************************************/
/* CORE TAG                                                                       */
/**********************************************************************************/

namespace ifb_engine {

    const IFBTagId core_tag_reserve   (const IFBEngineCore* ptr_core, const IFBEngineMemory* ptr_memory, const ifb_cstr tag_c_str);
    const IFBTagId core_tag_release   (const IFBEngineCore* ptr_core, const IFBEngineMemory* ptr_memory, const IFBTagId tag_id);
    const ifb_cstr core_tag_get_value (const IFBEngineCore* ptr_core, const IFBEngineMemory* ptr_memory, const IFBTagId tag_id);
    const ifb_cstr core_tag_get_hash  (const IFBEngineCore* ptr_core, const IFBEngineMemory* ptr_memory, const IFBTagId tag_id);
};

/**********************************************************************************/
/* CORE ARENA                                                                     */
/**********************************************************************************/

namespace ifb_engine {

    const IFBArenaId
    core_arena_commit(
        const IFBEngineCore*   ptr_core,
        const IFBEngineMemory* ptr_memory, 
        const ifb_u32          arena_size_minimum, 
        const ifb_cstr         arena_tag_c_str);

    const ifb_u32 core_arena_get_size           (const IFBEngineCore* ptr_core, const IFBEngineMemory* ptr_memory, const IFBArenaId arena_id);
    const ifb_u32 core_arena_get_tag_c_str      (const IFBEngineCore* ptr_core, const IFBEngineMemory* ptr_memory, const IFBArenaId arena_id);
    const ifb_u32 core_arena_get_pointer_start  (const IFBEngineCore* ptr_core, const IFBEngineMemory* ptr_memory, const IFBArenaId arena_id);
    const ifb_u32 core_arena_get_pointer_offset (const IFBEngineCore* ptr_core, const IFBEngineMemory* ptr_memory, const IFBArenaId arena_id, const ifb_u32 offset);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP