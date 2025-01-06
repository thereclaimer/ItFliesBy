#ifndef IFB_ENGINE_INTERNAL_MANAGERS_HPP
#define IFB_ENGINE_INTERNAL_MANAGERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-data.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineFrameArenas {
    IFBLinearArena engine;
    IFBLinearArena game;
    IFBLinearArena platform;
};

#define IFB_ENGINE_SCRATCH_ARENA_COUNT   32
#define IFB_ENGINE_SCRATCH_ARENA_SIZE_KB ifb_macro_size_kilobytes(64)    

struct IFBEngineScratchArenas  {
    union {
        struct {
            IFBScratchArena arena_00;
            IFBScratchArena arena_01;
            IFBScratchArena arena_02;
            IFBScratchArena arena_03;
            IFBScratchArena arena_04;
            IFBScratchArena arena_05;
            IFBScratchArena arena_06;
            IFBScratchArena arena_07;
            IFBScratchArena arena_08;
            IFBScratchArena arena_09;
            IFBScratchArena arena_10;
            IFBScratchArena arena_11;
            IFBScratchArena arena_12;
            IFBScratchArena arena_13;
            IFBScratchArena arena_14;
            IFBScratchArena arena_15;
            IFBScratchArena arena_16;
            IFBScratchArena arena_17;
            IFBScratchArena arena_18;
            IFBScratchArena arena_19;
            IFBScratchArena arena_20;
            IFBScratchArena arena_21;
            IFBScratchArena arena_22;
            IFBScratchArena arena_23;
            IFBScratchArena arena_24;
            IFBScratchArena arena_25;
            IFBScratchArena arena_26;
            IFBScratchArena arena_27;
            IFBScratchArena arena_28;
            IFBScratchArena arena_29;
            IFBScratchArena arena_30;
            IFBScratchArena arena_31;
        };
        IFBScratchArena array[IFB_ENGINE_SCRATCH_STACK_COUNT];
    };
};

struct IFBEngineArenaManager {
    IFBEngineFrameArenas   frame;
    IFBEngineScratchArenas scratch_space;
};

namespace ifb_engine {

    arena_mangager_initialize(IFBEngineArenaManager* arena_manager_ptr);

    const ifb_b8 arena_manager_scratch_space_reserve (IFBEngineArenaManager* arena_manager_ptr, IFBScratchArena& scratch_arena_ref);
    const ifb_b8 arena_manager_scratch_space_release (IFBEngineArenaManager* arena_manager_ptr, IFBScratchArena& scratch_arena_ref);

    ifb_ptr arena_manager_frame_arena_push_engine    (IFBEngineArenaManager* arena_manager_ptr, const ifb_u32);
    ifb_ptr arena_manager_frame_arena_push_game      (IFBEngineArenaManager* arena_manager_ptr, const ifb_u32);
    ifb_ptr arena_manager_frame_arena_push_platform  (IFBEngineArenaManager* arena_manager_ptr, const ifb_u32);

    ifb_ptr arena_manager_frame_arena_pull_engine    (IFBEngineArenaManager* arena_manager_ptr, const ifb_u32);
    ifb_ptr arena_manager_frame_arena_pull_game      (IFBEngineArenaManager* arena_manager_ptr, const ifb_u32);
    ifb_ptr arena_manager_frame_arena_pull_platform  (IFBEngineArenaManager* arena_manager_ptr, const ifb_u32);
 
    const ifb_b8 arena_manager_frame_arena_reset_all (IFBEngineArenaManager* arena_manager_ptr);

};

#endif //IFB_ENGINE_INTERNAL_MANAGERS_HPP  