#pragma once

#include "ifb-win32.hpp"

ifb_internal IFBVoid 
ifb_win32::file_dialog_api_initialize(
    IFBEnginePlatformFileDialog& platform_api_file_dialog_ref) {

    platform_api_file_dialog_ref.select_file = ifb_win32::file_dialog_select_file;
}

ifb_internal const IFBB8
ifb_win32::file_dialog_select_file(
    const IFBCStr  in_file_dialog_starting_directory,
    const IFBSize  in_file_type_count,
    const IFBCStr* in_file_type_name_cstr_ptr,
    const IFBCStr* in_file_type_spec_cstr_ptr,
          IFBCStr out_file_selection_buffer) {

    //sanity check
    if (
        in_file_dialog_starting_directory == NULL ||
        in_file_type_count                == 0    ||
        in_file_type_name_cstr_ptr        == NULL ||
        in_file_type_spec_cstr_ptr        == NULL ||
        out_file_selection_buffer         == NULL) {

        return(false);
    }

    //get a temporary arena
    IFBEngineMemoryArenaHandle tmp_arena_handle;
    if (!ifb_engine::memory_arena_commit(
        _ifb_win32.memory.arena_pool,
        tmp_arena_handle)) {

        return(false);
    }

    //allocate the wide string arrays 
    IFBWStr* file_type_name_wstr_ptr = ifb_engine_memory_arena_push_array_immediate(tmp_arena_handle,in_file_type_count,IFBWStr);
    IFBWStr* file_type_spec_wstr_ptr = ifb_engine_memory_arena_push_array_immediate(tmp_arena_handle,in_file_type_count,IFBWStr);

    //cache the size of a wchar
    const IFBSize w_char_size = sizeof(IFBWChar);

    //convert cstr to wstr
    for (
        IFBIndex file_type_index = 0;
        file_type_index < in_file_type_count;
        ++file_type_index) {

        //cache the current c-strings
        const IFBCStr file_type_name_cstr = in_file_type_name_cstr_ptr[file_type_index];
        const IFBCStr file_type_spec_cstr = in_file_type_spec_cstr_ptr[file_type_index];

        //get the c-string lengths, including the null terminator
        const IFBSize file_type_name_cstr_length = strnlen_s(file_type_name_cstr, IFB_WIN32_DIALOG_CSTR_LENGTH_MAX) + 1;
        const IFBSize file_type_spec_cstr_length = strnlen_s(file_type_spec_cstr, IFB_WIN32_DIALOG_CSTR_LENGTH_MAX) + 1;

        //determine the byte length of the equivalient w-string
        //wstr_byte_len = w_char_size * cstr_len
        const IFBSize file_type_name_wstr_length_bytes = w_char_size * file_type_name_cstr_length; 
        const IFBSize file_type_spec_wstr_length_bytes = w_char_size * file_type_spec_cstr_length; 
    
        //get the memory for the w-strings
        const IFBWStr file_type_name_wstr = ifb_engine_memory_arena_push_array_immediate(tmp_arena_handle, file_type_name_wstr_length_bytes, IFBWChar);
        const IFBWStr file_type_spec_wstr = ifb_engine_memory_arena_push_array_immediate(tmp_arena_handle, file_type_spec_wstr_length_bytes, IFBWChar);
    
        //clear the memory
        memset(file_type_name_wstr,0,file_type_name_wstr_length_bytes);        
        memset(file_type_spec_wstr,0,file_type_spec_wstr_length_bytes);

        //convert the c-strings to w-strings
        //we pass in the cstr_length twice, because that is the number of characters
        MultiByteToWideChar(CP_UTF8, 0, file_type_name_cstr, file_type_name_cstr_length, file_type_name_wstr, file_type_name_cstr_length);
        MultiByteToWideChar(CP_UTF8, 0, file_type_spec_cstr, file_type_spec_cstr_length, file_type_spec_wstr, file_type_spec_cstr_length);

        //update the wstr array
        file_type_name_wstr_ptr[file_type_index] = file_type_name_wstr; 
        file_type_spec_wstr_ptr[file_type_index] = file_type_spec_wstr; 
    }

    //now, we can open the dialog
    IFBB8 result = r_win32::file_dialog_select_file(
        _ifb_win32.file_dialog_handle,
        in_file_dialog_starting_directory,
        in_file_type_count,
        file_type_name_wstr_ptr,
        file_type_spec_wstr_ptr);

    //return the arena
    result &= ifb_engine::memory_arena_decommit(tmp_arena_handle);

    //we're done
    return(result);
}