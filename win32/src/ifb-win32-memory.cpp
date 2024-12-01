#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void 
ifb_win32::memory_api_initialize(
    IFBEnginePlatformMemoryApi& platform_memory_api_ref) {

    platform_memory_api_ref.pages_commit   = ifb_win32::memory_commit;
    platform_memory_api_ref.pages_decommit = ifb_win32::memory_decommit;
}

ifb_internal const ifb_memory
ifb_win32::memory_reserve(
    const ifb_size reserve_size) {

    const ifb_memory reservation = 
        (ifb_memory)VirtualAlloc(
            NULL,
            reserve_size,
            MEM_RESERVE,
            PAGE_NOACCESS);

    return(reservation);
}

ifb_internal const ifb_b8
ifb_win32::memory_release(
    const ifb_memory reservation_start,
    const ifb_size   reserve_size) {

    const ifb_b8 release_result = VirtualFree(
        reservation_start,
        reserve_size,
        MEM_RELEASE);

    return(release_result);
}

ifb_internal const ifb_memory 
ifb_win32::memory_commit_pages(
          IFBPlatformMemory& platform_memory_ref,
    const ifb_u32            commit_size) {

    //calculate the commit start
    const ifb_u32    page_size           = platform_memory_ref.page_size;
    const ifb_u32    commit_size_aligned = ifb_macro_align_a_to_b(commit_size,page_size);
    const ifb_u32    page_count          = commit_size_aligned / page_size;
    const ifb_memory commit_start        = platform_memory_ref.reservation + (platform_memory_ref.page_count_used * page_size);

    //do the commit
    const ifb_memory commit_result = 
        (ifb_memory)VirtualAlloc(
            commit_start,
            commit_size_aligned,
            MEM_COMMIT,
            PAGE_READWRITE);

    //update the page count
    platform_memory_ref.page_count_used += page_count;

    return(commit_result);
}

ifb_internal const ifb_b8 
ifb_win32::memory_decommit(
    const ifb_memory commit_start,
    const ifb_size   commit_size) {

    const ifb_b8 decommit_result = VirtualFree(
        commit_start,
        commit_size,
        MEM_DECOMMIT);

    return(decommit_result);
}