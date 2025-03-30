#pragma once

#include <ifb-data-structures.hpp>

#include "ifb-threads.hpp"

const ifb::u32 
ifb_thread::memory_size_pool_args(
    void) {

    const ifb::u32 size = ifb_macro_align_size_struct(IFBThreadPoolArgs);
    return(size);
}

const ifb::u32
ifb_thread::memory_size_pool_sizes_cache(
    void){

    const ifb::u32 size = ifb_macro_align_size_struct(IFBThreadPoolSizesCache);
    return(size);
}