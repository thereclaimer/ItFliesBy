#pragma once

#include "ifb-io.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBFileTableReadOnlyCommitSize {
    IFBU16 total;
    struct {
        IFBU16 file_table_size;
        IFBU16 file_path_buffer;
        IFBU16 array_file_context;
        IFBU16 array_last_bytes_read;
        IFBU16 array_list_files_open;
        IFBU16 array_list_files_closed;
        IFBU16 array_list_files_locked;
        IFBU16 context_memory_size;
    } properties;
};

namespace ifb_file_table {
    
    IFBVoid                         args_assert_valid                    (const IFBFileTableArgs* args);
    IFBFileTableReadOnlyCommitSize* args_read_only_commit_size_reserve   (const IFBFileTableArgs* args);
    IFBVoid                         args_read_only_commit_size_release   (const IFBFileTableArgs* args);
    IFBVoid                         args_read_only_commit_size_calculate (const IFBFileTableArgs* args, const IFBU32 context_data_size, IFBFileTableReadOnlyCommitSize* commit_size);
};

/**********************************************************************************/
/* READ ONLY                                                                      */
/**********************************************************************************/

const IFBHNDFileTable 
ifb_file_table::commit_read_only(const IFBFileTableArgs* args) {

    IFBHNDFileTable file_table_handle;
    file_table_handle.offset = 0;

    //make sure our arguments are valid
    ifb_file_table::args_assert_valid(args);

    //reserve our commit sizes
    IFBFileTableReadOnlyCommitSize* commit_size = ifb_file_table::args_read_only_commit_size_reserve(args);

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

    //set header properties
    const IFBAddr              file_table_start = (IFBAddr)file_table;
    const IFBU32               file_count       = args->file_count;
    const IFBFileAsyncCallback file_callback    = args->file_read_callback;
    file_table->header.start            = file_table_start;
    file_table->header.size             = commit_size->total;
    file_table->header.file_count       = file_count; 
    file_table->header.file_path_stride = args->file_path_stride;
    file_table->header.callback         = args->file_read_callback;

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
ifb_file_table::args_assert_valid(
    const IFBFileTableArgs* args) {

    ifb_macro_assert(args);
    ifb_macro_assert(args->arena_handle.pointer != NULL);
    ifb_macro_assert(args->file_read_callback   != NULL);
    ifb_macro_assert(args->file_path_buffer     != NULL);
    ifb_macro_assert(args->file_path_stride     != NULL);
    ifb_macro_assert(args->file_count           != NULL);
}

inline IFBFileTableReadOnlyCommitSize*
ifb_file_table::args_read_only_commit_size_reserve(
    const IFBFileTableArgs* args) {

    const IFBU32 size = ifb_macro_align_size_struct(IFBFileTableReadOnlyCommitSize);

    IFBFileTableReadOnlyCommitSize* result = (IFBFileTableReadOnlyCommitSize*)ifb_memory::arena_reserve_bytes_absolute(
        args->arena_handle,
        size);
    
    ifb_macro_assert(result);

    return(result);
}

inline IFBVoid
ifb_file_table::args_read_only_commit_size_release(
    const IFBFileTableArgs* args) {

    const IFBU32 size   = ifb_macro_align_size_struct(IFBFileTableReadOnlyCommitSize);
    const IFBB8  result = ifb_memory::arena_release_bytes(args->arena_handle,size);

    ifb_macro_assert(result);
}

inline IFBVoid
ifb_file_table::args_read_only_commit_size_calculate(
    const IFBFileTableArgs*               args,
    const IFBU32                          context_data_size,
          IFBFileTableReadOnlyCommitSize* commit_size) {

    //all values should be below the max commit size
    const IFBU32 commit_size_max = 0xFFFF;

    //cache constants
    const IFBU32 file_count               = args->file_count;
    const IFBU32 file_path_stride         = args->file_path_stride;
    const IFBU32 file_handle_size         = sizeof(IFBHNDFile);
    const IFBU32 file_array_list_size     = ifb_array_list::memory_allocation_size(file_handle_size,file_count);
    const IFBU32 file_context_size_struct = ifb_macro_align_size_struct(IFBFileContext);

    //property sizes
    const IFBU32 commit_size_file_table              = ifb_macro_align_size_struct(IFBFileReadOnlyTable); 
    const IFBU32 commit_size_file_path_buffer        = file_count * file_path_stride;
    const IFBU32 commit_size_array_file_context      = file_count * file_context_size_struct;
    const IFBU32 commit_size_array_last_bytes_read   = file_count * sizeof(IFBU32);
    const IFBU32 commit_size_array_list_files_open   = file_array_list_size;
    const IFBU32 commit_size_array_list_files_closed = file_array_list_size;
    const IFBU32 commit_size_array_list_files_locked = file_array_list_size;
    const IFBU32 commit_size_context_data            = file_count * context_data_size;

    //make sure the properties are within the expected commit size
    ifb_macro_assert(commit_size_file_table              < commit_size_max);
    ifb_macro_assert(commit_size_file_path_buffer        < commit_size_max);
    ifb_macro_assert(commit_size_array_file_context      < commit_size_max);
    ifb_macro_assert(commit_size_array_last_bytes_read   < commit_size_max);
    ifb_macro_assert(commit_size_array_list_files_open   < commit_size_max);
    ifb_macro_assert(commit_size_array_list_files_closed < commit_size_max);
    ifb_macro_assert(commit_size_array_list_files_locked < commit_size_max);
    ifb_macro_assert(commit_size_context_data            < commit_size_max);

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
    commit_size->total                              = *((IFBU16*)(&commit_size_total));
    commit_size->properties.file_table_size         = *((IFBU16*)(&commit_size_file_table));        
    commit_size->properties.file_path_buffer        = *((IFBU16*)(&commit_size_file_path_buffer));        
    commit_size->properties.array_file_context      = *((IFBU16*)(&commit_size_array_file_context));      
    commit_size->properties.array_last_bytes_read   = *((IFBU16*)(&commit_size_array_last_bytes_read));   
    commit_size->properties.array_list_files_open   = *((IFBU16*)(&commit_size_array_list_files_open));   
    commit_size->properties.array_list_files_closed = *((IFBU16*)(&commit_size_array_list_files_closed)); 
    commit_size->properties.array_list_files_locked = *((IFBU16*)(&commit_size_array_list_files_locked)); 
    commit_size->properties.context_memory_size     = *((IFBU16*)(&commit_size_context_data));

    //make sure we are within expected memory size
    ifb_macro_assert(commit_size_total < commit_size_max);
}