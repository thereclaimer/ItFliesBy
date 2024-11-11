#pragma once

#include "ifb-win32.hpp"

ifb_internal ifb_void 
ifb_win32::memory_api_initialize(
    IFBEnginePlatformMemory& platform_memory_api_ref) {

    platform_memory_api_ref.pages_commit   = ifb_win32::memory_commit;
    platform_memory_api_ref.pages_decommit = ifb_win32::memory_decommit;
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