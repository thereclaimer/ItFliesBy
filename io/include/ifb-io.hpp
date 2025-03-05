#ifndef IFB_IO_HPP
#define IFB_IO_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>

/**********************************************************************************/
/* FILE - READ ONLY                                                               */
/**********************************************************************************/

namespace ifb_file_ro {

    //memory
    IFBFileReadOnly* arena_load_pointer    (const IFBHNDArena arena_handle, const IFBU32 arena_offset);
    IFBFileReadOnly* arena_commit_absolute (const IFBHNDArena arena_handle, const IFBU32 platform_stack_size);
    const IFBU32     arena_commit_relative (const IFBHNDArena arena_handle, const IFBU32 platform_stack_size);

    //open/close    
    const IFBB8 open           (IFBFileReadOnly* file_read_only, const IFBChar* file_path_cstr);
    const IFBB8 close          (IFBFileReadOnly* file_read_only);
    
    //read
    const IFBB8 read_immediate (IFBFileReadOnly* file_read_only, const IFBHNDArena arena_handle, IFBU32& arena_offset, const IFBU32 read_size, const IFBU32 read_offset = 0);
    const IFBB8 read_async     (IFBFileReadOnly* file_read_only, const IFBHNDArena arena_handle, IFBU32& arena_offset, const IFBU32 read_size, const IFBU32 read_offset = 0);
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