#ifndef IFB_PLATFORM_MEMORY_HPP
#define IFB_PLATFORM_MEMORY_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* MEMORY API                                                                     */
/**********************************************************************************/

namespace ifb {

    typedef const ptr (*platform_api_memory_reserve_f)  (const u64 reservation_size);
    typedef const b8  (*platform_api_memory_release_f)  (const ptr reservation_start, const u64 reservation_size);
    typedef const ptr (*platform_api_memory_commit_f)   (const ptr commit_start,      const u64 commit_size);
    typedef const b8  (*platform_api_memory_decommit_f) (const ptr commit_start,      const u64 commit_size);
};

#endif //IFB_PLATFORM_MEMORY_HPP