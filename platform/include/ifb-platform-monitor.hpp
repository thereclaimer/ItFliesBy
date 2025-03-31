#ifndef IFB_PLATFORM_MONITOR_HPP
#define IFB_PLATFORM_MONITOR_HPP

#include <ifb.hpp>

using namespace ifb;

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

namespace ifb::platform {

   struct monitor_t {
        dimensions_t dimensions;
        position_t   position;
        u32          refresh_hz;
        u32          index;
    };
    
    typedef const u32 (*api_monitor_count_f) (void);
    typedef const b8  (*api_monitor_info_f)  (const u32 monitor_count, monitor_t* monitor_array);
};

#endif //IFB_PLATFORM_MONITOR_HPP