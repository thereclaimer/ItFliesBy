#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-core.hpp"

namespace ifb {
/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//memory
struct engine_memory_t;
struct engine_memory_stack_t;
struct engine_memory_reservation_t;

//sizes
struct engine_memory_sizes_t;

//handles
typedef u16 engine_memory_arena_t;
typedef u16 engine_memory_singleton_t;

/**********************************************************************************/
/* RESERVED MEMORY                                                                */
/**********************************************************************************/

struct engine_memory_reservation_t {
    memory_reservation_h system_reservation_handle;
    memory_arena_h*      arena_handle_array;
};

/**********************************************************************************/
/* STACK MEMORY                                                                   */
/**********************************************************************************/

struct engine_memory_stack_t {
    memory_stack_h  global_stack_handle;
    byte*           singleton_buffer;
};

namespace engine {

    engine_context_t*       memory_stack_get_context       (const engine_memory_t* memory);
    engine_core_graphics_t* memory_stack_get_core_graphics (const engine_memory_t* memory);
    engine_core_files_t*    memory_stack_get_core_files    (const engine_memory_t* memory);
    engine_core_threads_t*  memory_stack_get_core_threads  (const engine_memory_t* memory);
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct engine_memory_t {
    engine_memory_stack_t       stack;
    engine_memory_reservation_t reservation;
};

namespace engine {

    engine_memory_t* memory_allocate (const memory_t& stack_memory);    
}

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

namespace engine {

    const b8   memory_arena_reset                       (const engine_memory_t* memory, const engine_memory_arena_t arena);
    const u32  memory_arena_push_bytes_relative         (const engine_memory_t* memory, const engine_memory_arena_t arena, const u32 size);
    const ptr  memory_arena_push_bytes_absolute_pointer (const engine_memory_t* memory, const engine_memory_arena_t arena, const u32 size);
    const addr memory_arena_push_bytes_absolute_address (const engine_memory_t* memory, const engine_memory_arena_t arena, const u32 size);
    const b8   memory_arena_pull_bytes                  (const engine_memory_t* memory, const engine_memory_arena_t arena, const u32 size);
    const ptr  memory_arena_get_pointer                 (const engine_memory_t* memory, const engine_memory_arena_t arena, const u32 offset);
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
#define IFB_ENGINE_MEMORY_SIZE_ARENA_HANDLE_ARRAY IFB_ENGINE_MEMORY_SIZE_ARENA_COUNT * sizeof(memory_arena_h)
#define IFB_ENGINE_MEMORY_SIZE_STRUCT             ifb_macro_align_size_struct(engine_memory_t)
#define IFB_ENGINE_MEMORY_SIZE_TOTAL_RESERVATION  ifb_macro_size_gigabytes((u64)IFB_ENGINE_MEMORY_SIZE_GB_RESERVATION)
#define IFB_ENGINE_MEMORY_SIZE_TOTAL_ARENA        ifb_macro_size_kilobytes(IFB_ENGINE_MEMORY_SIZE_KB_ARENA)
#define IFB_ENGINE_MEMORY_SIZE_TOTAL              \
    IFB_ENGINE_MEMORY_SIZE_SINGLETON_BUFFER   +   \
    IFB_ENGINE_MEMORY_SIZE_ARENA_HANDLE_ARRAY +   \
    IFB_ENGINE_MEMORY_SIZE_STRUCT

struct engine_memory_globals {
    u32 gb_reservation;
    u32 kb_arena;
    u32 singleton_count;
    u16 singleton_buffer;
    u16 singleton_stride;
    u16 arena_count;
    u32 arena_handle_array;
    u32 memory_struct;
    u32 total_arena;
    u32 total_memory;
    u64 total_reservation;
};

namespace engine {

    ifb_global constexpr engine_memory_globals _globals_memory = {
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
enum engine_memory_singleton_e {
    engine_memory_singleton_e_context       = (0 * IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE),
    engine_memory_singleton_e_core_graphics = (1 * IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE),
    engine_memory_singleton_e_core_threads  = (2 * IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE),
    engine_memory_singleton_e_core_files    = (3 * IFB_ENGINE_MEMORY_SIZE_SINGLETON_STRIDE),
    engine_memory_singleton_e_count         = 4
};

//arenas
enum engine_memory_arena_e {
    engine_memory_arena_e_context       = 0,
    engine_memory_arena_e_core_graphics = 1,
    engine_memory_arena_e_core_threads  = 2,
    engine_memory_arena_e_core_files    = 3,
};

}; //namespace ifb

#endif //IFB_ENGINE_MEMORY_HPP