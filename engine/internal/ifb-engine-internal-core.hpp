#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

struct IFBEngineCoreManagers {
    ifb_memory_handle_t memory;
    ifb_memory_handle_t tag;
    ifb_memory_handle_t allocators;
    ifb_memory_handle_t assets;
};

struct IFBEngineCoreSystems {
    ifb_memory_handle_t physics;
    ifb_memory_handle_t rendering;

};

struct IFBEngineCoreStackAllocators {
    ifb_stack_index_t frame;
    ifb_stack_index_t platform;
    ifb_stack_index_t window;
};

struct IFBEngineCore {
    IFBEngineCoreManagers        managers;
    IFBEngineCoreStackAllocators stack_allocators;
};

namespace ifb_engine {

    const ifb_handle_memory_t core_routine_initialize (ifb_void);    
    const ifb_b8              core_routine_startup    (const ifb_handle_memory_t);    
};


#endif //IFB_ENGINE_INTERNAL_CORE_HPP