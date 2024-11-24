#ifndef IFB_ENGINE_ALLOCATORS_HPP
#define IFB_ENGINE_ALLOCATORS_HPP

#include <ifb-common.hpp>

#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* LINEAR ALLOCATOR                                                               */
/**********************************************************************************/

struct IFBEngineLinearAllocatorId {
    struct {
        ifb_index arena;
        ifb_index linear_allocator;
    } table_indexes;
};

struct IFBEngineLinearAllocator {
    IFBEngineLinearAllocatorId id;
    ifb_u32                    position;
    ifb_u32                    save_point;
};

namespace ifb_engine {

    ifb_api ifb_b8  
    linear_allocator_create(
        const ifb_cstr                     in_linear_allocator_tag_cstr,
        const ifb_u32                      in_linear_allocator_size_minimum,
              IFBEngineLinearAllocatorId& out_linear_allocator_id);
    
    ifb_api const ifb_handle_memory linear_allocator_reserve             (const IFBEngineLinearAllocatorId linear_allocator_id, const ifb_u32 size);
    ifb_api const ifb_handle_memory linear_allocator_release             (const IFBEngineLinearAllocatorId linear_allocator_id, const ifb_u32 size);
    ifb_api const ifb_b8            linear_allocator_save_point_set      (const IFBEngineLinearAllocatorId linear_allocator_id);
    ifb_api const ifb_b8            linear_allocator_save_point_clear    (const IFBEngineLinearAllocatorId linear_allocator_id);
    ifb_api const ifb_b8            linear_allocator_reset               (const IFBEngineLinearAllocatorId linear_allocator_id);
    ifb_api const ifb_b8            linear_allocator_reset_to_save_point (const IFBEngineLinearAllocatorId linear_allocator_id);
};

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineBlockAllocatorId {
    struct {
        ifb_index arena;
        ifb_index block_allocator;
    } table_indexes;
};

struct IFBEngineBlockMemory {
    ifb_handle_memory start;
};

struct IFBEngineBlockAllocator {
    IFBEngineBlockAllocatorId id;
    ifb_u32                   block_count;
    ifb_u32                   block_size;
    IFBEngineBlockMemory*     block_ptr;
};

namespace ifb_engine {

    ifb_api const ifb_b8 
    block_allocator_create(
        const ifb_cstr                  in_block_allocator_tag,
        const ifb_u32                   in_block_size,
        const ifb_u32                   in_block_count,
              IFBEngineBlockAllocator& out_block_allocator_ref);

    ifb_api const ifb_b8 block_allocator_reserve (const IFBEngineBlockAllocatorId in_block_allocator_id, IFBEngineBlockMemory& out_block_ref);
    ifb_api const ifb_b8 block_allocator_release (const IFBEngineBlockAllocatorId in_block_allocator_id, IFBEngineBlockMemory& out_block_ref);
    ifb_api const ifb_b8 block_allocator_reset   (const IFBEngineBlockAllocatorId in_block_allocator_id);
};

/**********************************************************************************/
/* TABLE ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineTableAllocatorId {
    struct {
        ifb_index arena;
        ifb_index table_allocator;
    } table_indexes;
};

struct IFBEngineTableMemoryHandle {
    ifb_handle_memory  table_header_start;
    ifB_handle_memory* column_start_ptr;
    ifb_u32            column_count;
};

struct IFBEngineTableAllocator {
    IFBEngineTableAllocatorId    
};

namespace ifb_engine {

    const ifb_b8
    table_allocator_reserve(
        const IFBEngineTableAllocatorId in_table_allocator_ref,
        const ifb_u32                   in_table_header_size,
        const ifb_u32                   in_table_row_count,
        const ifb_u32                   in_table_column_count,
        const ifb_u32*                  in_table_column_sizes,
              ifb_memory               out_table_header,
              ifb_memory*              out_table_columns);

};

#endif //IFB_ENGINE_ALLOCATORS_HPP