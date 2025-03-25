#pragma once

#include "ifb-platform-win32-internal.cpp"

ifb_internal const IFBPtr 
ifb_platform::win32_memory_reserve(
    const IFBU64 reservation_size) {

    const IFBPtr reservation_start = VirtualAlloc(
            NULL,
            reservation_size,
            MEM_RESERVE,
            PAGE_NOACCESS);

    return(reservation_start);
}

ifb_internal const IFBB8 
ifb_platform::win32_memory_release(
    const IFBPtr reservation_start, 
    const IFBU64 reservation_size) {

    const IFBB8 result = VirtualFree(
        reservation_start,
        reservation_size,
        MEM_RELEASE);

    return(result);
}

ifb_internal const IFBPtr 
ifb_platform::win32_memory_commit(
    const IFBPtr commit_start,
    const IFBU64 commit_size) {

    //do the commit
    const IFBPtr commit_result = VirtualAlloc(
        commit_start,
        commit_size,
        MEM_COMMIT,
        PAGE_READWRITE);

    //we're done
    return(commit_result);
}

ifb_internal const IFBB8
ifb_platform::win32_memory_decommit(
    const IFBPtr commit_start,
    const IFBU64 commit_size) {

    //do the decommit
    const IFBB8 free_result = VirtualFree(
        commit_start,        
        commit_size,
        MEM_DECOMMIT);

    return(free_result);
}