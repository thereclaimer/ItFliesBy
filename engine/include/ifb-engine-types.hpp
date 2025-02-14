#ifndef IFB_ENGINE_TYPES_HPP
#define IFB_ENGINE_TYPES_HPP

#include <ifb.hpp>

#ifdef IFB_ENGINE_INTERNAL
    #define ifb_engine_api __declspec(dllexport)
#else
    #define ifb_engine_api __declspec(dllimport)
#endif

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineConfig;
struct IFBEngineMemoryInfo;
struct IFBEngineSizeAndAlignment;
struct IFBEngineHandle;

/**********************************************************************************/
/* PUBLIC TYPES                                                                   */
/**********************************************************************************/

struct IFBEngineConfig {
    ifb_u16 memory_stack_size_kb;
    ifb_u16 memory_reservation_size_gb;
};

struct IFBEngineMemoryInfo {
    ifb_u64 reservation_size_total;
    ifb_u64 reservation_size_used;
    ifb_u32 stack_size_total;
    ifb_u32 stack_size_used;
};  

struct IFBEngineSizeAndAlignment {
    ifb_u32 size;
    ifb_u32 alignment;
};

struct IFBEngineHandle {
    ifb_u32 value;
};

#endif //IFB_ENGINE_TYPES_HPP