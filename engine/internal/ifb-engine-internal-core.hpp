#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* ENGINE CORE                                                                            */
/**********************************************************************************/

struct IFBEngineCoreManagers {
    ifb_handle_memory memory;
    ifb_handle_memory assets;
    ifb_handle_memory tables;
};

struct IFBEngineCoreSystems {
    ifb_handle_memory physics;
    ifb_handle_memory rendering;
};

struct IFBEngineCoreStackAllocators {
    IFBEngineStackAllocatorId frame;
    IFBEngineStackAllocatorId platform;
    IFBEngineStackAllocatorId window;
};

struct IFBEngineCore {
    IFBEngineCoreManagers        managers;
    IFBEngineCoreStackAllocators stack_allocators;
};

namespace ifb_engine {

    IFBEngineCore* core_pointer_from_context (ifb_void);
    
    const ifb_handle_memory core_manager_handle_memory     (ifb_void);
    const ifb_handle_memory core_manager_handle_assets     (ifb_void);
    const ifb_handle_memory core_manager_handle_tables     (ifb_void);

    const IFBEngineStackAllocatorId core_stack_allocator_platform (ifb_void);
    const IFBEngineStackAllocatorId core_stack_allocator_frame    (ifb_void);
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

    const ifb_b8 core_task_create_core_handle      (ifb_handle_memory&          engine_core_handle_ref);
    const ifb_b8 core_task_create_managers         (IFBEngineCoreManagers&        engine_core_managers_ref);
    const ifb_b8 core_task_create_stack_allocators (IFBEngineCoreStackAllocators& engine_core_stack_allocators_ref);
    const ifb_b8 core_task_create_and_show_window  (ifb_void);
    const ifb_b8 core_task_window_frame_start      (ifb_void);
    const ifb_b8 core_task_window_frame_render     (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP