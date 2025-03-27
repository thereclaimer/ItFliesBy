#pragma once

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//memory reservation
struct IFBMemoryReservation;
struct IFBMemoryReservationArrays;
struct IFBMemoryReservationInit;

//arena
struct IFBMemoryArenaCommit;
struct IFBMemoryArenaDecommit;
struct IFBMemoryArenaReset;
struct IFBMemoryArenaPushBytes;
struct IFBMemoryArenaPullBytes;

namespace ifb_memory {

    //reservation operations
    IFBMemoryReservation* reservation_load_and_assert_valid    (const IFBMEM64Stack stack_id, const IFBMEM32Reservation reservation_id);
    IFBAddr*          reservation_load_array_arena_start       (IFBMemoryReservation* reservation);
    IFBU32*           reservation_load_array_arena_position    (IFBMemoryReservation* reservation);
    IFBVoid           reservation_load_arrays                  (IFBMemoryReservation* reservation, IFBMemoryReservationArrays* arrays);

    //reservation init
    IFBVoid reservation_init_step_0_validate_args              (IFBMemoryReservationInit& init_ref);
    IFBVoid reservation_init_step_1_get_system_info            (IFBMemoryReservationInit& init_ref);
    IFBVoid reservation_init_step_3_calculate_sizes            (IFBMemoryReservationInit& init_ref);
    IFBVoid reservation_init_step_2_allocate_reservation       (IFBMemoryReservationInit& init_ref);
    IFBVoid reservation_init_step_4_reserve_system_memory      (IFBMemoryReservationInit& init_ref);
    IFBVoid reservation_init_step_5_set_properties             (IFBMemoryReservationInit& init_ref);
    IFBVoid reservation_init_step_6_cleanup                    (IFBMemoryReservationInit& init_ref);

    //arena commit
    IFBVoid arena_commit_step_0_validate_args                  (IFBMemoryArenaCommit& commit_ref);
    IFBVoid arena_commit_step_1_cache_reservation_properties   (IFBMemoryArenaCommit& commit_ref);
    IFBVoid arena_commit_step_2_find_free_arena                (IFBMemoryArenaCommit& commit_ref);
    IFBVoid arena_commit_step_3_commit_memory                  (IFBMemoryArenaCommit& commit_ref);
    IFBVoid arena_commit_step_4_update_arrays                  (IFBMemoryArenaCommit& commit_ref);

    //arena decommit
    IFBVoid arena_decommit_step_0_validate_args                (IFBMemoryArenaDecommit& decommit_ref);
    IFBVoid arena_decommit_step_1_cache_reservation_properties (IFBMemoryArenaDecommit& decommit_ref);
    IFBVoid arena_decommit_step_2_load_arena_start_array       (IFBMemoryArenaDecommit& decommit_ref);
    IFBVoid arena_decommit_step_3_decommit_memory              (IFBMemoryArenaDecommit& decommit_ref);
    IFBVoid arena_decommit_step_4_update_arena_start_array     (IFBMemoryArenaDecommit& decommit_ref);

    //arena reset
    IFBVoid arena_reset_step_0_validate_args                   (IFBMemoryArenaReset& reset_ref);
    IFBVoid arena_reset_step_1_cache_properties                (IFBMemoryArenaReset& reset_ref);
    IFBVoid arena_reset_step_2_reset_arena                     (IFBMemoryArenaReset& reset_ref);

    //arena push bytes
    IFBVoid arena_push_step_0_validate_args                    (IFBMemoryArenaPushBytes& push_ref);
    IFBVoid arena_push_step_1_cache_reservation_properties     (IFBMemoryArenaPushBytes& push_ref);
    IFBVoid arena_push_step_2_push_bytes_relative              (IFBMemoryArenaPushBytes& push_ref);
    IFBVoid arena_push_step_2_push_bytes_absolute              (IFBMemoryArenaPushBytes& push_ref);

    //arena reset
    IFBVoid arena_pull_step_0_validate_args                    (IFBMemoryArenaPullBytes& pull_ref);
    IFBVoid arena_pull_step_1_cache_properties                 (IFBMemoryArenaPullBytes& pull_ref);
    IFBVoid arena_pull_step_2_pull_bytes                       (IFBMemoryArenaPullBytes& pull_ref);
};

/**********************************************************************************/
/* MEMORY MANAGER DEFINITIONS                                                     */
/**********************************************************************************/

struct IFBMemoryReservation {
    IFBAddr reserved_memory_start;
    IFBU32  count_arenas;
    IFBU32  size_arena;
    IFBU32  size_page;
    IFBU32  size_granularity;
    IFBU32  offset_arena_array_start;
    IFBU32  offset_arena_array_position;
};

struct IFBMemoryReservationArrays {
    IFBAddr* arena_start;
    IFBU32*  arena_position;
};

struct IFBMemoryReservationInit {
    IFBB64                result;
    IFBMemoryReservation* reservation;
    IFBPtr                reserved_system_memory;
    IFBSystemMemoryInfo   sys_info;
    IFBMEM32Reservation   reservation_handle;
    struct {
        IFBMemoryReservationContext* context;
        IFBU64                   size_reservation;
        IFBU32                   size_arena;
    } args;
    struct {
        IFBU32  aligned_size_reservation;
        IFBU32  aligned_size_arena;
        IFBU32  count_arenas;
        IFBU32  commit_size_total;
        IFBU32  commit_size_reservation_struct;
        IFBU32  commit_size_array_arena_start;
        IFBU32  commit_size_array_arena_position;
        IFBByte padding[4];
    } cache;
};

/**********************************************************************************/
/* ARENA DEFINITIONS                                                              */
/**********************************************************************************/

struct IFBMemoryArenaCommit {
    IFBB64                 result;
    IFBMemoryArenaContext* context;
    struct {
        IFBMemoryReservationArrays arrays;
        IFBAddr                reservation_start;
        IFBAddr                arena_start;
        IFBU32                 arena_count;
        IFBU32                 arena_size;
    } cache;
};

struct IFBMemoryArenaDecommit {
    IFBB64                 result;
    IFBMemoryArenaContext* context;
    struct {
        IFBAddr* arena_start_array;
        IFBU32   arena_size;
        IFBU32   arena_count;
    } cache;
};

struct IFBMemoryArenaReset {
    IFBB64                 result;
    IFBMemoryArenaContext* context;
    struct {
        IFBU32* arena_position_array;
        IFBU64  arena_count;
    } cache; 
};

struct IFBMemoryArenaPushBytes {
    IFBB64                 result;
    IFBMemoryArenaContext* context;
    IFBU32                 push_size;
    struct {
        IFBMemoryReservationArrays arrays; 
        IFBU32                 arena_size;
        IFBU32                 arena_count;
    } cache;
    union {
        IFBPtr absolute_pointer;
        IFBU32 relative_offset;
    } memory;
};

struct IFBMemoryArenaPullBytes {
    IFBB64                 result;
    IFBMemoryArenaContext* context;
    struct {
        IFBU32* arena_position_array;
        IFBU64  arena_count;
    } cache; 
};
