#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-reservation-init.cpp"

/**********************************************************************************/
/* MEMORY RESERVATION                                                             */
/**********************************************************************************/

const IFBB8
ifb_memory::reserve_system_memory(
          IFBMemoryReservationContext& reservation_context,
    const IFBU64                   size_reservation,
    const IFBU32                   size_arena) {

    //init struct
    IFBMemoryReservationInit init;
    init.args.context          = &reservation_context; 
    init.args.size_reservation = size_reservation; 
    init.args.size_arena       = size_arena; 

    //initialize the memory reservation
    ifb_memory::reservation_init_step_0_validate_args         (init);
    ifb_memory::reservation_init_step_1_get_system_info       (init);
    ifb_memory::reservation_init_step_3_calculate_sizes       (init);
    ifb_memory::reservation_init_step_2_allocate_reservation      (init);
    ifb_memory::reservation_init_step_4_reserve_system_memory (init);
    ifb_memory::reservation_init_step_5_set_properties        (init);
    ifb_memory::reservation_init_step_6_cleanup               (init);

    //we're done
    return(init.result ? true : false);
}

const IFBB8      
ifb_memory::release_system_memory(
    IFBMemoryReservationContext& reservation_context) {
    
    ifb_macro_panic();

    return(false);
}

inline IFBMemoryReservation*
ifb_memory::reservation_load_and_assert_valid(
    const IFBMEM64Stack       stack,
    const IFBMEM32Reservation reservation_handle) {

    //get the memory reservation
    IFBMemoryReservation* reservation = (IFBMemoryReservation*)ifb_memory::stack_get_pointer(
        stack,
        reservation_handle.h32);

    //assert memory reservation
    ifb_macro_assert(reservation);
    ifb_macro_assert(reservation->reserved_memory_start);
    ifb_macro_assert(reservation->count_arenas);
    ifb_macro_assert(reservation->size_arena);
    ifb_macro_assert(reservation->size_page);
    ifb_macro_assert(reservation->size_granularity);
    ifb_macro_assert(reservation->offset_arena_array_start);
    ifb_macro_assert(reservation->offset_arena_array_position);

    //we're done
    return(reservation);
}

inline IFBAddr*
ifb_memory::reservation_load_array_arena_start(
    IFBMemoryReservation* reservation) {

    const IFBU32  offset = reservation->offset_arena_array_start;
    const IFBAddr start  = (IFBAddr)reservation;
    
    IFBAddr* pointer = (IFBAddr*)ifb_memory::get_pointer(start,offset);

    return(pointer); 
}

inline IFBU32* 
ifb_memory::reservation_load_array_arena_position(
    IFBMemoryReservation* reservation) {

    const IFBU32  offset = reservation->offset_arena_array_position;
    const IFBAddr start  = (IFBAddr)reservation;
    
    IFBU32* pointer = (IFBU32*)ifb_memory::get_pointer(start,offset);

    return(pointer);
}

inline IFBVoid
ifb_memory::reservation_load_arrays(
    IFBMemoryReservation*       reservation,
    IFBMemoryReservationArrays* arrays) {

    //sanity check
    ifb_macro_assert(reservation);
    ifb_macro_assert(arrays);

    //addresses and offsets
    const IFBAddr start                 = (IFBAddr)reservation;
    const IFBU32  offset_array_start    = reservation->offset_arena_array_start;
    const IFBU32  offset_array_position = reservation->offset_arena_array_position;

    //get the arrays
    arrays->arena_start    = (IFBAddr*)ifb_memory::get_pointer(start, offset_array_start);
    arrays->arena_position =  (IFBU32*)ifb_memory::get_pointer(start, offset_array_position);
}
