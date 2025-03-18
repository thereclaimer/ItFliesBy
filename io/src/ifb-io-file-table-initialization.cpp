#pragma once

#include "ifb-io.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBFileTableReadOnlySizeCache {
    struct {
        IFBU32 context_data;
        IFBU32 commit_max;
        IFBU32 file_handle;
        IFBU32 array_list;
        IFBU32 context_struct;
        IFBU32 sizes_struct;
    } tmp_cache;
    
    struct {
        IFBU16 total;
        IFBU16 file_table_size;
        IFBU16 file_path_buffer;
        IFBU16 array_file_context;
        IFBU16 array_last_bytes_read;
        IFBU16 array_list_files_open;
        IFBU16 array_list_files_closed;
        IFBU16 array_list_files_locked;
        IFBU16 context_memory_size;
    } commit;
};

struct IFBFileTableReadOnlyInit {
    IFBFileTableArgs*               args;
    IFBFileTableReadOnlySizeCache* sizes;
    IFBFileReadOnlyTable*      table;
    IFBHNDFileTable            handle;
};

namespace ifb_file_table {
    
    IFBVoid read_only_init_step_0_args_assert        (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_1_reserve_size_cache (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_2_commit_table       (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_3_release_size_cache (IFBFileTableReadOnlyInit& init_ref);
};

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBVoid
ifb_file_table::read_only_init_step_0_validate_args(
    IFBFileTableReadOnlyInit& init_ref) {

    ifb_macro_assert(init_ref.args);
    ifb_macro_assert(init_ref.args->arena_handle.pointer != NULL);
    ifb_macro_assert(init_ref.args->file_callback_read   != NULL);
    ifb_macro_assert(init_ref.args->file_path_buffer     != NULL);
    ifb_macro_assert(init_ref.args->file_path_stride     != NULL);
    ifb_macro_assert(init_ref.args->file_count           != NULL);
}

inline IFBVoid
ifb_file_table::read_only_init_step_1_reserve_size_cache(
    IFBFileTableReadOnlyInit& init_ref) {

    //calculate the struct size
    const IFBU32 size = ifb_macro_align_size_struct(IFBFileTableReadOnlySizeCache);

    //commit the struct
    IFBFileTableReadOnlySizeCache* table_sizes = (IFBFileTableReadOnlySizeCache*)ifb_memory::arena_reserve_bytes_absolute(
        init_ref.args->arena_handle,
        size);

    //sanity check    
    ifb_macro_assert(table_sizes);

    //create a cache of static values
    const IFBU32 file_count               = init_ref.args->file_count; 
    const IFBU32 file_path_stride         = init_ref.args->file_path_stride;
    const IFBU32 file_handle_size         = sizeof(IFBHNDFile);
    table_sizes->tmp_cache.context_data   = ifb_platform::file_ro_context_size();
    table_sizes->tmp_cache.commit_max     = 0xFFFF; 
    table_sizes->tmp_cache.file_handle    = file_handle_size;
    table_sizes->tmp_cache.array_list     = ifb_array_list::memory_allocation_size(file_handle_size,file_count);
    table_sizes->tmp_cache.context_struct = ifb_macro_align_size_struct(IFBFileContext);

    //property sizes
    const IFBU32 commit_size_file_table              = ifb_macro_align_size_struct(IFBFileReadOnlyTable); 
    const IFBU32 commit_size_file_path_buffer        = file_count * file_path_stride;
    const IFBU32 commit_size_array_file_context      = file_count * table_sizes->tmp_cache.context_struct;
    const IFBU32 commit_size_array_last_bytes_read   = file_count * sizeof(IFBU32);
    const IFBU32 commit_size_array_list_files_open   = table_sizes->tmp_cache.array_list;
    const IFBU32 commit_size_array_list_files_closed = table_sizes->tmp_cache.array_list;
    const IFBU32 commit_size_array_list_files_locked = table_sizes->tmp_cache.array_list;
    const IFBU32 commit_size_context_data            = file_count * table_sizes->tmp_cache.context_struct;

    //make sure the properties are within the expected commit size
    ifb_macro_assert(commit_size_file_table              < table_sizes->tmp_cache.commit_max);
    ifb_macro_assert(commit_size_file_path_buffer        < table_sizes->tmp_cache.commit_max);
    ifb_macro_assert(commit_size_array_file_context      < table_sizes->tmp_cache.commit_max);
    ifb_macro_assert(commit_size_array_last_bytes_read   < table_sizes->tmp_cache.commit_max);
    ifb_macro_assert(commit_size_array_list_files_open   < table_sizes->tmp_cache.commit_max);
    ifb_macro_assert(commit_size_array_list_files_closed < table_sizes->tmp_cache.commit_max);
    ifb_macro_assert(commit_size_array_list_files_locked < table_sizes->tmp_cache.commit_max);
    ifb_macro_assert(commit_size_context_data            < table_sizes->tmp_cache.commit_max);

    //total size    
    const IFBU32 commit_size_total = ( 
        commit_size_file_table              +
        commit_size_file_path_buffer        +
        commit_size_array_file_context      +
        commit_size_array_last_bytes_read   +
        commit_size_array_list_files_open   +
        commit_size_array_list_files_closed +
        commit_size_array_list_files_locked +
        commit_size_context_data);

    //update the structure
    table_sizes->commit.total                   = *((IFBU16*)(&commit_size_total));
    table_sizes->commit.file_table_size         = *((IFBU16*)(&commit_size_file_table));        
    table_sizes->commit.file_path_buffer        = *((IFBU16*)(&commit_size_file_path_buffer));        
    table_sizes->commit.array_file_context      = *((IFBU16*)(&commit_size_array_file_context));      
    table_sizes->commit.array_last_bytes_read   = *((IFBU16*)(&commit_size_array_last_bytes_read));   
    table_sizes->commit.array_list_files_open   = *((IFBU16*)(&commit_size_array_list_files_open));   
    table_sizes->commit.array_list_files_closed = *((IFBU16*)(&commit_size_array_list_files_closed)); 
    table_sizes->commit.array_list_files_locked = *((IFBU16*)(&commit_size_array_list_files_locked)); 
    table_sizes->commit.context_memory_size     = *((IFBU16*)(&commit_size_context_data));

    //make sure we are within expected memory size
    ifb_macro_assert(commit_size_total < table_sizes->tmp_cache.commit_max);
}

inline IFBVoid
ifb_file_table::read_only_init_step_3_release_size_cache(
    IFBFileTableReadOnlyInit& init_ref) {

    const IFBU32 size   = ifb_macro_align_size_struct(IFBFileTableReadOnlySizeCache);
    const IFBB8  result = ifb_memory::arena_release_bytes(init_ref.args->arena_handle,size);

    ifb_macro_assert(result);
}

inline IFBVoid 
ifb_file_table::read_only_init_step_2_commit_table(
    IFBFileTableReadOnlyInit& init_ref) {

}
