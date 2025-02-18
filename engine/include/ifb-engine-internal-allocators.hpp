#ifndef IFB_ENGINE_INTERNAL_ALLOCATORS_HPP
#define IFB_ENGINE_INTERNAL_ALLOCATORS_HPP

#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* ALLOCATOR BASE                                                                 */
/**********************************************************************************/

struct IFBEngineLinearAllocatorBase {
    IFBEngineMemoryArenaLinear linear_arena;
    IFBU32                    size;
};

struct IFBEngineBlockAllocatorBase {
    IFBHNDMemoryArenaBlock block_arena;
    IFBU32                   block_size;
    IFBU32                   block_count;
    IFBU32*                  block_index_array;
    IFBPtr*                  block_pointer_array;
};

/**********************************************************************************/
/* DATA STRUCTURE ALLOCATOR                                                       */
/**********************************************************************************/

struct IFBEngineDataStructureAllocator : IFBEngineBlockAllocatorBase { };

namespace ifb_engine {

    IFBArray*     data_structures_reserve_array      (IFBEngineDataStructureAllocator* allocator_ptr, const IFBU32 size);
    IFBArrayList* data_structures_reserve_array_list (IFBEngineDataStructureAllocator* allocator_ptr, const IFBU32 element_size, const IFBU32 element_count);
    IFBStack*     data_structures_reserve_stack      (IFBEngineDataStructureAllocator* allocator_ptr, const IFBU32 size);

    IFBArray*     data_structures_release_array      (IFBEngineDataStructureAllocator* allocator_ptr, IFBArray*     array_ptr);
    IFBArrayList* data_structures_release_array_list (IFBEngineDataStructureAllocator* allocator_ptr, IFBArrayList* array_list_ptr);
    IFBStack*     data_structures_release_stack      (IFBEngineDataStructureAllocator* allocator_ptr, IFBStack*     stack_ptr);


};

#endif //IFB_ENGINE_INTERNAL_ALLOCATORS_HPP