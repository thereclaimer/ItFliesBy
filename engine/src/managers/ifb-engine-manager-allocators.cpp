#pragma once

#include "ifb-engine-internal-managers.hpp"

inline const IFBEngineGlobalHandleAllocatorManager
ifb_engine::allocator_manager_create(
          IFBEngineMemory* ptr_engine_memory,
    const ifb_u32          linear_allocator_count_max,
    const ifb_u32          block_allocator_count_max) {

    IFBEngineGlobalHandleAllocatorManager allocator_manager_handle;
    ifb_engine_global_stack_push_type(allocator_manager_handle, IFBEngineAllocatorManager);

    //calculate the size of the linear allocator info
    const ifb_u32 stack_allocator_struct_size         = ifb_macro_align_size_struct(IFBEngineLinearAllocators);
    const ifb_u32 stack_allocator_size_arena_id_array = ifb_macro_size_array(IFBArenaId,                  stack_allocator_count_max);
    const ifb_u32 stack_allocator_size_info_array     = ifb_macro_size_array(IFBEngineLinearAllocatorInfo,stack_allocator_count_max);

    //calculate the size of the block allocator info
    const ifb_u32 block_allocator_struct_size         = ifb_macro_align_size_struct(IFBEngineBlockAllocators);
    const ifb_u32 block_allocator_size_arena_id_array = ifb_macro_size_array(IFBArenaId,                 block_allocator_count_max);
    const ifb_u32 block_allocator_size_info_array     = ifb_macro_size_array(IFBEngineBlockAllocatorInfo,block_allocator_count_max);
    const ifb_u32 block_allocator_address_ptr_array   = ifb_macro_size_array(ifb_address*,               block_allocator_count_max);

    //calculate the total commit size
    const ifb_u32 stack_allocator_size_total = 
        stack_allocator_struct_size         +
        stack_allocator_size_arena_id_array +
        stack_allocator_size_info_array;        

    const ifb_u32 block_allocator_size_total = 
        block_allocator_struct_size         +
        block_allocator_size_arena_id_array +
        block_allocator_size_info_array     +
        block_allocator_address_ptr_array;

    const ifb_u32 allocator_manager_commit_size = 
        stack_allocator_size_total +
        block_allocator_size_total;

    //calculate offsets
    const ifb_u32 commit_offset_linear_allocator_arena_id_array       = 0; 
    const ifb_u32 commit_offset_linear_allocator_info_array           = stack_allocator_struct_size;
    const ifb_u32 commit_offset_block_allocator_arena_id_array        = commit_offset_linear_allocator_info_array + block_allocator_struct_size;
    const ifb_u32 commit_offset_block_allocator_info_array            = commit_offset_block_allocator_arena_id_array + block_allocator_size_arena_id_array;
    const ifb_u32 commit_offset_block_allocator_address_pointer_array = commit_offset_block_allocator_info_array + block_allocator_size_info_array;

    //do the commit
    const IFBCommitId commit_id = ifb_engine::memory_commit(ptr_engine_memory,allocator_manager_commit_size);

    //get the allocator pointers
    IFBEngineAllocatorManager* ptr_allocator_manager = ifb_engine::global_stack_get_pointer(allocator_manager_handle);
    
    IFBEngineLinearAllocators* ptr_linear_allocators = ifb_engine::allocator_manager_get_pointer_linear_allocators(
        ptr_allocator_manager,
        ptr_engine_memory);

    IFBEngineBlockAllocators* ptr_block_allocators = ifb_engine::allocator_manager_get_pointer_block_allocators(
        ptr_allocator_manager,
        ptr_engine_memory);

    //initialize the manager structure
    ptr_allocator_manager->commit_id                        = commit_id;
    ptr_allocator_manager->commit_offsets.linear_allocators = 0;
    ptr_allocator_manager->commit_offsets.block_allocators  = stack_allocator_struct_size;

    //initialize the linear allocators
    ptr_linear_allocators->count_max                            = linear_allocator_count_max;
    ptr_linear_allocators->count_committed                      = 0;
    ptr_linear_allocators->commit_offsets.arena_id              = commit_offset_linear_allocator_arena_id_array;
    ptr_linear_allocators->commit_offsets.linear_allocator_info = commit_offset_linear_allocator_info_array;

    //initialize the block allocators
    ptr_block_allocators->count_max                           = block_allocator_count_max;
    ptr_block_allocators->count_committed                     = 0;
    ptr_block_allocators->commit_offsets.arena_id             = commit_offset_block_allocator_arena_id_array;
    ptr_block_allocators->commit_offsets.block_allocator_info = commit_offset_block_allocator_info_array;
    ptr_block_allocators->commit_offsets.block_addresses_ptr  = commit_offset_block_allocator_address_pointer_array;

    //we're done
    return(allocator_manager_handle);
}

inline IFBEngineLinearAllocators* 
ifb_engine::allocator_manager_get_pointer_linear_allocators(
    const IFBEngineAllocatorManager* ptr_allocator_manager, 
    const IFBEngineMemory*           ptr_engine_memory) {

    IFBEngineLinearAllocators* ptr_linear_allocators = (IFBEngineLinearAllocators*)ifb_engine::memory_get_commit_pointer(
        ptr_engine_memory,
        ptr_allocator_manager->commit_id,
        ptr_allocator_manager->commit_offsets.linear_allocators);

    return(ptr_linear_allocators);
}

inline IFBEngineBlockAllocators*  
ifb_engine::allocator_manager_get_pointer_block_allocators(
    const IFBEngineAllocatorManager* ptr_allocator_manager, 
    const IFBEngineMemory*           ptr_engine_memory) {

    IFBEngineBlockAllocators* ptr_block_allocators = (IFBEngineBlockAllocators*)ifb_engine::memory_get_commit_pointer(
        ptr_engine_memory,
        ptr_allocator_manager->commit_id,
        ptr_allocator_manager->commit_offsets.block_allocators);

    return(ptr_block_allocators);
}