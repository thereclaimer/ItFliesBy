#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-managers.hpp"

/**********************************************************************************/
/* CORE MANAGERS                                                                  */
/**********************************************************************************/

#define IFB_ENGINE_CORE_DEFAULT_ARENA_SIZE  4096
#define IFB_ENGINE_CORE_DEFAULT_ARENA_COUNT  128

struct IFBEngineCoreManagerHandles {
    IFBEngineMemoryManagerHandle memory;
    IFBEngineTagManagerHandle    tag;
    IFBEngineArenaManagerHandle  arena;
};

namespace ifb_engine {

    ifb_void                core_managers_create_all                 (IFBEngineCoreManagerHandles& ref_core_managers);
    IFBEngineMemoryManager* core_managers_get_pointer_memory_manager (const IFBEngineCoreManagerHandles& ref_core_managers);
    IFBEngineTagManager*    core_managers_get_pointer_tag_manager    (const IFBEngineCoreManagerHandles& ref_core_managers);
    IFBEngineArenaManager*  core_managers_get_pointer_arena_manager  (const IFBEngineCoreManagerHandles& ref_core_managers);
};

/**********************************************************************************/
/* CORE                                                                           */
/**********************************************************************************/

struct IFBEngineCoreHandle {
    ifb_handle value;
};

struct IFBEngineCore {
    IFBEngineCoreManagerHandles manager_handles;
};

namespace ifb_engine {

    const IFBEngineCoreHandle core_create (ifb_void);

    IFBEngineCore*          core_get_pointer                (const IFBEngineCoreHandle core_handle);

};

/**********************************************************************************/
/* CORE MEMORY                                                                    */
/**********************************************************************************/

namespace ifb_engine {

    const IFBMemoryCommitId core_memory_commit          (const IFBEngineCore* ptr_core, const ifb_u32 size);
          ifb_ptr           core_memory_get_pointer     (const IFBEngineCore* ptr_core, const IFBMemoryCommitId commit_id)
          ifb_ptr           core_memory_get_pointer     (const IFBEngineCore* ptr_core, const IFBMemoryCommitId commit_id, const ifb_u32 offset);
          ifb_ptr           core_memory_get_pointer     (const IFBEngineCore* ptr_core, const ifb_handle        handle);
    const ifb_u32           core_memory_get_commit_size (const IFBEngineCore* ptr_core, const IFBMemoryCommitId commit_id);
};

/**********************************************************************************/
/* CORE TAG                                                                       */
/**********************************************************************************/

namespace ifb_engine {

    const IFBTagId core_tag_reserve   (const IFBEngineCore* ptr_core, const ifb_cstr tag_c_str);
    const IFBTagId core_tag_release   (const IFBEngineCore* ptr_core, const IFBTagId tag_id);
    const ifb_cstr core_tag_get_value (const IFBEngineCore* ptr_core, const IFBTagId tag_id);
    const ifb_cstr core_tag_get_hash  (const IFBEngineCore* ptr_core, const IFBTagId tag_id);
};

/**********************************************************************************/
/* CORE ARENA                                                                     */
/**********************************************************************************/

namespace ifb_engine {

    const IFBArenaId
    core_arena_commit(
              IFBEngineCore* ptr_core, 
        const ifb_u32        arena_size_minimum, 
        const ifb_cstr       arena_tag_c_str);

    const ifb_u32 core_arena_get_size           (IFBEngineCore* ptr_core, const IFBArenaId arena_id);
    const ifb_u32 core_arena_get_tag_c_str      (IFBEngineCore* ptr_core, const IFBArenaId arena_id);
    const ifb_u32 core_arena_get_pointer_start  (IFBEngineCore* ptr_core, const IFBArenaId arena_id);
    const ifb_u32 core_arena_get_pointer_offset (IFBEngineCore* ptr_core, const IFBArenaId arena_id, const ifb_u32 offset);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP