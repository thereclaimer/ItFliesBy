#ifndef IFB_ENGINE_TYPES_HPP
#define IFB_ENGINE_TYPES_HPP

#include <ifb.hpp>


/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineConfig;
struct IFBEngineMemoryInfo;
struct IFBEngineSizeAndAlignment;


struct IFBEngineMemoryArenaUnmanaged;
struct IFBEngineMemoryArenaLinear;
struct IFBEngineMemoryArenaBlock;

/**********************************************************************************/
/* HANDLES                                                                        */
/**********************************************************************************/

struct IFBEngineHandle {
    IFBU32 value;
};

struct IFBEngineSingletonHandle : IFBEngineHandle { };

/**********************************************************************************/
/* PUBLIC TYPES                                                                   */
/**********************************************************************************/

struct IFBEngineConfig {
    IFBU16 memory_stack_size_kb;
    IFBU16 memory_reservation_size_gb;
};

struct IFBEngineMemoryInfo {
    IFBU64 reservation_size_total;
    IFBU64 reservation_size_used;
    IFBU32 stack_size_total;
    IFBU32 stack_size_used;
};  

struct IFBEngineSizeAndAlignment {
    IFBU32 size;
    IFBU32 alignment;
};

struct IFBEngineContextUpdate {
    IFBPosition   window_position;
    IFBDimensions window_dimensions;
    IFBInput      user_input;
};

typedef IFBHNDArena  IFBHNDEngineArena;
typedef IFBArenaInfo IFBEngineArenaInfo;

#endif //IFB_ENGINE_TYPES_HPP