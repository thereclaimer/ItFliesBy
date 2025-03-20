#pragma once

#include <ifb-data-structures.hpp>

#include "ifb-threads.hpp"

const IFBU32 
ifb_thread::memory_size_pool_args(
    IFBVoid) {

    const IFBU32 size = ifb_macro_align_size_struct(IFBThreadPoolArgs);
    return(size);
}

const IFBU32
ifb_thread::memory_size_pool_sizes_cache(
    IFBVoid){

    const IFBU32 size = ifb_macro_align_size_struct(IFBThreadPoolSizesCache);
    return(size);
}