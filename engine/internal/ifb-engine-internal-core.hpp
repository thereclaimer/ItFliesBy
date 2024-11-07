#ifndef IFB_ENGINE_CORE_HPP
#define IFB_ENGINE_CORE_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* CORE MEMORY                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_CORE_MEMORY_CSTRING_MAX_SIZE 256
#define IFB_ENGINE_CORE_MEMORY_WSTRING_MAX_SIZE 128

#define IFB_ENGINE_CORE_MEMORY_ARENA_TAG            "ENGINE CORE"
#define IFB_ENGINE_CORE_MEMORY_ARENA_SIZE_KILOBYTES 64
#define IFB_ENGINE_CORE_MEMORY_ARENA_COUNT          2

/**********************************************************************************/
/* CORE MEMORY                                                                    */
/**********************************************************************************/

struct IFBEngineCoreMemory {
    ifb_size w_str_size_max;
    ifb_size c_str_size_max;
    ifb_size arena_size;
    ifb_size arena_count;
    struct {
        IFBEngineMemoryArenaHandle system;
        IFBEngineMemoryArenaHandle frame;
    } arenas;
    IFBEngineMemoryArenaPoolHandle arena_pool;
};

namespace ifb_engine {

    //--------------------
    // core memory
    //--------------------

    const ifb_b8 core_memory_reserve(IFBEngineCoreMemory& core_memory_ref);

    //--------------------
    // system arena
    //--------------------

    const ifb_memory core_memory_system_arena_push         (IFBEngineCoreMemory& core_memory_ref, const ifb_size size);
    const ifb_memory core_memory_system_arena_push         (const ifb_size size);
    const ifb_memory core_memory_system_arena_push_aligned (IFBEngineCoreMemory& core_memory_ref, const ifb_size size, const ifb_size alignment);
    const ifb_memory core_memory_system_arena_push_aligned (const ifb_size size, const ifb_size alignment);
    const ifb_cstr   core_memory_system_arena_push_cstring (const ifb_cstr string);

    //--------------------
    // frame arena
    //--------------------

    const ifb_memory core_memory_frame_arena_push         (IFBEngineCoreMemory& core_memory_ref, const ifb_size size);
    const ifb_memory core_memory_frame_arena_push         (const ifb_size size);
    const ifb_memory core_memory_frame_arena_push_aligned (IFBEngineCoreMemory& core_memory_ref, const ifb_size size, const ifb_size alignment);
    const ifb_memory core_memory_frame_arena_push_aligned (const ifb_size size, const ifb_size alignment);
    const ifb_cstr   core_memory_frame_arena_push_cstring (const ifb_cstr string);
};


#define ifb_engine_core_arena_push_struct(struct)        \
    (struct*)ifb_engine::core_system_arena_push_aligned( \
        sizeof(struct),                                  \
        alignof(struct))                                 \

#define ifb_engine_core_arena_push_array(count,type) \
    (type*)ifb_engine::core_system_arena_push(       \
        sizeof(type) * count)                        \

#define ifb_engine_core_arena_ref_push_struct(core_memory_ref,struct) \
    (struct*)ifb_engine::core_system_arena_push_aligned(              \
        core_memory_ref,                                              \
        sizeof(struct),                                               \
        alignof(struct))                                              \

#define ifb_engine_core_arena_ref_push_array(core_memory_ref,count,type) \
    (type*)ifb_engine::core_system_arena_push(                           \
        core_memory_ref,                                                 \
        sizeof(type) * count)                                            \

/**********************************************************************************/
/* ENGINE CORE                                                                    */
/**********************************************************************************/

struct IFBEngineCore {
    IFBEngineCoreMemory memory;
};

namespace ifb_engine {

    const ifb_b8 core_initialize (IFBEngineCore& core_ref);
};

#endif //IFB_ENGINE_CORE_HPP