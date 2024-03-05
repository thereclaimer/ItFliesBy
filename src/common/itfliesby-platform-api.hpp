#ifndef ITFLIESBY_PLATFORM_API_HPP
#define ITFLIESBY_PLATFORM_API_HPP

#include "itfliesby-types.hpp"

typedef handle 
(*func_itfliesby_platform_memory_allocate)
(
    u64 size
);

typedef void 
(*func_itfliesby_platform_memory_free)
(
    handle, 
    u64
);

typedef  u64 
(*func_itfliesby_platform_file_size_get)
(
    handle file_path
);

typedef handle
(*func_itfliesby_platform_file_open)
(
    str file_path,
    b8  create_new
);

typedef void
(*func_itfliesby_platform_file_close)
(
    handle file_handle
);

typedef void
(*func_itfliesby_platform_file_write)
(
    handle file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer
);

typedef void
(*func_itfliesby_platform_file_read)
(
    handle file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer
);

typedef handle
(*func_itfliesby_platform_initialize_graphics_api)
(
    handle window
);

#define RECLAIMER_PLATFORM_API_NAME "ReclaimerPlatformApi"

struct ReclaimerPlatformApi  {

    //Use this as a pointer to whatever window data the platform is
    //using. This will need to be passed back to the platform when
    //initializing whatever graphics api the renderer uses 
    handle                                          window;
    
    //platform fuctions
    func_itfliesby_platform_file_size_get           file_size_get;
    func_itfliesby_platform_file_write              file_write;
    func_itfliesby_platform_file_open               file_open;
    func_itfliesby_platform_file_close              file_close;
    func_itfliesby_platform_memory_allocate         memory_allocate;
    func_itfliesby_platform_memory_free             memory_free;
    func_itfliesby_platform_initialize_graphics_api graphics_api_init;
};

#endif //ITFLIESBY_PLATFORM_API_HPP