#pragma once

#include "ifb-threads.hpp"

#include "ifb-threads-pool-init.cpp"

using namespace ifb;
using namespace ifb::threads;

const b8
threads::pool_create(
    thread_pool_init_t* init) {
    
    ifb::b8 result = true;
    threads::pool_init_step_0_validate_args  (init,result);
    threads::pool_init_step_1_set_size_cache (init,result);
    threads::pool_init_step_2_cast_memory    (init,result);
    threads::pool_init_step_3_set_header     (init,result);
    threads::pool_init_step_4_set_handles    (init,result);
    threads::pool_init_step_5_validate_pool  (init,result);
    return(result);
}

const b8
threads::pool_destroy(
    const thread_pool_t* thread_pool) {

    return(false);
}