#ifndef IFB_IO_HPP
#define IFB_IO_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//handles
struct IFBIO64FileTable     : IFBHND64 { };  
struct IFBIO64FileArrayList : IFBHND64 { };       
struct IFBIO16File          : IFBHND16 { };       

//callbacks
// typedef IFBU32 (*IFBFileAsyncCallback) (IFBFileContext* file_context);
// struct  IFBFileAsyncCallbacks;

/**********************************************************************************/
/* FILE TABLE                                                                     */
/**********************************************************************************/

struct IFBFileTableArgs {
    IFBMemory memory;
    IFBU32    file_count;
    IFBU32    file_stride_path;
    IFBU32    file_stride_context;
};

namespace ifb_io { 

    const IFBU32           file_table_memory_size       (const IFBU32      file_count);
    const IFBIO64FileTable file_table_memory_initialize (IFBFileTableArgs& file_table_args);
};


#endif //IFB_IO_HPP