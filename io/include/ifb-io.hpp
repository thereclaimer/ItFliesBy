#ifndef IFB_IO_HPP
#define IFB_IO_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* FILE TABLE ARGS                                                                */
/**********************************************************************************/

namespace ifb_file_table {

    //read only
    const IFBHNDFileTable commit_read_only(const IFBFileTableArgs* args); 
};

/**********************************************************************************/
/* FILE TABLE READ ONLY                                                           */
/**********************************************************************************/

namespace ifb_file_ro {

    const IFBB8 file_open           (const IFBFileReadOnlyRequest* request);
    const IFBB8 file_close          (const IFBFileReadOnlyRequest* request);
    const IFBB8 file_read_immediate (const IFBFileReadOnlyRequest* request);
    const IFBB8 file_read_async     (const IFBFileReadOnlyRequest* request);
};

#endif //IFB_IO_HPP