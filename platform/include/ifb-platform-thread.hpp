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

typedef const IFBU32 (*IFBPlatformThreadSize)        (IFBVoid);
typedef const IFBB8  (*IFBPlatformThreadCreate)      (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadDestroy)     (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadAssignCores) (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadWake)        (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadSleep)       (const IFBPlatformThreadRequest* request);
typedef const IFBB8  (*IFBPlatformThreadGetStatus)   (const IFBPlatformThreadRequest* request);

#endif //IFB_PLATFORM_THREAD_HPP