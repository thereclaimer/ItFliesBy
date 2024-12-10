#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-managers.hpp"

/**********************************************************************************/
/* CORE MANAGERS                                                                  */
/**********************************************************************************/

namespace ifb_engine {

    ifb_void 
    core_managers_create_all(
              IFBEngineCoreManagers& ref_core_managers, 
        const IFBEngineMemory*       ptr_memory);
    
    IFBEngineTagManager*    core_managers_get_pointer_tag_manager    (const IFBEngineCoreManagers& ref_core_managers);
    IFBEngineArenaManager*  core_managers_get_pointer_arena_manager  (const IFBEngineCoreManagers& ref_core_managers);
};

/**********************************************************************************/
/* CORE                                                                           */
/**********************************************************************************/

struct IFBHNDEngineCore : IFBHND;

struct IFBEngineCore {
    IFBHNDEngineMemory       memory_handle;
    IFBHNDEngineTagManager   tag_manager_handle;
    IFBHNDEngineArenaManager arena_manager_handle;
};

namespace ifb_engine {

    const IFBHNDEngineCore core_create (ifb_void);

    
    IFBEngineCore* core_get_pointer (const IFBHNDEngineCore core_handle);

    IFBEngineMemory*     core_get_pointer_memory       (const IFBEngineCore* ptr_core);
    IFBEngineTagManager* core_get_pointer_tag_manager  (const IFBEngineCore* ptr_core);
    IFBEngineTagManager* core_get_pointer_arena_manager(const IFBEngineCore* ptr_core);
};

/**********************************************************************************/
/* CORE MEMORY                                                                    */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_ptr core_memory_get_pointer(const IFBEngineCore* ptr_core, const ifb_u32 offset);
};

/**********************************************************************************/
/* CORE TAG                                                                       */
/**********************************************************************************/

namespace ifb_engine {

    const IFBIDTag core_tag_reserve   (const IFBEngineCore* ptr_core, const ifb_cstr tag_c_str);
    const IFBIDTag core_tag_release   (const IFBEngineCore* ptr_core, const IFBIDTag tag_id);
    const ifb_cstr core_tag_get_value (const IFBEngineCore* ptr_core, const IFBIDTag tag_id);
    const ifb_cstr core_tag_get_hash  (const IFBEngineCore* ptr_core, const IFBIDTag tag_id);
};

/**********************************************************************************/
/* CORE ARENA                                                                     */
/**********************************************************************************/

namespace ifb_engine {

    const IFBIDArena
    core_arena_commit(
        const IFBEngineCore*   ptr_core,
        const ifb_u32          arena_size_minimum, 
        const ifb_cstr         arena_tag_c_str);

    const ifb_u32 core_arena_get_size           (const IFBEngineCore* ptr_core, const IFBIDArena arena_id);
    const ifb_u32 core_arena_get_tag_c_str      (const IFBEngineCore* ptr_core, const IFBIDArena arena_id);
    const ifb_u32 core_arena_get_start          (const IFBEngineCore* ptr_core, const IFBIDArena arena_id);
    const ifb_u32 core_arena_get_pointer_start  (const IFBEngineCore* ptr_core, const IFBIDArena arena_id);
    const ifb_u32 core_arena_get_pointer_offset (const IFBEngineCore* ptr_core, const IFBIDArena arena_id, const ifb_u32 offset);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP 