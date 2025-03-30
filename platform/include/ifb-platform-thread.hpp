#ifndef IFB_PLATFORM_THREAD_HPP
#define IFB_PLATFORM_THREAD_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBPlatformThreadRequest;

/**********************************************************************************/
/* THREAD API                                                                     */
/**********************************************************************************/

typedef const ifb::u32 (*IFBPlatformThreadSize)        (void);
typedef const ifb::b8  (*IFBPlatformThreadCreate)      (const IFBPlatformThreadRequest* request);
typedef const ifb::b8  (*IFBPlatformThreadDestroy)     (const IFBPlatformThreadRequest* request);
typedef const ifb::b8  (*IFBPlatformThreadAssignCores) (const IFBPlatformThreadRequest* request);
typedef const ifb::b8  (*IFBPlatformThreadWake)        (const IFBPlatformThreadRequest* request);
typedef const ifb::b8  (*IFBPlatformThreadSleep)       (const IFBPlatformThreadRequest* request);
typedef const ifb::b8  (*IFBPlatformThreadGetStatus)   (const IFBPlatformThreadRequest* request);

#endif //IFB_PLATFORM_THREAD_HPP