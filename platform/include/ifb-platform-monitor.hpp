#ifndef IFB_PLATFORM_MONITOR_HPP
#define IFB_PLATFORM_MONITOR_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* MONITOR                                                                        */
/**********************************************************************************/

struct IFBMonitor;

typedef const IFBU32 (*IFBPlatformMonitorCount) (IFBVoid);
typedef const IFBB8  (*IFBPlatformMonitorInfo)  (const IFBU32 monitor_count, IFBMonitor* monitor_array);

#endif //IFB_PLATFORM_MONITOR_HPP