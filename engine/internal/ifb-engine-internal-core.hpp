#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-tables.hpp"

struct IFBEngineCore;

/**********************************************************************************/
/* ENGINE CORE MANAGERS                                                           */
/**********************************************************************************/

struct IFBEngineCoreManagers {
    IFBEngineMemoryHandle assets;
};

namespace ifb_engine {

    const IFBEngineMemoryHandle core_manager_handle_assets (ifb_void);
};

/**********************************************************************************/
/* ENGINE CORE ALLOCATORS                                                         */
/**********************************************************************************/

struct IFBEngineCoreAllocators {
    struct {
        IFBEngineLinearAllocatorHandle frame;
        IFBEngineLinearAllocatorHandle platform;
    } linear_allocators;
    IFBEngineTableAllocatorHandle table_allocator;
};

namespace ifb_engine {

    const IFBEngineLinearAllocatorHandle core_allocator_linear_frame    (ifb_void);
    const IFBEngineLinearAllocatorHandle core_allocator_linear_platform (ifb_void);
    const IFBEngineTableAllocatorHandle  core_allocator_table           (ifb_void);
};

/**********************************************************************************/
/* ENGINE CORE TABLES                                                             */
/**********************************************************************************/

struct IFBEngineCoreTables {
    IFBEngineTableHandleTag   tag;
    IFBEngineTableHandleArena arena;
};

namespace ifb_engine {

    inline IFBEngineTableTag*   core_table_tag   (const IFBEngineCore* engine_core_ptr);
    inline IFBEngineTableArena* core_table_arena (const IFBEngineCore* engine_core_ptr);
};

/**********************************************************************************/
/* ENGINE CORE ROUTINES                                                           */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8 core_routine_initialize   (ifb_void);    
    const ifb_b8 core_routine_startup      (ifb_void);
    const ifb_b8 core_routine_frame_start  (ifb_void);
    const ifb_b8 core_routine_frame_render (ifb_void);
};

/**********************************************************************************/
/* ENGINE CORE TASKS                                                              */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8 core_task_create_core_handle      (IFBEngineMemoryHandle&   engine_core_handle_ref);
    const ifb_b8 core_task_create_managers         (IFBEngineCoreManagers&   engine_core_managers_ref);
    const ifb_b8 core_task_create_allocators       (IFBEngineCoreAllocators& engine_core_allocators_ref);
    const ifb_b8 core_task_create_and_show_window  (ifb_void);
    const ifb_b8 core_task_window_frame_start      (ifb_void);
    const ifb_b8 core_task_window_frame_render     (ifb_void);
};

/**********************************************************************************/
/* ENGINE CORE                                                                     */
/**********************************************************************************/

struct IFBEngineCore {
    IFBEngineCoreManagers   managers;
    IFBEngineCoreAllocators allocators;
    IFBEngineCoreTables     tables;
};

namespace ifb_engine {

    IFBEngineCore* core_pointer_from_context (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP