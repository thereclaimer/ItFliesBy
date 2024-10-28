#ifndef IFB_ENGINE_PLATFORM_HPP
#define IFB_ENGINE_PLATFORM_HPP

#include <r-libs.hpp>
#include "ifb-engine-types.hpp"


/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/



/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef const ifb_memory
(*funcptr_ifb_engine_platform_memory_pages_reserve)(
    const ifb_size size);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_memory_pages_release)(
    const ifb_memory reservation);

typedef const ifb_memory
(*funcptr_ifb_engine_platform_memory_pages_commit)(
    const ifb_memory commit_start,
    const ifb_size   commit_size);

typedef const ifb_memory
(*funcptr_ifb_engine_platform_memory_pages_decommit)(
    const ifb_memory commit_start,
    const ifb_size   commit_size);

struct IFBEnginePlatformMemory {
    funcptr_ifb_engine_platform_memory_pages_reserve  pages_reserve;
    funcptr_ifb_engine_platform_memory_pages_release  pages_release;
    funcptr_ifb_engine_platform_memory_pages_commit   pages_commit;
    funcptr_ifb_engine_platform_memory_pages_decommit pages_decommit;
};

/**********************************************************************************/
/* FILES                                                                          */
/**********************************************************************************/

typedef ifb_index IFBEnginePlatformFileIndex;

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_open_read_only) (
    const ifb_cstr                     in_file_path,
          IFBEnginePlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_open_read_write) (
    const ifb_cstr                     in_file_path,
          IFBEnginePlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_open_read_write) (
    const ifb_cstr                     in_file_path,
          IFBEnginePlatformFileIndex& out_file_index_ref);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_close) (
    const IFBEnginePlatformFileIndex file_index);

typedef const ifb_size
(*funcptr_ifb_engine_platform_file_size) (
    const IFBEnginePlatformFileIndex file_index);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_read)(
    const IFBEnginePlatformFileIndex in_file_index,
    const ifb_size                   in_file_read_start,
    const ifb_size                   in_file_read_size,
          ifb_memory                out_file_read_buffer);

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_write)(
    const IFBEnginePlatformFileIndex in_file_index,
    const ifb_size                   in_file_write_start,
    const ifb_size                   in_file_write_size,
          ifb_memory                 in_file_write_buffer);

struct IFBEnginePlatformFile {
    funcptr_ifb_engine_platform_file_open_read_only  open_read_only;
    funcptr_ifb_engine_platform_file_open_read_write open_read_write;
    funcptr_ifb_engine_platform_file_close           close;
    funcptr_ifb_engine_platform_file_size            size;
    funcptr_ifb_engine_platform_file_read            read;
    funcptr_ifb_engine_platform_file_write           write;
};

/**********************************************************************************/
/* FILE DIALOG                                                                    */
/**********************************************************************************/

typedef const ifb_b8
(*funcptr_ifb_engine_platform_file_dialog_select_file) (
    const ifb_cstr  in_file_dialog_starting_directory,
    const ifb_size  in_file_type_count,
    const ifb_cstr* in_file_type_name_cstr_ptr,
    const ifb_cstr* in_file_type_spec_cstr_ptr,
          ifb_cstr out_file_selection_buffer);

struct IFBEnginePlatformFileDialog {
    funcptr_ifb_engine_platform_file_dialog_select_file select_file;
};

/**********************************************************************************/
/* PLATFORM API                                                                   */
/**********************************************************************************/

struct IFBEnginePlatformApi {
    IFBEnginePlatformMemory     memory;
    IFBEnginePlatformFile       file;
    IFBEnginePlatformFileDialog file_dialog;
};

#endif //IFB_ENGINE_PLATFORM_HPP