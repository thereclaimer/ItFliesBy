#ifndef IFB_ENGINE_TYPES_HPP
#define IFB_ENGINE_TYPES_HPP

#include <ifb.hpp>

#ifdef IFB_ENGINE_INTERNAL
    #define ifb_engine_api __declspec(dllexport)
#else
    #define ifb_engine_api __declspec(dllimport)
#endif

/**********************************************************************************/
/* PUBLIC TYPES                                                                   */
/**********************************************************************************/

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

/**********************************************************************************/
/* INTERNAL TYPES                                                                 */
/**********************************************************************************/

struct IFBEngineContext;
struct IFBEngineMemory;
struct IFBEngineAllocators;

#endif //IFB_ENGINE_TYPES_HPP