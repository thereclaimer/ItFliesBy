#pragma once

#include "ifb-io.hpp"

#include "ifb-io-file-table-initialization.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

/**********************************************************************************/
/* READ ONLY                                                                      */
/**********************************************************************************/

const IFBHNDFileTable 
ifb_file_table::commit_read_only(const IFBFileTableArgs* args) {

    //create our initalization struct
    IFBFileTableReadOnlyInit init;
    init.args          = (IFBFileTableArgs*)args;
    init.sizes         = NULL;
    init.table         = NULL;
    init.handle.offset = 0;

    //file table initialization steps
    ifb_file_table::read_only_init_step_0_args_assert        (init);
    ifb_file_table::read_only_init_step_1_reserve_size_cache (init);
    ifb_file_table::read_only_init_step_2_commit_table       (init);
    ifb_file_table::read_only_init_step_3_release_size_cache (init);

    //reserve our commit sizes
    IFBFileTableReadOnlySizes* commit_size = ifb_file_table::read_only_sizes_reserve(args);

    //get the context data size
    const IFBU32 file_context_data_size = ifb_platform::file_ro_context_size();
    ifb_macro_assert(file_context_data_size);

    //calculate commit sizes
    ifb_file_table::args_read_only_commit_size_calculate(
        args,
        file_context_data_size,
        commit_size);

    //do the commit
    const IFBHNDArena file_table_arena      = args->arena_handle;
    const IFBU32      file_table_size_total = commit_size->total;  
    const IFBU32      file_table_offset     = ifb_memory::arena_commit_bytes_relative(
        file_table_arena,
        file_table_size_total);

    //load the pointer
    IFBFileReadOnlyTable* file_table = (IFBFileReadOnlyTable*)ifb_memory::arena_get_pointer(
        file_table_arena,
        file_table_offset);

    //make sure its valid
    ifb_macro_assert(file_table);

    //cache args
    const IFBAddr              file_table_start = (IFBAddr)file_table;
    const IFBU32               file_count       = args->file_count;
    const IFBFileAsyncCallback file_callback    = args->file_callback_read;

    //set header properties
    file_table->header.start            = file_table_start;
    file_table->header.size             = commit_size->total;
    file_table->header.file_count       = file_count; 
    file_table->header.file_path_stride = args->file_path_stride;
    file_table->header.callback         = file_callback; 

    //calculate the offsets
    const IFBU16 offset_file_path_buffer        = commit_size->properties.file_table_size;
    const IFBU16 offset_array_file_context      = commit_size->properties.file_path_buffer        + offset_file_path_buffer;
    const IFBU16 offset_array_last_bytes_read   = commit_size->properties.array_file_context      + offset_array_file_context;
    const IFBU16 offset_array_list_files_open   = commit_size->properties.array_last_bytes_read   + offset_array_last_bytes_read;
    const IFBU16 offset_array_list_files_closed = commit_size->properties.array_list_files_open   + offset_array_list_files_open;
    const IFBU16 offset_array_list_files_locked = commit_size->properties.array_list_files_closed + offset_array_list_files_closed;
    const IFBU16 offset_context_data            = commit_size->properties.array_list_files_locked + offset_array_list_files_locked;

    //set handles
    file_table->handles.file_path_buffer.offset        = offset_file_path_buffer;
    file_table->handles.array_file_context.offset      = offset_array_file_context;
    file_table->handles.array_last_bytes_read.offset   = offset_array_last_bytes_read;
    file_table->handles.array_list_files_open.offset   = offset_array_list_files_open;
    file_table->handles.array_list_files_closed.offset = offset_array_list_files_closed;
    file_table->handles.array_list_files_locked.offset = offset_array_list_files_locked;

    //load the list memory
    const IFBPtr ptr_memory_list_file_open   = ifb_memory::arena_get_pointer(file_table_arena, offset_array_list_files_open);
    const IFBPtr ptr_memory_list_file_closed = ifb_memory::arena_get_pointer(file_table_arena, offset_array_list_files_closed);
    const IFBPtr ptr_memory_list_file_locked = ifb_memory::arena_get_pointer(file_table_arena, offset_array_list_files_locked);

    //initialize the lists
    const IFBU32 element_size = sizeof(IFBHNDFile);
    IFBArrayList* list_file_open   = ifb_array_list::memory_initialize(element_size, file_count, ptr_memory_list_file_open);
    IFBArrayList* list_file_closed = ifb_array_list::memory_initialize(element_size, file_count, ptr_memory_list_file_closed);
    IFBArrayList* list_file_locked = ifb_array_list::memory_initialize(element_size, file_count, ptr_memory_list_file_locked);

    //assert the lists are valid
    ifb_macro_assert(list_file_open);
    ifb_macro_assert(list_file_closed);
    ifb_macro_assert(list_file_locked);

    //load the context array
    IFBFileContext* file_context_array = (IFBFileContext*)ifb_memory::arena_get_pointer(file_table_arena,offset_array_file_context);
    ifb_macro_assert(file_context_array);

    //initialize the contexts
    for (
        IFBU32 file_context_index = 0;
               file_context_index < file_count;
             ++file_context_index) {

        //calculate info
        const IFBU32    current_file_context_data_offset = file_context_index * file_context_data_size;
        IFBFileContext& current_file_context_ref         = file_context_array[file_context_index];

        //initialize the context
        current_file_context_ref.memory_start               = file_table_start;
        current_file_context_ref.callback_read              = file_callback;
        current_file_context_ref.callback_write             = NULL;
        current_file_context_ref.context_data_size          = file_context_data_size;
        current_file_context_ref.bytes_transferred          = 0;
        current_file_context_ref.handle_context_data.offset = current_file_context_data_offset;
    }

    //release the commit sizes
    ifb_file_table::args_read_only_commit_size_release(args);

    //we're done
    return(file_table_handle);
} 

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBVoid
ifb_file_table::read_only_init_step_0_args_assert(
    IFBFileTableReadOnlyInit& init_ref) {

    ifb_macro_assert(init_ref.args);
    ifb_macro_assert(init_ref.args->arena_handle.pointer != NULL);
    ifb_macro_assert(init_ref.args->file_callback_read   != NULL);
    ifb_macro_assert(init_ref.args->file_path_buffer     != NULL);
    ifb_macro_assert(init_ref.args->file_path_stride     != NULL);
    ifb_macro_assert(init_ref.args->file_count           != NULL);
}


inline IFBVoid
ifb_file_table::read_only_init_step_1_reserve_sizes(
    IFBFileTableReadOnlyInit& init_ref) {

    //calculate the struct size
    const IFBU32 size = ifb_macro_align_size_struct(IFBFileTableReadOnlySizes);

    //commit the struct
    IFBFileTableReadOnlySizes* table_sizes = (IFBFileTableReadOnlySizes*)ifb_memory::arena_reserve_bytes_absolute(
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
ifb_file_table::read_only_init_step_3_release_sizes(
    const IFBFileTableArgs* args) {

    const IFBU32 size   = ifb_macro_align_size_struct(IFBFileTableReadOnlySizes);
    const IFBB8  result = ifb_memory::arena_release_bytes(args->arena_handle,size);

    ifb_macro_assert(result);
}

inline const IFBU32
ifb_file_table::read_only_init_step_2_commit_table(
    IFBFileTableReadOnlyInit& init_ref) {

}
