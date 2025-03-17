#ifndef IFB_IO_HPP
#define IFB_IO_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>

/**********************************************************************************/
/* FILE - READ ONLY                                                               */
/**********************************************************************************/

struct IFBFileTableArgs {
    IFBHNDArena arena_handle;
    IFBChar*    file_path_buffer;
    IFBU32      file_path_stride; 
    IFBU32      file_count;
};

struct IFBFileTableReadOnlyRequest {
    IFBFileReadOnlyTable*   file_table;
    IFBFileReadOnlyRequest* file_request;
};

namespace ifb_file_table_ro {

    IFBFileReadOnlyTable*        commit_table    (IFBFileTableArgs* args);
    IFBFileTableReadOnlyRequest* reserve_request (const IFBHNDArena arena_handle, const IFBU32 file_count);
    IFBFileTableReadOnlyRequest* release_request (const IFBHNDArena arena_handle, IFBFileTableReadOnlyRequest* file_table_request);

    const IFBB8 file_open           (IFBFileTableReadOnlyRequest* file_table_request);
    const IFBB8 file_close          (IFBFileTableReadOnlyRequest* file_table_request);
    const IFBB8 file_read_immediate (IFBFileTableReadOnlyRequest* file_table_request);
    const IFBB8 file_read_async     (IFBFileTableReadOnlyRequest* file_table_request);

};

/**********************************************************************************/
/* FILE - READ WRITE                                                              */
/**********************************************************************************/

namespace ifb_file_rw {

    //memory
    IFBFileReadWrite* arena_load_pointer    (const IFBHNDArena arena_handle, const IFBU32 arena_offset);
    IFBFileReadWrite* arena_commit_absolute (const IFBHNDArena arena_handle, const IFBU32 platform_stack_size);
    const IFBU32      arena_commit_relative (const IFBHNDArena arena_handle, const IFBU32 platform_stack_size);

    //open/close
    const IFBB8 open            (IFBFileReadWrite* file_read_write, const IFBChar* file_path_cstr);
    const IFBB8 close           (IFBFileReadWrite* file_read_write);

    //read
    const IFBB8 read_immediate  (IFBFileReadWrite* file_read_write, const IFBHNDArena arena_handle, const IFBU32& arena_offset, const IFBU32 read_size,  const IFBU32 read_offset  = 0);
    const IFBB8 read_async      (IFBFileReadWrite* file_read_write, const IFBHNDArena arena_handle, const IFBU32& arena_offset, const IFBU32 read_size,  const IFBU32 read_offset  = 0);

    //write
    const IFBB8 write_immediate (IFBFileReadWrite* file_read_write, const IFBHNDArena arena_handle, const IFBU32  arena_offset, const IFBU32 write_size, const IFBU32 write_offset = 0);
    const IFBB8 write_async     (IFBFileReadWrite* file_read_write, const IFBHNDArena arena_handle, const IFBU32  arena_offset, const IFBU32 write_size, const IFBU32 write_offset = 0);
};

#endif //IFB_IO_HPP