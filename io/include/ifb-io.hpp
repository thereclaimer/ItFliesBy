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

namespace ifb_file_ro {

    const IFBHNDFileTable file_table_commit   (const IFBFileTableArgs*       args);
    const IFBB8           file_open           (const IFBFileReadOnlyRequest* request);
    const IFBB8           file_close          (const IFBFileReadOnlyRequest* request);
    const IFBB8           file_read_immediate (const IFBFileReadOnlyRequest* request);
    const IFBB8           file_read_async     (const IFBFileReadOnlyRequest* request);
};

#endif //IFB_IO_HPP