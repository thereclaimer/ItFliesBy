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
    IFBFileTableArgs*              args;
    IFBFileTableReadOnlySizeCache* sizes;
    IFBFileTableReadOnly*          table;
    IFBHNDFileTable                handle;
};

namespace ifb_file_table {
    
    IFBVoid read_only_init_step_0_validate_args         (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_1_reserve_size_cache    (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_2_commit_table          (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_3_set_table_header      (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_4_set_table_handles     (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_5_set_table_lists       (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_6_set_table_contexts    (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_7_set_table_path_buffer (IFBFileTableReadOnlyInit& init_ref);
    IFBVoid read_only_init_step_8_release_size_cache    (IFBFileTableReadOnlyInit& init_ref);
};

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBVoid
ifb_file_table::read_only_init_step_0_validate_args(
    IFBFileTableReadOnlyInit& init_ref) {

    ifb_macro_assert(init_ref.args);
    ifb_macro_assert(init_ref.args->arena              != NULL);
    ifb_macro_assert(init_ref.args->file_callback_read != NULL);
    ifb_macro_assert(init_ref.args->file_path_buffer   != NULL);
    ifb_macro_assert(init_ref.args->file_path_stride   != NULL);
    ifb_macro_assert(init_ref.args->file_count         != NULL);
}

inline IFBVoid
ifb_file_table::read_only_init_step_1_reserve_size_cache(
    IFBFileTableReadOnlyInit& init_ref) {

    //calculate the struct size
    const IFBU32 size = ifb_macro_align_size_struct(IFBFileTableReadOnlySizeCache);

    //commit the struct
    IFBFileTableReadOnlySizeCache* table_sizes = (IFBFileTableReadOnlySizeCache*)ifb_memory::arena_reserve_bytes_absolute(
        init_ref.args->arena,
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
    const IFBU32 commit_size_file_table              = ifb_macro_align_size_struct(IFBFileTableReadOnly); 
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
ifb_file_table::read_only_init_step_2_commit_table(
    IFBFileTableReadOnlyInit& init_ref) {

    //do the commit
    IFBMemoryArena* file_table_arena      = init_ref.args->arena; 
    const IFBU32    file_table_size_total = init_ref.sizes->commit.total; 
    const IFBU32    file_table_offset     = ifb_memory::arena_commit_bytes_relative(
        file_table_arena,
        file_table_size_total);

    //load the pointer
    IFBFileTableReadOnly* file_table = (IFBFileTableReadOnly*)ifb_memory::arena_get_pointer(
        file_table_arena,
        file_table_offset);

    //make sure its valid
    ifb_macro_assert(file_table);

    //update the init struct
    init_ref.table         = file_table;
    init_ref.handle.offset = file_table_offset;
}

inline IFBVoid
ifb_file_table::read_only_init_step_3_set_table_header(
    IFBFileTableReadOnlyInit& init_ref) {

    //get the table
    IFBFileTableReadOnly* file_table = init_ref.table;

    //set header properties
    file_table->header.memory.start     = (IFBAddr)init_ref.table;
    file_table->header.memory.size      = init_ref.sizes->commit.total;
    file_table->header.file_count       = init_ref.args->file_count; 
    file_table->header.file_path_stride = init_ref.args->file_path_stride;
    file_table->header.callback         = init_ref.args->file_callback_read; 
}

inline IFBVoid
ifb_file_table::read_only_init_step_4_set_table_handles(
    IFBFileTableReadOnlyInit& init_ref) {

    //calculate the offsets
    const IFBU16 offset_file_path_buffer        = init_ref.sizes->commit.file_table_size;
    const IFBU16 offset_array_file_context      = init_ref.sizes->commit.file_path_buffer        + offset_file_path_buffer;
    const IFBU16 offset_array_last_bytes_read   = init_ref.sizes->commit.array_file_context      + offset_array_file_context;
    const IFBU16 offset_array_list_files_open   = init_ref.sizes->commit.array_last_bytes_read   + offset_array_last_bytes_read;
    const IFBU16 offset_array_list_files_closed = init_ref.sizes->commit.array_list_files_open   + offset_array_list_files_open;
    const IFBU16 offset_array_list_files_locked = init_ref.sizes->commit.array_list_files_closed + offset_array_list_files_closed;
    const IFBU16 offset_context_data            = init_ref.sizes->commit.array_list_files_locked + offset_array_list_files_locked;

    //set handles
    init_ref.table->handles.file_path_buffer.offset        = offset_file_path_buffer;
    init_ref.table->handles.array_file_context.offset      = offset_array_file_context;
    init_ref.table->handles.array_last_bytes_read.offset   = offset_array_last_bytes_read;
    init_ref.table->handles.array_list_files_open.offset   = offset_array_list_files_open;
    init_ref.table->handles.array_list_files_closed.offset = offset_array_list_files_closed;
    init_ref.table->handles.array_list_files_locked.offset = offset_array_list_files_locked;
    init_ref.table->handles.context_data.offset            = offset_context_data;
}

inline IFBVoid
ifb_file_table::read_only_init_step_5_set_table_lists(
    IFBFileTableReadOnlyInit& init_ref) {
    
    //cache memory and offsets
    const IFBAddr memory_start       = init_ref.table->header.memory.start;
    const IFBU32  offset_list_open   = init_ref.table->handles.array_list_files_open.offset;
    const IFBU32  offset_list_closed = init_ref.table->handles.array_list_files_closed.offset;
    const IFBU32  offset_list_locked = init_ref.table->handles.array_list_files_locked.offset;

    //calculate addresses
    const IFBAddr addr_list_file_open   = memory_start + offset_list_open;
    const IFBAddr addr_list_file_closed = memory_start + offset_list_closed;
    const IFBAddr addr_list_file_locked = memory_start + offset_list_locked;
    
    const IFBPtr memory_list_file_open   = (IFBPtr)addr_list_file_open; 
    const IFBPtr memory_list_file_closed = (IFBPtr)addr_list_file_closed; 
    const IFBPtr memory_list_file_locked = (IFBPtr)addr_list_file_locked; 

    const IFBU32 file_handle_size  = init_ref.sizes->tmp_cache.file_handle;
    const IFBU32 file_handle_count = init_ref.args->file_count;

    //initialize the lists
    IFBArrayList* list_file_open   = ifb_array_list::memory_initialize(file_handle_size, file_handle_count, memory_list_file_open);
    IFBArrayList* list_file_closed = ifb_array_list::memory_initialize(file_handle_size, file_handle_count, memory_list_file_closed);
    IFBArrayList* list_file_locked = ifb_array_list::memory_initialize(file_handle_size, file_handle_count, memory_list_file_locked);

    //assert the lists are valid
    ifb_macro_assert(list_file_open);
    ifb_macro_assert(list_file_closed);
    ifb_macro_assert(list_file_locked);

    //add the indexes to the closed list
    for (
        IFBU32 file_index = 0;
               file_index < file_handle_count;
             ++file_index) {

        //add the index
        const IFBB8 result = ifb_array_list::add_to_end(list_file_open,(IFBPtr)&file_index);
        ifb_macro_assert(result);
    }
}

inline IFBVoid 
ifb_file_table::read_only_init_step_6_set_table_contexts(
    IFBFileTableReadOnlyInit& init_ref) {

    //cache constants
    const IFBU32               file_count                     = init_ref.args->file_count;
    const IFBU32               file_context_data_size         = init_ref.sizes->tmp_cache.context_data; 
    const IFBU32               offset_file_context_array      = init_ref.table->handles.array_file_context.offset;
    const IFBU32               offset_file_context_data_start = init_ref.table->handles.context_data.offset;
    const IFBAddr              file_table_memory              = init_ref.table->header.memory.start;
    const IFBFileAsyncCallback file_async_callback            = init_ref.table->header.callback;

    //get the file context array    
    const IFBAddr   file_context_array_addr = file_table_memory + offset_file_context_array;
    IFBFileContext* file_context_array_ptr  = (IFBFileContext*)file_context_array_addr;
    ifb_macro_assert(file_context_array_ptr);

    //initialize the contexts
    for (
        IFBU32 file_context_index = 0;
               file_context_index < file_count;
             ++file_context_index) {

        //get the current context struct and data offset
        const IFBU32    current_file_data_offset    = offset_file_context_data_start + (file_context_data_size * file_context_index);
        IFBFileContext& current_file_context_struct = file_context_array_ptr[file_context_index];

        //initialize the context
        current_file_context_struct.platform_memory.start = file_table_memory;
        current_file_context_struct.platform_memory.size  = file_context_data_size;
        current_file_context_struct.callbacks.read        = file_async_callback;
        current_file_context_struct.callbacks.write       = NULL;
        current_file_context_struct.bytes_transferred     = 0;
    }
}

inline IFBVoid
ifb_file_table::read_only_init_step_7_set_table_path_buffer(
    IFBFileTableReadOnlyInit& init_ref) {

    //calculate sizes and addresses
    const IFBU32   file_count                    = init_ref.args->file_count;
    const IFBU32   file_path_stride              = init_ref.args->file_path_stride;
    const IFBU32   file_path_buffer_size         = file_count * file_path_stride;
    const IFBAddr  file_table_start              = init_ref.table->header.memory.start;
    const IFBU32   file_table_path_buffer_offset = init_ref.table->handles.file_path_buffer.offset;
    const IFBAddr  file_table_path_buffer_start  = file_table_start + file_table_path_buffer_offset;
    
    //source and destination buffers
    const IFBChar* file_path_buffer_source      = init_ref.args->file_path_buffer;
    IFBChar*       file_path_buffer_destination = (IFBChar*)file_table_path_buffer_start; 

    //copy the buffer
    for (
        IFBU32 char_index = 0;
               char_index < file_path_buffer_size;
             ++char_index) {

        file_path_buffer_destination[char_index] = file_path_buffer_source[char_index];
    }
}


inline IFBVoid
ifb_file_table::read_only_init_step_8_release_size_cache(
    IFBFileTableReadOnlyInit& init_ref) {

    const IFBU32 size   = init_ref.sizes->tmp_cache.sizes_struct; 
    const IFBB8  result = ifb_memory::arena_release_bytes(init_ref.args->arena,size);
    ifb_macro_assert(result);
}