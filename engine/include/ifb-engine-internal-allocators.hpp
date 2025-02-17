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
    ifb_u32                    size;
};

struct IFBEngineBlockAllocatorBase {
    IFBMemoryBlockArenaHandle block_arena;
    ifb_u32                   block_size;
    ifb_u32                   block_count;
    ifb_u32*                  block_index_array;
    ifb_ptr*                  block_pointer_array;
};

/**********************************************************************************/
/* DATA STRUCTURE ALLOCATOR                                                       */
/**********************************************************************************/

struct IFBEngineDataStructureAllocator : IFBEngineBlockAllocatorBase { };

namespace ifb_engine {

    IFBArray*     data_structures_reserve_array      (IFBEngineDataStructureAllocator* allocator_ptr, const ifb_u32 size);
    IFBArrayList* data_structures_reserve_array_list (IFBEngineDataStructureAllocator* allocator_ptr, const ifb_u32 element_size, const ifb_u32 element_count);
    IFBStack*     data_structures_reserve_stack      (IFBEngineDataStructureAllocator* allocator_ptr, const ifb_u32 size);

    IFBArray*     data_structures_release_array      (IFBEngineDataStructureAllocator* allocator_ptr, IFBArray*     array_ptr);
    IFBArrayList* data_structures_release_array_list (IFBEngineDataStructureAllocator* allocator_ptr, IFBArrayList* array_list_ptr);
    IFBStack*     data_structures_release_stack      (IFBEngineDataStructureAllocator* allocator_ptr, IFBStack*     stack_ptr);


};

#endif //IFB_ENGINE_INTERNAL_ALLOCATORS_HPP