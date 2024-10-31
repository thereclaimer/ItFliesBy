#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* PLATFORM INFO                                                                  */
/**********************************************************************************/

struct IFBEngineMemoryPlatformInfo {
    ifb_size allocation_granularity;
    ifb_size page_size;
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_RESERVATION_SIZE_GIGABYTES 4

struct IFBEngineMemoryReservation {
    ifb_size   size_total;
    ifb_size   size_used;
    ifb_memory start;
};

namespace ifb_engine {

    ifb_internal const ifb_b8 memory_reserve (IFBEngineMemoryReservation& reservation_ref);
    ifb_internal const ifb_b8 memory_release (IFBEngineMemoryReservation& reservation_ref);

    inline const ifb_size
    memory_reservation_offset(
        IFBEngineMemoryReservation& reservation_ref) {

        const ifb_size reservation_offset = (ifb_address)reservation_ref.start - reservation_ref.size_used;

        return(reservation_offset);
    }
};

/**********************************************************************************/
/* ARENA HEADER                                                                   */
/**********************************************************************************/

struct IFBEngineMemoryArenaHeader {
    IFBEngineMemoryArenaHeaderIndex index;
    IFBEngineMemoryArenaDetailIndex starting_arena_detail_index;
    ifb_size                        offset;
    ifb_size                        arena_size;
    ifb_size                        arena_count;
    ifb_cstr                        tag;
};

struct IFBEngineMemoryArenaHeaderTable {
    ifb_u8   header_count_current;
    ifb_u8   header_count_max;
    ifb_char tag_buffer[IFB_ENGINE_MEMORY_ARENA_HEADER_TABLE_TAG_BUFFER_SIZE];
    struct {
        ifb_size array_arena_size [IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX];
        ifb_size array_arena_count[IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX];
        ifb_size array_offset     [IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX];
    } columns;
};

namespace ifb_engine {

    ifb_internal const ifb_b8 
    memory_arena_header_table_create(
        IFBEngineMemoryArenaHeaderTable& arena_header_table_ref); 

    ifb_internal const IFBEngineMemoryArenaHeaderIndex 
    memory_arena_header_create(
        const ifb_cstr                         in_arena_header_tag,
        const ifb_size                         in_arena_size,
        const ifb_size                         in_arena_count,
              IFBEngineMemoryReservation&      in_memory_reservation_ref,
              IFBEngineMemoryArenaHeaderTable& in_arena_table_header_ref);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

struct IFBEngineMemoryArenaDetail {
    IFBEngineMemoryArenaDetailIndex index;
    ifb_size                        size_used;
    ifb_b8                          committed;
};

struct IFBEngineMemoryArenaDetailTable {
    ifb_u32 arena_count_current;
    ifb_u32 arena_count_max;
    ifb_u32 arena_minimum_size;
    struct {
        // TODO(SAM): I want to turn this array of booleans
        // to an array of bits
        ifb_b8     array_committed    [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_u32    array_header_index [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_u32    array_size_used    [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_index array_pool_index    [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
    } columns;
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineMemoryManager {
    struct {
        IFBEngineMemoryArenaHeaderTable header;
        IFBEngineMemoryArenaDetailTable detail;
    } arena_tables;
    IFBEngineMemoryReservation  reservation;
    IFBEngineMemoryPlatformInfo platform_info;
};

namespace ifb_engine {

    ifb_internal const ifb_b8 memory_manager_start_up  (IFBEngineMemoryManager& memory_manager_ref);
    ifb_internal const ifb_b8 memory_manager_shut_down (IFBEngineMemoryManager& memory_manager_ref);
};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP