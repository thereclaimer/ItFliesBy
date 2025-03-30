#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-core.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//memory
struct IFBEngineMemory;
struct IFBEngineStack;
struct IFBEngineReservation;

//sizes
struct IFBMemorySizes;

//handles
typedef IFBU16 IFBEngineArena;
typedef IFBU16 IFBEngineSingleton;

/**********************************************************************************/
/* RESERVED MEMORY                                                                */
/**********************************************************************************/

struct IFBEngineReservation {
    IFBMEMReservation system_reservation_handle;
    IFBMEMArena*      arena_handle_array;
};

/**********************************************************************************/
/* STACK MEMORY                                                                   */
/**********************************************************************************/

struct IFBEngineStack {
    IFBMEMStack global_stack_handle;
    IFBByte*    singleton_buffer;
};

namespace ifb_engine {

    IFBEngineContext*         memory_stack_get_context          (const IFBEngineMemory* memory);

    IFBEngineGraphicsManager* memory_stack_get_manager_graphics (const IFBEngineMemory* memory);
    IFBEngineFileManager*     memory_stack_get_manager_files    (const IFBEngineMemory* memory);
    IFBEngineThreadManager*   memory_stack_get_manager_threads  (const IFBEngineMemory* memory);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineMemory {
    IFBEngineStack       stack;
    IFBEngineReservation reservation;
};

namespace ifb_engine {

    IFBEngineMemory* memory_allocate (const IFBMemory& stack_memory);    
}

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8   memory_arena_reset                       (const IFBEngineMemory* memory, const IFBEngineArena arena);
    const IFBU32  memory_arena_push_bytes_relative         (const IFBEngineMemory* memory, const IFBEngineArena arena, const IFBU32 size);
    const IFBPtr  memory_arena_push_bytes_absolute_pointer (const IFBEngineMemory* memory, const IFBEngineArena arena, const IFBU32 size);
    const IFBAddr memory_arena_push_bytes_absolute_address (const IFBEngineMemory* memory, const IFBEngineArena arena, const IFBU32 size);
    const IFBB8   memory_arena_pull_bytes                  (const IFBEngineMemory* memory, const IFBEngineArena arena, const IFBU32 size);
    const IFBPtr  memory_arena_get_pointer                 (const IFBEngineMemory* memory, const IFBEngineArena arena, const IFBU32 offset);
};

/**********************************************************************************/
/* MEMORY MANAGER SIZES                                                           */
/**********************************************************************************/

//memory sizes
#define IFB_ENGINE_MEMORY_SIZE_GB_RESERVATION     4
#define IFB_ENGINE_MEMORY_SIZE_KB_ARENA           64
#define IFB_ENGINE_MEMORY_SIZE_SINGLETON_COUNT    4
#define IFB_ENGINE_MEMORY_SIZE_SINGLETON_BUFFER   0xFFFF
#define IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE   IFB_ENGINE_MEMORY_SIZE_SINGLETON_BUFFER / IFB_ENGINE_MEMORY_SIZE_SINGLETON_COUNT
#define IFB_ENGINE_MEMORY_SIZE_ARENA_COUNT        4
#define IFB_ENGINE_MEMORY_SIZE_ARENA_HANDLE_ARRAY IFB_ENGINE_MEMORY_SIZE_ARENA_COUNT * sizeof(IFBMEMArena)
#define IFB_ENGINE_MEMORY_SIZE_STRUCT             ifb_macro_align_size_struct(IFBEngineMemory)
#define IFB_ENGINE_MEMORY_SIZE_TOTAL_RESERVATION  ifb_macro_size_gigabytes((IFBU64)IFB_ENGINE_MEMORY_SIZE_GB_RESERVATION)
#define IFB_ENGINE_MEMORY_SIZE_TOTAL_ARENA        ifb_macro_size_kilobytes(IFB_ENGINE_MEMORY_SIZE_KB_ARENA)
#define IFB_ENGINE_MEMORY_SIZE_TOTAL              \
    IFB_ENGINE_MEMORY_SIZE_SINGLETON_BUFFER   +   \
    IFB_ENGINE_MEMORY_SIZE_ARENA_HANDLE_ARRAY +   \
    IFB_ENGINE_MEMORY_SIZE_STRUCT

struct IFBMemorySizes {
    IFBU32 gb_reservation;
    IFBU32 kb_arena;
    IFBU32 singleton_count;
    IFBU16 singleton_buffer;
    IFBU16 singleton_stride;
    IFBU16 arena_count;
    IFBU32 arena_handle_array;
    IFBU32 memory_struct;
    IFBU32 total_arena;
    IFBU32 total_memory;
    IFBU64 total_reservation;
};

namespace ifb_engine {

    ifb_global constexpr IFBMemorySizes _global_memory_sizes = {
        IFB_ENGINE_MEMORY_SIZE_GB_RESERVATION,
        IFB_ENGINE_MEMORY_SIZE_KB_ARENA,
        IFB_ENGINE_MEMORY_SIZE_SINGLETON_COUNT,
        IFB_ENGINE_MEMORY_SIZE_SINGLETON_BUFFER,
        IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE,
        IFB_ENGINE_MEMORY_SIZE_ARENA_COUNT,
        IFB_ENGINE_MEMORY_SIZE_ARENA_HANDLE_ARRAY,
        IFB_ENGINE_MEMORY_SIZE_STRUCT,
        IFB_ENGINE_MEMORY_SIZE_TOTAL_ARENA,
        IFB_ENGINE_MEMORY_SIZE_TOTAL,
        IFB_ENGINE_MEMORY_SIZE_TOTAL_RESERVATION
    };
};

//singletons
enum IFBEngineSingleton_ {
    IFBEngineSingleton_Context              = (0 * IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE),
    IFBEngineSingleton_Core_ManagerGraphics = (1 * IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE),
    IFBEngineSingleton_Core_ManagerThreads  = (2 * IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE),
    IFBEngineSingleton_Core_ManagerFiles    = (3 * IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE),
    IFBEngineSingleton_Count                = 4
};

//arenas
enum IFBEngineArena_ {
    IFBEngineArena_Context              = 0,
    IFBEngineArena_Core_ManagerGraphics = 1,
    IFBEngineArena_Core_ManagerThreads  = 2,
    IFBEngineArena_Core_ManagerFiles    = 3,
};

/**********************************************************************************/
/* MEMORY CORE SIZES                                                              */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_WINDOW_TITLE  255
#define IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_MANAGER       ifb_macro_align_size_struct(IFBEngineGraphicsManager)

struct IFBEngineMemoryGraphicsSizes {
    IFBU32 graphics_manager_struct;
    IFBU32 window_title_length;
};

namespace ifb_engine {
    
    ifb_global const IFBEngineMemoryGraphicsSizes _memory_graphics_sizes = {
        IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_MANAGER, 
        IFB_ENGINE_MEMORY_CORE_SIZE_GRAPHICS_WINDOW_TITLE,
    };
};

#define IFB_ENGINE_MEMORY_CORE_SIZE_FILE_MANAGER     ifb_macro_align_size_struct(IFBEngineFileManager)
#define IFB_ENGINE_MEMORY_CORE_SIZE_THREAD_MANAGER   ifb_macro_align_size_struct(IFBEngineThreadManager)

#endif //IFB_ENGINE_MEMORY_HPP