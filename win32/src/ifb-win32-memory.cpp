#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void 
ifb_win32::memory_api_initialize(
    IFBEnginePlatformMemory& platform_memory_api_ref) {

    platform_memory_api_ref.pages_reserve  = ifb_win32::memory_reserve;
    platform_memory_api_ref.pages_release  = ifb_win32::memory_release;
    platform_memory_api_ref.pages_commit   = ifb_win32::memory_commit;
    platform_memory_api_ref.pages_decommit = ifb_win32::memory_decommit;
}

ifb_internal const ifb_memory
ifb_win32::memory_reserve(
    const ifb_size reservation_size) {

    const ifb_memory reservation = r_win32::memory_reserve(NULL,reservation_size);

    return(reservation);
}

ifb_internal const ifb_b8
ifb_win32::memory_release(
    const ifb_memory reservation_start,
    const ifb_size   reservation_size) {

    const ifb_b8 result = r_win32::memory_release(reservation_start,reservation_size);

    return(result);
}

ifb_internal const ifb_memory 
ifb_win32::memory_commit(
    const ifb_memory commit_start,
    const ifb_size   commit_size) {

    const ifb_memory commit_result = r_win32::memory_commit(commit_start,commit_size); 

    return(commit_result);
}

ifb_internal const ifb_b8 
ifb_win32::memory_decommit(
    const ifb_memory commit_start,
    const ifb_size   commit_size) {

    const ifb_b8 decommit_result = r_win32::memory_decommit(commit_start,commit_size);

    return(decommit_result);
}