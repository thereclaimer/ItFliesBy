#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void 
ifb_win32::memory_api_initialize(
    IFBEnginePlatformMemory& platform_memory_api_ref) {

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
ifb_win32::memory_commit(
    const ifb_memory commit_start,
    const ifb_size   commit_size) {

    const ifb_memory commit_result = 
        (ifb_memory)VirtualAlloc(
            commit_start,
            commit_size,
            MEM_COMMIT,
            PAGE_READWRITE);

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