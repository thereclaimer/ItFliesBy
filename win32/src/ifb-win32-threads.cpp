#pragma once

#include "ifb-win32.hpp"

ifb_internal const IFBB8
ifb_win32::thread_create(
    IFBThread* ptr_thread) {
    
    if (!ptr_thread) return(false);

    return(false);
}

ifb_internal const IFBB8
ifb_win32::thread_destroy(
    IFBThread* ptr_thread) {

    if (!ptr_thread) return(false);
    
    return(false);
}