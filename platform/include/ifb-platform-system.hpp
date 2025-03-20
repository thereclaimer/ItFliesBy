#ifndef IFB_PLATFORM_SYSTEM_HPP
#define IFB_PLATFORM_SYSTEM_HPP

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBSystemMemoryInfo;
struct IFBSystemCPUCacheInfo;
struct IFBSystemCPUInfo;
struct IFBSystemInfo;

/**********************************************************************************/
/* SYSTEM API                                                                     */
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

typedef const IFBB8     (*IFBPlatformSystemGetInfo)    (IFBSystemInfo* system_info);
typedef const IFBTimems (*IFBPlatformSystemTimeMS)     (IFBVoid);
typedef IFBVoid         (*IFBPlatformSystemSleep)      (const IFBU32   ms);
typedef IFBVoid         (*IFBPlatformSystemDebugPrint) (const IFBChar* debug_string);

#endif //IFB_PLATFORM_SYSTEM_HPP