#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-core.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//memory manager
struct IFBEngineMemoryManager;
struct IFBEngineMemoryHandles;
struct IFBEngineMemoryStack;
struct IFBEngineMemoryArenas;

//sizes
struct IFBMemoryManagerSizes;

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

namespace ifb_engine {

    IFBEngineMemoryManager* memory_manager_create                (const IFBMEMStack global_stack_handle);    
    IFBVoid                 memory_manager_allocate_core_systems (const IFBEngineMemoryManager* memory_manager);
}

/**********************************************************************************/
/* STACK MEMORY                                                                    */
/**********************************************************************************/


enum IFBEngineMemoryStackOffset_ {
    IFBEngineMemoryStackOffset_Core_ManagerGraphics = 0,
    IFBEngineMemoryStackOffset_Core_ManagerThreads  = 1,
    IFBEngineMemoryStackOffset_Core_ManagerFiles    = 2,
    IFBEngineMemoryStackOffset_Count                = 3
};

typedef IFBU16 IFBEngineMemoryStackOffset;

struct IFBEngineMemoryStack {
    IFBAddr start;
};

namespace ifb_engine {

    IFBEngineGraphicsManager* memory_stack_get_manager_graphics (const IFBEngineMemoryStack* stack);
    IFBEngineFileManager*     memory_stack_get_manager_files    (const IFBEngineMemoryStack* stack);
    IFBEngineThreadManager*   memory_stack_get_manager_threads  (const IFBEngineMemoryStack* stack);

    IFBVoid                   memory_stack_get_core             (const IFBEngineMemoryStack* stack, IFBEngineCore& core);

};

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

enum IFBEngineMemoryArena_ {
    IFBEngineMemoryArena_Core_ManagerGraphics = 0,
    IFBEngineMemoryArena_Core_ManagerThreads  = 1,
    IFBEngineMemoryArena_Core_ManagerFiles    = 2,
    IFBEngineMemoryArena_Count                = 3
};

struct IFBEngineMemoryArenas {
    IFBMEMArena array[IFBEngineMemoryArena_Count]; 
};

/**********************************************************************************/
/* MEMORY MANAGER SIZES                                                           */
/**********************************************************************************/

//memory manager sizes
#define IFB_ENGINE_MEMORY_MANAGER_SIZE_GB_RESERVATION 4
#define IFB_ENGINE_MEMORY_MANAGER_SIZE_KB_ARENA       64
#define IFB_ENGINE_MEMORY_MANAGER_SIZE_RESERVATION    ifb_macro_size_gigabytes((IFBU64)IFB_ENGINE_MEMORY_MANAGER_SIZE_GB_RESERVATION)
#define IFB_ENGINE_MEMORY_MANAGER_SIZE_ARENA          ifb_macro_size_kilobytes(IFB_ENGINE_MEMORY_MANAGER_SIZE_KB_ARENA)

#define IFB_ENGINE_MEMORY_MANAGER_SIZE_STACK               0xFFFF
#define IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_MANAGER      ifb_macro_align_size_struct(IFBEngineMemoryManager)
#define IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_HANDLES      ifb_macro_align_size_struct(IFBEngineMemoryHandles)
#define IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_STACK        ifb_macro_align_size_struct(IFBEngineMemoryStack)
#define IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_ARENAS       ifb_macro_align_size_struct(IFBEngineMemoryArenas)
#define IFB_ENGINE_MEMORY_MANAGER_SIZE_STACK_OFFSET_STRIDE (IFB_ENGINE_MEMORY_MANAGER_SIZE_STACK / IFBEngineMemoryStackOffset_Count)

#define IFB_ENGINE_MEMORY_MANAGER_SIZE_MANAGER_TOTAL \
    IFB_ENGINE_MEMORY_MANAGER_SIZE_STACK          +  \
    IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_MANAGER +  \
    IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_HANDLES +  \
    IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_STACK   +  \
    IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_ARENAS 

struct IFBMemoryManagerSizes {
    IFBU32 gb_reservation;
    IFBU32 kb_arena;
    IFBU32 stack;
    IFBU16 stack_offset_stride;
    IFBU32 struct_manager;
    IFBU32 struct_handles;
    IFBU32 struct_stack;
    IFBU32 struct_arenas;
    IFBU32 total_arena;
    IFBU32 total_manager;
    IFBU64 total_reservation;
};

namespace ifb_engine {

    ifb_global constexpr IFBMemoryManagerSizes _memory_manager_sizes = {
        IFB_ENGINE_MEMORY_MANAGER_SIZE_GB_RESERVATION,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_KB_ARENA,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_STACK,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_STACK_OFFSET_STRIDE,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_MANAGER,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_HANDLES,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_STACK,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_STRUCT_ARENAS,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_ARENA,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_MANAGER_TOTAL,
        IFB_ENGINE_MEMORY_MANAGER_SIZE_RESERVATION
    };
};

/**********************************************************************************/
/* MEMORY CORE SIZES                                                              */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_WINDOW_TITLE  255
#define IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_WINDOW        ifb_graphics::window_memory_size(IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_WINDOW_TITLE)
#define IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_MANAGER       ifb_macro_align_size_struct(IFBEngineGraphicsManager)
#define IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_MANAGER_TOTAL \
    IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_WINDOW

struct IFBEngineMemoryGraphicsSizes {
    IFBU32 graphics_manager_struct;
    IFBU32 graphics_manager_total;
    IFBU32 window_title_length;
    IFBU32 window;
};

namespace ifb_engine {
    
    ifb_global const IFBEngineMemoryGraphicsSizes _memory_graphics_sizes = {
        IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_MANAGER, 
        IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_MANAGER_TOTAL, 
        IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_WINDOW_TITLE,
        IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_WINDOW
    };
};

#define IFB_ENGINE_MEMORY_CORE_SIZE_FILE_MANAGER     ifb_macro_align_size_struct(IFBEngineFileManager)
#define IFB_ENGINE_MEMORY_CORE_SIZE_THREAD_MANAGER   ifb_macro_align_size_struct(IFBEngineThreadManager)

#endif //IFB_ENGINE_MEMORY_HPP