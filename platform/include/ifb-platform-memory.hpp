#ifndef IFB_PLATFORM_MEMORY_HPP
#define IFB_PLATFORM_MEMORY_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* MEMORY API                                                                     */
/**********************************************************************************/

typedef const ifb::ptr (*IFBPlatformMemoryReserve)  (const ifb::u64 reservation_size);
typedef const ifb::b8  (*IFBPlatformMemoryRelease)  (const ifb::ptr reservation_start, const ifb::u64 reservation_size);
typedef const ifb::ptr (*IFBPlatformMemoryCommit)   (const ifb::ptr commit_start,      const ifb::u64 commit_size);
typedef const ifb::b8  (*IFBPlatformMemoryDecommit) (const ifb::ptr commit_start,      const ifb::u64 commit_size);

struct IFBPlatformAPIMemory {
    IFBPlatformMemoryReserve  reserve;
    IFBPlatformMemoryRelease  release;
    IFBPlatformMemoryCommit   commit;
    IFBPlatformMemoryDecommit decommit;
};

#endif //IFB_PLATFORM_MEMORY_HPP