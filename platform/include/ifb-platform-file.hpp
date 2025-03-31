#ifndef IFB_PLATFORM_FILE_HPP
#define IFB_PLATFORM_FILE_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FILES                                                                          */                            
/**********************************************************************************/

namespace ifb::platform {

    struct file_request_t {
        ptr x; //TEMPORARY
    };

    typedef const u32 (*file_ro_context_size_f)    (void);
    typedef const b8  (*file_ro_open_f)            (file_request_t* file_ro_request);
    typedef const b8  (*file_ro_read_immediate_f)  (file_request_t* file_ro_request);
    typedef const b8  (*file_ro_read_async_f)      (file_request_t* file_ro_request);
    typedef const b8  (*file_ro_close_f)           (file_request_t* file_ro_request);

    typedef const u32 (*file_rw_context_size_f)    (void);
    typedef const b8  (*file_rw_open_f)            (file_request_t* file_rw_request);
    typedef const b8  (*file_rw_read_immediate_f)  (file_request_t* file_rw_request);
    typedef const b8  (*file_rw_read_async_f)      (file_request_t* file_rw_request);
    typedef const b8  (*file_rw_write_immediate_f) (file_request_t* file_rw_request);
    typedef const b8  (*file_rw_write_async_f)     (file_request_t* file_rw_request);
    typedef const b8  (*file_rw_close_f)           (file_request_t* file_rw_request);

};
#endif //IFB_PLATFORM_FILE_HPP