#ifndef IFB_ENGINE_ALLOCATORS_HPP
#define IFB_ENGINE_ALLOCATORS_HPP

#include <ifb-common.hpp>

#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* LINEAR ALLOCATOR                                                               */
/**********************************************************************************/

struct IFBEngineLinearAllocatorHandle : IFBEngineMemoryHandle { };

struct IFBEngineLinearAllocator {
    IFBEngineArenaId arena_id;
    ifb_u32          position;
    ifb_u32          save_point;
};

namespace ifb_engine {

    ifb_api ifb_b8  
    linear_allocator_create(
        const ifb_cstr                         in_linear_allocator_tag_cstr,
        const ifb_u32                          in_linear_allocator_size_minimum,
              IFBEngineLinearAllocatorHandle& out_linear_allocator_handle);
    
    ifb_api const IFBEngineMemoryHandle linear_allocator_reserve             (const IFBEngineLinearAllocatorHandle linear_allocator_handle, const ifb_u32 size);
    ifb_api const IFBEngineMemoryHandle linear_allocator_release             (const IFBEngineLinearAllocatorHandle linear_allocator_handle, const ifb_u32 size);
    ifb_api const ifb_b8                linear_allocator_save_point_set      (const IFBEngineLinearAllocatorHandle linear_allocator_handle);
    ifb_api const ifb_b8                linear_allocator_save_point_clear    (const IFBEngineLinearAllocatorHandle linear_allocator_handle);
    ifb_api const ifb_b8                linear_allocator_reset               (const IFBEngineLinearAllocatorHandle linear_allocator_handle);
    ifb_api const ifb_b8                linear_allocator_reset_to_save_point (const IFBEngineLinearAllocatorHandle linear_allocator_handle);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineBlockAllocatorHandle : IFBEngineMemoryHandle { };
struct IFBEngineBlockMemoryHandle    : IFBEngineMemoryHandle { };

struct IFBEngineBlockAllocator {
    IFBEngineArenaId          arena_id;
    ifb_u32                   block_count;
    ifb_u32                   block_size;
    IFBEngineMemoryHandle     block_array_handle;
};

namespace ifb_engine {

    ifb_api const ifb_b8 
    block_allocator_create(
        const ifb_cstr                        in_block_allocator_tag,
        const ifb_u32                         in_block_size,
        const ifb_u32                         in_block_count,
              IFBEngineBlockAllocatorHandle& out_block_allocator_handle_ref);

    ifb_api const ifb_b8 block_allocator_reserve (const IFBEngineBlockAllocatorHandle in_block_allocator_handle, IFBEngineBlockMemoryHandle& out_block_ref);
    ifb_api const ifb_b8 block_allocator_release (const IFBEngineBlockAllocatorHandle in_block_allocator_handle, IFBEngineBlockMemoryHandle& out_block_ref);
    ifb_api const ifb_b8 block_allocator_reset   (const IFBEngineBlockAllocatorHandle in_block_allocator_handle);
};

/**********************************************************************************/
/* TABLE ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineTableAllocatorHandle : IFBEngineMemoryHandle { };
struct IFBEngineTableMemoryHandle    : IFBEngineMemoryHandle { };

struct IFBEngineTableAllocator {
    IFBEngineArenaId arena_id;
    ifb_u32          position;
};

namespace ifb_engine {

    ifb_api const ifb_b8
    table_allocator_create(
        const ifb_cstr                        in_table_allocator_tag_cstr,
        const ifb_u32                         in_table_allocator_size_minimum,
              IFBEngineTableAllocatorHandle& out_table_allocator_ref);

    ifb_api const ifb_b8
    table_allocator_reserve(
        const IFBEngineTableAllocatorHandle in_table_allocator_handle,
        const ifb_u32                       in_table_count_rows,
        const ifb_u32                       in_table_count_columns,
        const ifb_u32                       in_table_size_header,
        const ifb_u32*                      in_table_size_columns_ptr,
              IFBEngineTableMemoryHandle*  out_table_memory_handles_ptr);

    ifb_api const ifb_b8
    table_allocator_reset(const IFBEngineTableAllocatorHandle table_allocator_handle);
};

#endif //IFB_ENGINE_ALLOCATORS_HPP