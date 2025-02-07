#ifndef IFB_ENGINE_TYPES_HPP
#define IFB_ENGINE_TYPES_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* PUBLIC TYPES                                                                   */
/**********************************************************************************/

struct IFBEngineMemoryInfo {
    ifb_u64 reservation_size_total;
    ifb_u64 reservation_size_used;
    ifb_u32 stack_size_total;
    ifb_u32 stack_size_used;
};  

/**********************************************************************************/
/* INTERNAL TYPES                                                                 */
/**********************************************************************************/

struct IFBEngineContext;
struct IFBEngineMemory;
struct IFBEngineAllocators;

#endif //IFB_ENGINE_TYPES_HPP