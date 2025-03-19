#ifndef IFB_TYPES_SYSTEM_HPP
#define IFB_TYPES_SYSTEM_HPP

#include "ifb-types-primitives.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBSystemInfo;
struct IFBSystemMemory;
struct IFBSystemCPU;

/**********************************************************************************/
/* SYSTEM TYPES                                                                   */
/**********************************************************************************/

struct IFBSystemMemoryInfo {
    IFBU32 page_size;
    IFBU32 allocation_granularity;
};

struct IFBSystemCPUCacheInfo {
    IFBU32 size_total;
    IFBU32 size_line;
};

struct IFBSystemCPUInfo {
    IFBU32                parent_core_number;
    IFBU32                speed_mhz;
    IFBU32                core_count_physical;
    IFBU32                core_count_logical;
    IFBSystemCPUCacheInfo cache_l1;
    IFBSystemCPUCacheInfo cache_l2;
    IFBSystemCPUCacheInfo cache_l3;
};

struct IFBSystemInfo {
    IFBSystemCPUInfo    cpu;
    IFBSystemMemoryInfo memory;
};

#endif //IFB_TYPES_SYSTEM_HPP