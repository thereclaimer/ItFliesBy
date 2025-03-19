#pragma once

#include "ifb-io.hpp"

#include "ifb-io-file-table-initialization.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_file_table {

    IFBChar*        read_only_load_file_path_buffer        (const IFBFileTableReadOnly* table);
    IFBFileContext* read_only_load_array_file_context      (const IFBFileTableReadOnly* table);
    IFBU32*         read_only_load_array_last_bytes_read   (const IFBFileTableReadOnly* table);
    IFBArrayList*   read_only_load_array_list_files_open   (const IFBFileTableReadOnly* table);
    IFBArrayList*   read_only_load_array_list_files_closed (const IFBFileTableReadOnly* table);
    IFBArrayList*   read_only_load_array_list_files_locked (const IFBFileTableReadOnly* table);
    IFBPtr          read_only_load_context_data            (const IFBFileTableReadOnly* table);
};

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
    ifb_file_table::read_only_init_step_0_validate_args         (init);
    ifb_file_table::read_only_init_step_1_reserve_size_cache    (init);
    ifb_file_table::read_only_init_step_2_commit_table          (init);
    ifb_file_table::read_only_init_step_3_set_table_header      (init);
    ifb_file_table::read_only_init_step_4_set_table_handles     (init);
    ifb_file_table::read_only_init_step_5_set_table_lists       (init);
    ifb_file_table::read_only_init_step_6_set_table_contexts    (init);
    ifb_file_table::read_only_init_step_7_set_table_path_buffer (init);
    ifb_file_table::read_only_init_step_8_release_size_cache    (init);

    //we're done
    return(init.handle);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBChar*
ifb_file_table::read_only_load_file_path_buffer(
    const IFBFileTableReadOnly* table) {

    const IFBU32  offset      = table->handles.file_path_buffer.offset;
    const IFBAddr start       = table->header.memory.start;
    const IFBAddr result_addr = offset + start;

    IFBChar* result_ptr = (IFBChar*)result_addr;
    return(result_ptr);  
}

inline IFBFileContext*
ifb_file_table::read_only_load_array_file_context(
    const IFBFileTableReadOnly* table) {

    const IFBU32  offset      = table->handles.array_file_context.offset;
    const IFBAddr start       = table->header.memory.start;
    const IFBAddr result_addr = offset + start;

    IFBFileContext* result_ptr = (IFBFileContext*)result_addr;
    return(result_ptr);  
}

inline IFBU32*
ifb_file_table::read_only_load_array_last_bytes_read(
    const IFBFileTableReadOnly* table) {

    const IFBU32  offset      = table->handles.array_last_bytes_read.offset;
    const IFBAddr start       = table->header.memory.start;
    const IFBAddr result_addr = offset + start;

    IFBU32* result_ptr = (IFBU32*)result_addr;
    return(result_ptr);  
}

inline IFBArrayList*
ifb_file_table::read_only_load_array_list_files_open(
    const IFBFileTableReadOnly* table) {

    const IFBU32  offset      = table->handles.array_list_files_open.offset;
    const IFBAddr start       = table->header.memory.start;
    const IFBAddr result_addr = offset + start;

    IFBArrayList* result_ptr = (IFBArrayList*)result_addr;
    return(result_ptr);  
}

inline IFBArrayList*
ifb_file_table::read_only_load_array_list_files_closed(
    const IFBFileTableReadOnly* table) {

    const IFBU32  offset      = table->handles.array_list_files_closed.offset;
    const IFBAddr start       = table->header.memory.start;
    const IFBAddr result_addr = offset + start;

    IFBArrayList* result_ptr = (IFBArrayList*)result_addr;
    return(result_ptr);  
}

inline IFBArrayList*
ifb_file_table::read_only_load_array_list_files_locked(
    const IFBFileTableReadOnly* table) {

    const IFBU32  offset      = table->handles.array_list_files_locked.offset;
    const IFBAddr start       = table->header.memory.start;
    const IFBAddr result_addr = offset + start;

    IFBArrayList* result_ptr = (IFBArrayList*)result_addr;
    return(result_ptr);  
}

inline IFBPtr
ifb_file_table::read_only_load_context_data(
    const IFBFileTableReadOnly* table) {

    const IFBU32  offset      = table->handles.context_data.offset;
    const IFBAddr start       = table->header.memory.start;
    const IFBAddr result_addr = offset + start;

    IFBPtr* result_ptr = (IFBPtr*)result_addr;
    return(result_ptr);  
}