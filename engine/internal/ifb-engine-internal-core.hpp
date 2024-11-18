#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* ENGINE CORE                                                                            */
/**********************************************************************************/

struct IFBEngineCoreManagers {
    ifb_handle_memory_t memory;
    ifb_handle_memory_t tag;
    ifb_handle_memory_t allocators;
    ifb_handle_memory_t assets;
};

struct IFBEngineCoreSystems {
    ifb_handle_memory_t physics;
    ifb_handle_memory_t rendering;
};

struct IFBEngineCoreStackAllocators {
    ifb_index_stack_t frame;
    ifb_index_stack_t platform;
    ifb_index_stack_t window;
};

struct IFBEngineCore {
    IFBEngineCoreManagers        managers;
    IFBEngineCoreStackAllocators stack_allocators;
};

namespace ifb_engine {

    IFBEngineCore* core_pointer_from_context (ifb_void);
    
    const ifb_handle_memory_t core_manager_handle_memory     (ifb_void);
    const ifb_handle_memory_t core_manager_handle_tag        (ifb_void);
    const ifb_handle_memory_t core_manager_handle_allocators (ifb_void);
    const ifb_handle_memory_t core_manager_handle_assets     (ifb_void);

    const ifb_index_stack_t core_stack_allocator_platform (ifb_void);
    const ifb_index_stack_t core_stack_allocator_frame    (ifb_void);
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

    const ifb_b8 core_task_create_core_handle      (ifb_handle_memory_t&          engine_core_handle_ref);
    const ifb_b8 core_task_create_managers         (IFBEngineCoreManagers&        engine_core_managers_ref);
    const ifb_b8 core_task_create_stack_allocators (IFBEngineCoreStackAllocators& engine_core_stack_allocators_ref);
    const ifb_b8 core_task_create_and_show_window  (ifb_void);
    const ifb_b8 core_task_window_frame_start (ifb_void);
    const ifb_b8 core_task_window_frame_render (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP