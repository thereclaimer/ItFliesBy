#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//memory manager
struct IFBEngineMemoryManager;
struct IFBEngineMemoryHandles;
struct IFBEngineMemoryStack;
struct IFBEngineMemoryArenas;

//sizes
struct IFBMemorySizes;

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineMemoryManager {
    IFBEngineMemoryHandles* handles;
    IFBEngineMemoryStack*   stack;
    IFBEngineMemoryArenas*  arenas;
};

struct IFBEngineMemoryHandles {
    IFBMEMStack       global_stack;
    IFBMEMReservation system_reservation;    
};

struct IFBEngineMemoryStack {
    IFBAddr start;
    struct {
        IFBU16 graphics_manager;
        IFBU16 threads_manager;
        IFBU16 files_manager;
    } offsets;
};

struct IFBEngineMemoryArenas {
    IFBMEMArena graphics_manager;
    IFBMEMArena thread_manager;
    IFBMEMArena file_manager;
};

namespace ifb_engine {

    IFBEngineMemoryManager* memory_manager_create(const IFBMEMStack global_stack_handle);    
}

/**********************************************************************************/
/* SIZES                                                                          */
/**********************************************************************************/

//memory manager sizes
#define IFB_ENGINE_MEMORY_SIZE_GB_RESERVATION 4
#define IFB_ENGINE_MEMORY_SIZE_KB_ARENA       64
#define IFB_ENGINE_MEMORY_SIZE_RESERVATION    ifb_macro_size_gigabytes((IFBU64)IFB_ENGINE_MEMORY_SIZE_GB_RESERVATION)
#define IFB_ENGINE_MEMORY_SIZE_ARENA          ifb_macro_size_kilobytes(IFB_ENGINE_MEMORY_SIZE_KB_ARENA)

#define IFB_ENGINE_MEMORY_SIZE_STACK          0xFFFF
#define IFB_ENGINE_MEMORY_SIZE_STRUCT_MANAGER ifb_macro_align_size_struct(IFBEngineMemoryManager)
#define IFB_ENGINE_MEMORY_SIZE_STRUCT_HANDLES ifb_macro_align_size_struct(IFBEngineMemoryHandles)
#define IFB_ENGINE_MEMORY_SIZE_STRUCT_STACK   ifb_macro_align_size_struct(IFBEngineMemoryStack)
#define IFB_ENGINE_MEMORY_SIZE_STRUCT_ARENAS  ifb_macro_align_size_struct(IFBEngineMemoryArenas)

#define IFB_ENGINE_MEMORY_SIZE_MANAGER_TOTAL \
    IFB_ENGINE_MEMORY_SIZE_STACK          +  \
    IFB_ENGINE_MEMORY_SIZE_STRUCT_MANAGER +  \
    IFB_ENGINE_MEMORY_SIZE_STRUCT_HANDLES +  \
    IFB_ENGINE_MEMORY_SIZE_STRUCT_STACK   +  \
    IFB_ENGINE_MEMORY_SIZE_STRUCT_ARENAS 

struct IFBMemorySizes {
    IFBU32 gb_reservation;
    IFBU32 kb_arena;
    IFBU32 stack;
    IFBU32 struct_manager;
    IFBU32 struct_handles;
    IFBU32 struct_stack;
    IFBU32 struct_arenas;
    IFBU32 total_arena;
    IFBU32 total_manager;
    IFBU64 total_reservation;
};

namespace ifb_engine {

    constexpr IFBMemorySizes _memory_sizes = {
        IFB_ENGINE_MEMORY_SIZE_GB_RESERVATION,
        IFB_ENGINE_MEMORY_SIZE_KB_ARENA,
        IFB_ENGINE_MEMORY_SIZE_STACK,
        IFB_ENGINE_MEMORY_SIZE_STRUCT_MANAGER,
        IFB_ENGINE_MEMORY_SIZE_STRUCT_HANDLES,
        IFB_ENGINE_MEMORY_SIZE_STRUCT_STACK,
        IFB_ENGINE_MEMORY_SIZE_STRUCT_ARENAS,
        IFB_ENGINE_MEMORY_SIZE_ARENA,
        IFB_ENGINE_MEMORY_SIZE_MANAGER_TOTAL,
        IFB_ENGINE_MEMORY_SIZE_RESERVATION
    };
};

#endif //IFB_ENGINE_MEMORY_HPP