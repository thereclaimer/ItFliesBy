#ifndef IFB_PLATFORM_MONITOR_HPP
#define IFB_PLATFORM_MONITOR_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

struct IFBMonitor;

typedef const ifb::u32 (*IFBPlatformMonitorCount) (void);
typedef const ifb::b8  (*IFBPlatformMonitorInfo)  (const ifb::u32 monitor_count, IFBMonitor* monitor_array);

#endif //IFB_PLATFORM_MONITOR_HPP