#pragma once

#include "ifb-engine-allocators.hpp"

ifb_api const ifb_b8
ifb_engine::table_allocator_create(
    const ifb_cstr                        in_table_allocator_tag_cstr,
    const ifb_u32                         in_table_allocator_size_minimum,
          IFBEngineTableAllocatorHandle& out_table_allocator_ref) {

    return(false);
}

ifb_api const ifb_b8
ifb_engine::table_allocator_reserve(
    const IFBEngineTableAllocatorHandle in_table_allocator_handle,
    const ifb_u32                       in_table_count_rows,
    const ifb_u32                       in_table_count_columns,
    const ifb_u32                       in_table_size_header,
    const ifb_u32*                      in_table_size_columns_ptr,
          IFBEngineTableMemoryHandle*  out_table_memory_handles_ptr) {

    return(false);
}

ifb_api const ifb_b8
ifb_engine::table_allocator_reset(
    const IFBEngineTableAllocatorHandle table_allocator_handle) {

    return(false);
}