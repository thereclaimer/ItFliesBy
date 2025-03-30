#pragma once

#include "ifb-threads.hpp"

#include "ifb-threads-pool-init.cpp"

const ifb::b8
ifb_thread::pool_create(
    IFBThreadPoolInit* init) {
    
    ifb::b8 result = true;
    ifb_thread::pool_init_step_0_validate_args  (init,result);
    ifb_thread::pool_init_step_1_set_size_cache (init,result);
    ifb_thread::pool_init_step_2_cast_memory    (init,result);
    ifb_thread::pool_init_step_3_set_header     (init,result);
    ifb_thread::pool_init_step_4_set_handles    (init,result);
    ifb_thread::pool_init_step_5_validate_pool  (init,result);
    return(result);
}

const ifb::b8
ifb_thread::pool_destroy(
    const IFBThreadPool* thread_pool) {

    return(false);
}