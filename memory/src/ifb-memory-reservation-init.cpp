#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

/**********************************************************************************/
/* INITIALIZATION                                                                 */
/**********************************************************************************/

inline IFBVoid 
ifb_memory::reservation_init_step_0_validate_args(
    IFBMemoryReservationInit& init_ref) {
    
    init_ref.result =  true;    
    init_ref.result &= ifb_memory_macro_is_handle_valid_stack(init_ref.args.context->handle_stack); 
    init_ref.result &= (init_ref.args.size_reservation != NULL);
    init_ref.result &= (init_ref.args.size_arena       != NULL);
}

inline IFBVoid 
ifb_memory::reservation_init_step_1_get_system_info(
    IFBMemoryReservationInit& init_ref) {

    init_ref.result &= ifb_platform::system_get_info_memory(&init_ref.sys_info);
    init_ref.result &= init_ref.sys_info.allocation_granularity != 0;
    init_ref.result &= init_ref.sys_info.page_size              != 0;
}

inline IFBVoid 
ifb_memory::reservation_init_step_3_calculate_sizes(
    IFBMemoryReservationInit& init_ref) {
    
    if (init_ref.result) {

        //align the reservation size to the allocation granularity
        init_ref.cache.aligned_size_reservation = ifb_macro_align_a_to_b(
            init_ref.args.size_reservation,
            (IFBU64)init_ref.sys_info.allocation_granularity);

        //align the arena size to a page size
        init_ref.cache.aligned_size_arena = ifb_macro_align_a_to_b(
            (IFBU32)init_ref.args.size_arena,
            init_ref.sys_info.page_size);

        //page and arena counts
        init_ref.cache.count_arenas = init_ref.cache.aligned_size_reservation / init_ref.cache.aligned_size_arena;

        // TODO: the array to store this amount of information is HUGE for
        // reservations in the gigabyte range. This will definitely work,
        // but maybe later we come up with a better way to track arenas

        //property sizes    
        init_ref.cache.commit_size_reservation_struct   = ifb_macro_align_size_struct(IFBMemoryReservation);
        init_ref.cache.commit_size_array_arena_start    = sizeof(IFBAddr) * init_ref.cache.count_arenas;
        init_ref.cache.commit_size_array_arena_position = sizeof(IFBU32)  * init_ref.cache.count_arenas;
     
        //total commit size
        init_ref.cache.commit_size_total = 
            init_ref.cache.commit_size_reservation_struct    +
            init_ref.cache.commit_size_array_arena_start +
            init_ref.cache.commit_size_array_arena_position;

        //sanity check, make sure all sizes are non-zero
        init_ref.result &= (init_ref.cache.aligned_size_reservation         != 0);
        init_ref.result &= (init_ref.cache.aligned_size_arena               != 0);
        init_ref.result &= (init_ref.cache.count_arenas                     != 0);
        init_ref.result &= (init_ref.cache.commit_size_total                != 0);
        init_ref.result &= (init_ref.cache.commit_size_reservation_struct       != 0);
        init_ref.result &= (init_ref.cache.commit_size_array_arena_start    != 0);
        init_ref.result &= (init_ref.cache.commit_size_array_arena_position != 0);
    }
}

inline IFBVoid 
ifb_memory::reservation_init_step_2_allocate_reservation(
    IFBMemoryReservationInit& init_ref) {

    if (init_ref.result) {

        //do the stack commit
        init_ref.reservation = (IFBMemoryReservation*)ifb_memory::stack_push_bytes_absolute(
            init_ref.args.context->handle_stack,
            init_ref.cache.commit_size_total);

        //make sure we have the reservation
        init_ref.result &= (init_ref.reservation != NULL); 
    }
}

inline IFBVoid 
ifb_memory::reservation_init_step_4_reserve_system_memory(
    IFBMemoryReservationInit& init_ref) {

    if (init_ref.result) {

        //make the reservation
        init_ref.reserved_system_memory = ifb_platform::memory_reserve(
            init_ref.cache.aligned_size_reservation);

        //make sure we got it
        init_ref.result &= (init_ref.reserved_system_memory != NULL);
    }
}

inline IFBVoid 
ifb_memory::reservation_init_step_5_set_properties(
    IFBMemoryReservationInit& init_ref) {
        
    //set the properties
    init_ref.reservation->reserved_memory_start = (IFBAddr)init_ref.reservation;
    init_ref.reservation->count_arenas          = init_ref.cache.count_arenas;
    init_ref.reservation->size_arena            = init_ref.cache.aligned_size_arena;
    init_ref.reservation->size_page             = init_ref.sys_info.page_size;
    init_ref.reservation->size_granularity      = init_ref.sys_info.allocation_granularity;

    //offsets
    init_ref.reservation->offset_arena_array_start    = init_ref.cache.commit_size_reservation_struct;
    init_ref.reservation->offset_arena_array_position = init_ref.cache.commit_size_array_arena_start + init_ref.reservation->offset_arena_array_start; 

    //sanity check, make sure the properties are non-zero
    init_ref.result &= (init_ref.reservation->reserved_memory_start        != 0);
    init_ref.result &= (init_ref.reservation->count_arenas                 != 0);
    init_ref.result &= (init_ref.reservation->size_arena                   != 0);
    init_ref.result &= (init_ref.reservation->size_page                    != 0);
    init_ref.result &= (init_ref.reservation->size_granularity             != 0);
    init_ref.result &= (init_ref.reservation->offset_arena_array_start     != 0);
    init_ref.result &= (init_ref.reservation->offset_arena_array_position  != 0);
}

inline IFBVoid 
ifb_memory::reservation_init_step_6_cleanup(
    IFBMemoryReservationInit& init_ref) {

    //if we were not able to create the reservation,
    //we need to release any aquired memory
    const IFBB8 should_release_memory_reservation = (!init_ref.result && init_ref.reservation != NULL); 
    const IFBB8 should_release_memory_stack       = (!init_ref.result && init_ref.reservation     != NULL); 

    //platform memory
    if (should_release_memory_reservation) {

        //release the memory        
        const IFBB8 released = ifb_platform::memory_release(
            init_ref.reservation,
            init_ref.cache.aligned_size_reservation);

        //we should AlWAYS be able to release memory        
        ifb_macro_assert(released);
    }

    //stack memory
    if (should_release_memory_stack) {

        //release the memory
        const IFBB8 released = ifb_memory::stack_pull_bytes(
            init_ref.args.context->handle_stack,
            init_ref.cache.commit_size_total);

        //we should AlWAYS be able to release memory        
        ifb_macro_assert(released);
    }

    //make sure the reserved pointers are null
    init_ref.reservation     = NULL;
    init_ref.reservation = NULL;    
}