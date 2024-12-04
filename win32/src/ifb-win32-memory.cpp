#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void 
ifb_win32::memory_api_initialize(
    IFBPlatformMemoryApi& platform_memory_api_ref) {
    
    platform_memory_api_ref.reserve = ifb_win32::memory_reserve;
    platform_memory_api_ref.release = ifb_win32::memory_release;
    platform_memory_api_ref.commit  = ifb_win32::memory_commit;
}

ifb_internal const ifb_b8 
ifb_win32::memory_reserve(
    IFBPlatformMemoryReservation& reservation_ref) {

    const ifb_size reservation_size = ifb_platform::memory_reservation_size_total(reservation_ref);

    reservation_ref.start = (ifb_memory)VirtualAlloc(
            NULL,
            reservation_size,
            MEM_RESERVE,
            PAGE_NOACCESS);

    return(reservation_ref.start != NULL);
}

ifb_internal const ifb_b8 
ifb_win32::memory_release(
    IFBPlatformMemoryReservation& reservation_ref) {

    const ifb_size reservation_size = ifb_platform::memory_reservation_size_total(reservation_ref);

    const ifb_b8 result = VirtualFree(
        reservation_ref.start,
        reservation_size,
        MEM_RELEASE);

    if (result) {
        reservation_ref.start = NULL;
    }

    return(result);
}

ifb_internal const ifb_b8 
ifb_win32::memory_commit(
    IFBPlatformMemoryReservation& reservation_ref, 
    IFBPlatformMemoryCommit&      commit_ref) {

    //calculate commit size and start
    const ifb_memory commit_start = ifb_platform::memory_commit_start(reservation_ref);
    const ifb_size   commit_size  = ifb_platform::memory_commit_size (commit_ref);

    //do the commit
    const ifb_memory commit_result = (ifb_memory)VirtualAlloc(
        commit_start,
        commit_size,
        MEM_COMMIT,
        PAGE_READWRITE);

    //if that failed, we're done
    if (commit_start != commit_result) {
        commit_ref.start = NULL;
        return(false);       
    }

    //otherwise, update the commit start and the used page count
    commit_ref.start = commit_start;
    reservation_ref.page_count_used += commit_ref.page_count; 

    //we're done
    return(true);
}