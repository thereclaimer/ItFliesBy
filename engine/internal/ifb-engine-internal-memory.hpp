#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_RESERVATION_SIZE_GIGABYTES 4

struct IFBEngineMemoryReservation {
    ifb_size   platform_allocation_granularity;
    ifb_size   platform_page_size;
    ifb_size   pages_total;
    ifb_size   pages_used;
    ifb_size   size;
    ifb_memory start;
};

namespace ifb_engine {

    const ifb_b8  memory_reserve               (IFBEngineMemoryReservation& reservation_ref);
    const ifb_b8  memory_release               (IFBEngineMemoryReservation& reservation_ref);
    const ifb_u32 memory_reservation_next_page (IFBEngineMemoryReservation& reservation_ref);
    
    const ifb_memory 
    memory_reservation_get_pointer (
              IFBEngineMemoryReservation& reservation_ref, 
        const ifb_u32                     page_number,
        const ifb_u32                     page_offset);

    const ifb_size
    memory_reservation_align_page_count(
              IFBEngineMemoryReservation& reservation_ref,
        const ifb_size                    size);

    const ifb_b8
    memory_reservation_add_pages(
              IFBEngineMemoryReservation& in_reservation_ref,
        const ifb_u32                     in_page_count,
              ifb_u32&                   out_page_start_ref);

};

/**********************************************************************************/
/* ARENA HEADER                                                                   */
/**********************************************************************************/

struct IFBEngineMemoryArenaHeader {
    ifb_u32  page_start;
    ifb_u32  arena_page_count;
    ifb_u32  arena_count;
    ifb_cstr tag;
};

struct IFBEngineMemoryTableRecordArenaHeader {
    IFBEngineMemoryTableIndexArenaHeader table_index_arena_header;
    IFBEngineMemoryArenaHeader           arena_header;
};

struct IFBEngineMemoryTableArenaHeader {
    ifb_u8   header_count_current;
    ifb_u8   header_count_max;
    ifb_char tag_buffer[IFB_ENGINE_MEMORY_ARENA_HEADER_TABLE_TAG_BUFFER_SIZE];
    struct {
        ifb_u32 page_start       [IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX];
        ifb_u32 arena_page_count [IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX];
        ifb_u32 arena_count      [IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX];
    } columns;
};

namespace ifb_engine {

    const ifb_b8 
    memory_arena_header_table_create(
        IFBEngineMemoryTableArenaHeader& arena_header_table_ref); 

    const IFBEngineMemoryTableIndexArenaHeader 
    memory_arena_header_create(
        const ifb_cstr                         arena_header_tag,
        const ifb_size                         arena_size,
        const ifb_size                         arena_count,
              IFBEngineMemoryReservation&      reservation_ref,
              IFBEngineMemoryTableArenaHeader& table_arena_header_ref);

    const ifb_size memory_arena_header_page_start       (IFBEngineMemoryTableArenaHeader& arena_table_header_ref, const IFBEngineMemoryTableIndexArenaHeader arena_header_index);
    const ifb_size memory_arena_header_arena_page_count (IFBEngineMemoryTableArenaHeader& arena_table_header_ref, const IFBEngineMemoryTableIndexArenaHeader arena_header_index);
    const ifb_size memory_arena_header_arena_count      (IFBEngineMemoryTableArenaHeader& arena_table_header_ref, const IFBEngineMemoryTableIndexArenaHeader arena_header_index);
};

/**********************************************************************************/
/* ARENA DETAIL                                                                    */
/**********************************************************************************/

struct IFBEngineMemoryArenaDetail {
    IFBEngineMemoryTableIndexArenaDetail memory_table_index_arena;
    ifb_size                             size_used;
    ifb_b8                               committed;
};

struct IFBEngineMemoryArenaDetailTable {
    ifb_u32 arena_count_current;
    ifb_u32 arena_count_max;
    ifb_u32 arena_minimum_size;
    struct {
        // TODO(SAM): I want to turn this array of booleans
        // to an array of bits
        ifb_b8  committed    [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_u8  header_index [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_u32 size_used    [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_u32 pool_index   [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
    } columns;
};

namespace ifb_engine {


    const IFBEngineMemoryTableIndexArenaDetail
    memory_arena_detail_table_insert(
        const IFBEngineMemoryTableIndexArenaHeader arena_header_index,
        const ifb_u32                              arena_count,
              IFBEngineMemoryArenaDetailTable&     arena_detail_table_ref);

    const IFBEngineMemoryTableIndexArenaDetail 
    memory_arena_detail_next_available_index(
              IFBEngineMemoryArenaDetailTable&     arena_detail_table_ref,
        const IFBEngineMemoryTableIndexArenaDetail arena_detail_index_start,
        const IFBEngineMemoryTableIndexArenaHeader arena_header_index);

    const ifb_b8                               memory_arena_detail_committed    (IFBEngineMemoryArenaDetailTable& arena_table_detail_ref, const IFBEngineMemoryTableIndexArenaDetail arena_detail_index);
    const IFBEngineMemoryTableIndexArenaHeader memory_arena_detail_header_index (IFBEngineMemoryArenaDetailTable& arena_table_detail_ref, const IFBEngineMemoryTableIndexArenaDetail arena_detail_index);
    const ifb_u32                              memory_arena_detail_size_used    (IFBEngineMemoryArenaDetailTable& arena_table_detail_ref, const IFBEngineMemoryTableIndexArenaDetail arena_detail_index);
    const ifb_index                            memory_arena_detail_pool_index   (IFBEngineMemoryArenaDetailTable& arena_table_detail_ref, const IFBEngineMemoryTableIndexArenaDetail arena_detail_index);

    const ifb_void memory_arena_detail_committed_set_true  (IFBEngineMemoryArenaDetailTable& arena_table_detail_ref, const IFBEngineMemoryTableIndexArenaDetail arena_detail_index);
    const ifb_void memory_arena_detail_committed_set_false (IFBEngineMemoryArenaDetailTable& arena_table_detail_ref, const IFBEngineMemoryTableIndexArenaDetail arena_detail_index);
    
    const ifb_void
    memory_arena_detail_used_size_update(
              IFBEngineMemoryArenaDetailTable&      arena_table_detail_ref, 
        const IFBEngineMemoryTableIndexArenaDetail  arena_detail_index,
        const ifb_size                              arena_used_size);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

struct IFBEngineMemoryArenaSizeAndOffset {
    ifb_size size; 
    ifb_size offset; 
};

namespace ifb_engine {

    const ifb_b8
    memory_arena_validate(
        IFBEngineMemoryTableArenaHeader& arena_table_header_ref,
        IFBEngineMemoryArenaDetailTable& arena_table_detail_ref,
        IFBEngineMemoryArenaHandle&      arena_handle_ref);

    const ifb_b8
    memory_arena_validate_commit(
        IFBEngineMemoryTableArenaHeader&    in_arena_table_header_ref,
        IFBEngineMemoryArenaDetailTable&    in_arena_table_detail_ref,
        IFBEngineMemoryArenaHandle&         in_arena_handle_ref,
        IFBEngineMemoryArenaSizeAndOffset& out_arena_size_and_offset_ref);

    const ifb_void
    memory_arena_size_and_offset(
        IFBEngineMemoryTableArenaHeader&    in_arena_table_header_ref,
        IFBEngineMemoryArenaDetailTable&    in_arena_table_detail_ref,        
        IFBEngineMemoryArenaHandle&         in_arena_handle_ref,
        IFBEngineMemoryArenaSizeAndOffset& out_arena_size_offset_ref);
};


/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineMemoryManager {
    IFBEngineMemoryReservation  reservation;
    struct {
        IFBEngineMemoryTableArenaHeader header;
        IFBEngineMemoryArenaDetailTable detail;
    } arena_tables;
};

namespace ifb_engine {

    ifb_internal const ifb_b8 memory_manager_start_up  (IFBEngineMemoryManager& memory_manager_ref);
    ifb_internal const ifb_b8 memory_manager_shut_down (IFBEngineMemoryManager& memory_manager_ref);

    ifb_internal const ifb_memory 
    memory_manager_page_commit(
              IFBEngineMemoryManager& memory_manager_ref,
        const ifb_size                page_size,
        const ifb_size                page_offset);

    ifb_internal const ifb_b8 
    memory_manager_page_decommit(
              IFBEngineMemoryManager& memory_manager_ref,
        const ifb_size                page_size,
        const ifb_size                page_offset);
};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP