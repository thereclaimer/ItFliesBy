#ifndef IFB_ENGINE_INTERNAL_ALLOCATORS_HPP
#define IFB_ENGINE_INTERNAL_ALLOCATORS_HPP

#include "ifb-engine.hpp"

namespace ifb_engine {

    IFBEngineLinearAllocator* linear_allocator_from_handle(const IFBEngineLinearAllocatorHandle linear_allocator_handle);
    IFBEngineTableAllocator*  table_allocator_from_handle (const IFBEngineTableAllocatorHandle table_allocator_handle);
};

#endif //IFB_ENGINE_INTERNAL_ALLOCATORS_HPP