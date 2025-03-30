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

struct IFBSystemCPUCacheInfo {
    ifb::u32 size_total;
    ifb::u32 size_line;
};

struct IFBSystemCPUInfo {
    ifb::u32                parent_core_number;
    ifb::u32                speed_mhz;
    ifb::u32                core_count_physical;
    ifb::u32                core_count_logical;
    IFBSystemCPUCacheInfo cache_l1;
    IFBSystemCPUCacheInfo cache_l2;
    IFBSystemCPUCacheInfo cache_l3;
};

struct IFBSystemMemoryInfo {
    ifb::u32 page_size;
    ifb::u32 allocation_granularity;
};

typedef const ifb::b8     (*IFBPlatformSystemGetInfoCPU)    (IFBSystemCPUInfo*    cpu_info);
typedef const ifb::b8     (*IFBPlatformSystemGetInfoMemory) (IFBSystemMemoryInfo* memory_info);
typedef const ifb::ms (*IFBPlatformSystemTimeMS)        (void);
typedef void         (*IFBPlatformSystemSleep)         (const ifb::u32   ms);
typedef void         (*IFBPlatformSystemDebugPrint)    (const ifb::utf8* debug_string);

#endif //IFB_PLATFORM_SYSTEM_HPP