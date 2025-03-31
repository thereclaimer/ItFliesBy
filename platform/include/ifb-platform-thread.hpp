#ifndef IFB_PLATFORM_THREAD_HPP
#define IFB_PLATFORM_THREAD_HPP

#include <ifb.hpp>

using namespace ifb;

/**********************************************************************************/
/* THREAD API                                                                     */
/**********************************************************************************/

namespace ifb::platform {

    struct thread_request_t;

    typedef const u32 (*api_thread_size_f)         (void);
    typedef const b8  (*api_thread_create_f)       (const thread_request_t* request);
    typedef const b8  (*api_thread_destroy_f)      (const thread_request_t* request);
    typedef const b8  (*api_thread_assign_cores_f) (const thread_request_t* request);
    typedef const b8  (*api_thread_wake_f)         (const thread_request_t* request);
    typedef const b8  (*api_thread_sleep_f)        (const thread_request_t* request);
};

#endif //IFB_PLATFORM_THREAD_HPP