#ifndef IFB_PLATFORM_MEMORY_HPP
#define IFB_PLATFORM_MEMORY_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* MEMORY API                                                                     */
/**********************************************************************************/

typedef const IFBPtr (*IFBPlatformMemoryReserve)  (const IFBU64 reservation_size);
typedef const IFBB8  (*IFBPlatformMemoryRelease)  (const IFBPtr reservation_start, const IFBU64 reservation_size);
typedef const IFBPtr (*IFBPlatformMemoryCommit)   (const IFBPtr commit_start,      const IFBU64 commit_size);
typedef const IFBB8  (*IFBPlatformMemoryDecommit) (const IFBPtr commit_start,      const IFBU64 commit_size);

struct IFBPlatformAPIMemory {
    IFBPlatformMemoryReserve  reserve;
    IFBPlatformMemoryRelease  release;
    IFBPlatformMemoryCommit   commit;
    IFBPlatformMemoryDecommit decommit;
};

#endif //IFB_PLATFORM_MEMORY_HPP