#ifndef IFB_THREADING_HPP
#define IFB_THREADING_HPP

#include <ifb.hpp>

namespace ifb_thread_pool {

    IFBThreadPool* arena_load_pointer    (IFBMemoryArena* ptr_arena, const IFBU32 arena_offset);
    IFBThreadPool* arena_commit_absolute (IFBMemoryArena* ptr_arena, const IFBU32 thread_count);
    const IFBU32   arena_commit_relative (IFBMemoryArena* ptr_arena, const IFBU32 thread_count);


    IFBThread*  reserve_thread();
    const IFBB8 release_thread();
};

#endif //IFB_THREADING_HPP