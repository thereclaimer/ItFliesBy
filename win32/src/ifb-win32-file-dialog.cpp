#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void 
ifb_win32::file_dialog_api_initialize(
    IFBEnginePlatformFileDialog platform_api_file_dialog_ref) {

    platform_api_file_dialog_ref.select_file = ifb_win32::file_dialog_select_file;
}

ifb_internal const ifb_b8
ifb_win32::file_dialog_select_file(
    const ifb_cstr  in_starting_directory,
    const ifb_size  in_file_extension_count,
    const ifb_size  in_file_extension_stride,
    const ifb_cstr  in_file_extension_buffer,
    const ifb_size  in_file_selection_buffer_size,
          ifb_cstr out_file_selection_buffer) {

    //sanity check
    if (
        in_starting_directory         != NULL &&
        in_file_extension_count       != 0    &&
        in_file_extension_stride      != 0    &&
        in_file_extension_buffer      != NULL &&
        in_file_selection_buffer_size != 0    &&
        out_file_selection_buffer     != NULL) {

        return(false);
    }

    return(true);
}