#ifndef IFB_IO_HPP
#define IFB_IO_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>

using namespace ifb;

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb::io {

    //handles
    struct file_table_h      : hnd64 { };  
    struct file_array_list_h : hnd64 { };       
    struct file_h            : hnd16 { };       
};

/**********************************************************************************/
/* FILE TABLE                                                                     */
/**********************************************************************************/

namespace ifb::io {

    struct file_table_args_t {
        memory_t memory;
        u32      file_count;
        u32      file_stride_path;
        u32      file_stride_context;
    };

    const u32          file_table_memory_size       (const u32          file_count);
    const file_table_h file_table_memory_initialize (file_table_args_t& file_table_args);
};

#endif //IFB_IO_HPP