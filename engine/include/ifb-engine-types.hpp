#ifndef IFB_ENGINE_TYPES_HPP
#define IFB_ENGINE_TYPES_HPP

#include <ifb.hpp>
#include <ifb-graphics.hpp>

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

struct IFBHNDEngineSingleton : IFBHND32  { };
struct IFBHNDEngineArena     : IFBHNDPTR { };

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

struct IFBEngineContextUpdateWindow {
    IFBDimensions dimensions;
    IFBPosition   position;
};

enum IFBEngineContextUpdateFlags_ {
    IFBEngineContextUpdateFlags_None             = IFB_BIT_FLAG_0,
    IFBEngineContextUpdateFlags_Quit             = IFB_BIT_FLAG_1,
    IFBEngineContextUpdateFlags_WindowDimensions = IFB_BIT_FLAG_2,
    IFBEngineContextUpdateFlags_WindowPosition   = IFB_BIT_FLAG_3
};

typedef IFBU32 IFBEngineContextUpdateFlags;

struct IFBEngineContextUpdate {
    IFBEngineContextUpdateFlags  flags;    
    IFBEngineContextUpdateWindow window;
    IFBInput                     user_input;
};


namespace ifb_engine {

    inline IFBVoid     update_flags_set_quit              (IFBEngineContextUpdateFlags& flags_ref)       { ifb_macro_bit_set(IFBEngineContextUpdateFlags_Quit,             flags_ref); }
    inline IFBVoid     update_flags_set_window_dimensions (IFBEngineContextUpdateFlags& flags_ref)       { ifb_macro_bit_set(IFBEngineContextUpdateFlags_WindowDimensions, flags_ref); }
    inline IFBVoid     update_flags_set_window_position   (IFBEngineContextUpdateFlags& flags_ref)       { ifb_macro_bit_set(IFBEngineContextUpdateFlags_WindowPosition,   flags_ref); }

    inline const IFBB8 update_flags_get_quit              (const IFBEngineContextUpdateFlags& flags_ref) { return(ifb_macro_bit_test(IFBEngineContextUpdateFlags_Quit,             flags_ref)); }
    inline const IFBB8 update_flags_get_window_dimensions (const IFBEngineContextUpdateFlags& flags_ref) { return(ifb_macro_bit_test(IFBEngineContextUpdateFlags_WindowDimensions, flags_ref)); }
    inline const IFBB8 update_flags_get_window_position   (const IFBEngineContextUpdateFlags& flags_ref) { return(ifb_macro_bit_test(IFBEngineContextUpdateFlags_WindowPosition,   flags_ref)); }
};

#endif //IFB_ENGINE_TYPES_HPP