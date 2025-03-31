#pragma once

#include <ifb-data-structures.hpp>

#include "ifb-threads.hpp"

using namespace ifb;
using namespace ifb::threads;

const u32 
threads::memory_size_pool_args(
    void) {

    const u32 size = ifb_macro_align_size_struct(thread_pool_args_t);
    return(size);
}

const u32
threads::memory_size_pool_sizes_cache(
    void){

    const u32 size = ifb_macro_align_size_struct(thread_pool_sizes_cache_t);
    return(size);
}