#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

struct IFBEngineMemoryLinearArenas {
    IFBMemoryLinearArenaHandle frame;
};

enum IFBEngineMemoryBlockArenaId_ {
    IFBEngineMemoryBlockArenaId_Small     = 0,
    IFBEngineMemoryBlockArenaId_Large     = 1,
    IFBEngineMemoryBlockArenaId_AssetData = 2,
    IFBEngineMemoryBlockArenaId_Count     = 3
};

typedef ifb_u32 IFBEngineMemoryBlockArenaId;

struct IFBEngineMemoryBlockArenas {
    union {
        struct {
            IFBMemoryBlockArenaHandle small;
            IFBMemoryBlockArenaHandle large;
            IFBMemoryBlockArenaHandle asset_data;
        };
        IFBMemoryBlockArenaHandle array[IFBEngineMemoryBlockArenaId_Count];
    };
};

struct IFBEngineMemoryBlock {
    IFBEngineMemoryBlockArenaId arena_id;
    ifb_u32                     index;
};

struct IFBEngineMemoryArenas {
    IFBEngineMemoryLinearArenas linear;
    IFBEngineMemoryBlockArenas  block;
};

struct IFBEngineMemoryManager {
    IFBMemoryHandle       memory_handle;
    IFBEngineMemoryArenas arenas;
};

namespace ifb_engine {

    //create/destroy
    const ifb_b8   memory_manager_create    (ifb_void);
    const ifb_b8   memory_manager_destroy   (ifb_void);

    //frame memory
    const ifb_ptr  memory_frame_reserve     (const ifb_u32 size);
    const ifb_ptr  memory_frame_release     (const ifb_u32 size);
    const ifb_void memory_frame_reset       (ifb_void);

    //block memory
    const ifb_b8   memory_block_reserve     (IFBEngineMemoryBlock* memory_block_ptr);

    const ifb_b8   memory_block_release     (const IFBEngineMemoryBlock* memory_block_ptr);
    const ifb_ptr  memory_block_get_pointer (const IFBEngineMemoryBlock* memory_block_ptr, const ifb_u32 offset);
};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP