#ifndef IFB_PLATFORM_MONITOR_HPP
#define IFB_PLATFORM_MONITOR_HPP

#include <ifb.hpp>

using namespace ifb;

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

namespace ifb::platform {

    struct monitor_t;

    typedef const u32 (*api_monitor_count_f) (void);
    typedef const b8  (*api_monitor_info_f)  (const u32 monitor_count, monitor_t* monitor_array);
};

#endif //IFB_PLATFORM_MONITOR_HPP