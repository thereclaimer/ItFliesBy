#ifndef IFB_PLATFORM_MONITOR_HPP
#define IFB_PLATFORM_MONITOR_HPP

#include <ifb.hpp>

using namespace ifb;

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

namespace ifb {

   struct platform_monitor_t {
        dimensions_t dimensions;
        position_t   position;
        u32          refresh_hz;
        u32          index;
    };
    
    typedef const u32 (*platform_api_monitor_count_f) (void);
    typedef const b8  (*platform_api_monitor_info_f)  (const u32 monitor_count, platform_monitor_t* monitor_array);
};

#endif //IFB_PLATFORM_MONITOR_HPP