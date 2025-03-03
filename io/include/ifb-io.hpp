#ifndef IFB_IO_HPP
#define IFB_IO_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBHNDPlatformIO : IFBHNDPTR { }

struct IFBFileReadOnly;
struct IFBFileReadWrite;

/**********************************************************************************/
/* FILE                                                                           */
/**********************************************************************************/

struct IFBFileReadOnly {
    IFBHNDPlatformIO platform_handle;
    IFBU32           size;
    IFBU32           bytes_read;
};

struct IFBFileReadWrite {
    IFBHNDPlatformIO platform_handle;
    IFBU32           size;
    IFBU32           bytes_read;
    IFBU32           bytes_written;
};

namespace ifb_file {

    //read only
    const IFBB8 open  (IFBFileReadOnly* file_read_only, const IFBChar*    file_path_cstr);
    const IFBB8 read  (IFBFileReadOnly* file_read_only, const IFBHNDArena arena_handle, const IFBU32 offset = 0);
    const IFBB8 close (IFBFileReadOnly* file_read_only, const IFBHNDArena arena_handle, const IFBU32 offset = 0);

    //read write
    const IFBB8 open  (IFBFileReadWrite* file_read_only, const IFBChar*    file_path_cstr);
    const IFBB8 read  (IFBFileReadWrite* file_read_only, const IFBHNDArena arena_handle, const IFBU32 offset = 0);
    const IFBB8 write (IFBFileReadWrite* file_read_only, const IFBHNDArena arena_handle, const IFBU32 offset = 0);
    const IFBB8 close (IFBFileReadWrite* file_read_only, const IFBHNDArena arena_handle, const IFBU32 offset = 0);
};

#endif //IFB_IO_HPP