#pragma once

#include "ifb-threads.hpp"

const IFBHNDThreadPool
ifb_thread::pool_create(
    const IFBThreadPoolArgs* args) {

    IFBHNDThreadPool handle;
    handle.offset = 0;
    return(handle);
}

const IFBB8
ifb_thread::pool_destroy(
    const IFBThreadPool* thread_pool) {

    return(false);
}