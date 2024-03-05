#ifndef IFB_PLATFORM_API_HPP
#define IFB_PLATFORM_API_HPP

#include "ifb-types.hpp"

typedef handle 
(*func_ifb_platform_memory_allocate)
(
    u64 size
);

typedef void 
(*func_ifb_platform_memory_free)
(
    handle, 
    u64
);

typedef  u64 
(*func_ifb_platform_file_size_get)
(
    handle file_path
);

typedef void 
(*func_ifb_platform_file_read_and_null_terminate)
(
    str    file_path,
    u64    allocated_buffer_size,
    memory allocated_buffer,
    b8     create_if_not_exists
);

typedef void 
(*func_ifb_platform_file_write)
(
    str     file_path,
    u64     allocated_buffer_size,
    memory  allocated_buffer,
    b8      create_if_not_exists
);

typedef handle
(*func_ifb_platform_file_open)
(
    str file_path
);

typedef void
(*func_ifb_platform_file_close)
(
    handle file_handle
);

typedef void
(*func_ifb_platform_file_write_handle)
(
    handle  file_handle,
    u64    allocated_buffer_size,
    memory allocated_buffer
);

typedef void
(*func_ifb_platform_file_read_handle)
(
    handle  file_handle,
    u64    allocated_buffer_size,
    memory allocated_buffer
);

typedef void
(*func_ifb_platform_file_seek_handle)
(
    handle file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer
);

typedef handle
(*func_ifb_platform_initialize_graphics_api)
(
    handle window
);

#define RECLAIMER_PLATFORM_API_NAME "ReclaimerPlatformApi"

struct ReclaimerPlatformApi  {

    //Use this as a pointer to whatever window data the platform is
    //using. This will need to be passed back to the platform when
    //initializing whatever graphics api the renderer uses 
    mem_data                                             window;
    
    //platform fuctions
    func_ifb_platform_file_size_get                file_size_get;
    func_ifb_platform_file_read_and_null_terminate file_read_and_null_terminate;
    func_ifb_platform_file_read_handle             file_read_handle;
    func_ifb_platform_file_write                   file_write;
    func_ifb_platform_file_write_handle            file_write_handle;
    func_ifb_platform_file_open                    file_open;
    func_ifb_platform_file_close                   file_close;
    func_ifb_platform_file_seek_handle             file_seek_handle;
    func_ifb_platform_memory_allocate              memory_allocate;
    func_ifb_platform_memory_free                  memory_free;
    func_ifb_platform_initialize_graphics_api      graphics_api_init;
};


#endif //IFB_PLATFORM_API_HPP