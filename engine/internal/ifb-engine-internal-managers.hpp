#ifndef IFB_ENGINE_INTERNAL_MANAGERS_HPP
#define IFB_ENGINE_INTERNAL_MANAGERS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineGlobalHandleMemoryManager : IFBEngineGlobalHandle;
struct IFBEngineGlobalHandleTagManager    : IFBEngineGlobalHandle;
struct IFBEngineGlobalHandleArenaManager  : IFBEngineGlobalHandle;

struct IFBEngineMemoryManager;
struct IFBEngineTagManager;
struct IFBEngineArenaManager;

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_MANAGER_COMMIT_COUNT_MAX 128

struct IFBEngineMemoryManager {
    ifb_u32          page_size;
    ifb_u32          allocation_granularity;
    ifb_u32          count_pages_reserved;
    ifb_address      reservation_start;
    ifb_u32          commit_count_total;
    ifb_u32          commit_count_used;
    IFBEngineHandle  commit_array_handle; // IFBMemoryCommit
};

namespace ifb_engine {

    const IFBEngineGlobalHandleMemoryManager 
    memory_manager_create(
        const ifb_u32 memory_reservation_gigabyte_count,
        const ifb_u32 commit_count_max);

    const ifb_ptr memory_manager_reservation_pointer       (IFBEngineMemoryManager* ptr_memory_manager);
    const ifb_u32 memory_manager_size_reserved             (IFBEngineMemoryManager* ptr_memory_manager);
    const ifb_u32 memory_manager_size_committed            (IFBEngineMemoryManager* ptr_memory_manager);
    const ifb_u32 memory_manager_size_to_page_count        (IFBEngineMemoryManager* ptr_memory_manager, const ifb_u32 size);
    const ifb_u32 memory_manager_align_size_to_page        (IFBEngineMemoryManager* ptr_memory_manager, const ifb_u32 size);
    const ifb_u32 memory_manager_align_size_to_granularity (IFBEngineMemoryManager* ptr_memory_manager, const ifb_u32 size);

    const IFBMemoryCommitId  memory_manager_commit             (IFBEngineMemoryManager* ptr_memory_manager, const ifb_u32           size);
    const ifb_handle         memory_manager_get_commit_handle  (IFBEngineMemoryManager* ptr_memory_manager, const IFBMemoryCommitId commit_id);
    const ifb_u32            memory_manager_get_commit_size    (IFBEngineMemoryManager* ptr_memory_manager, const IFBMemoryCommitId commit_id);
          ifb_ptr            memory_manager_get_commit_pointer (IFBEngineMemoryManager* ptr_memory_manager, const IFBMemoryCommitId commit_id);
          ifb_ptr            memory_manager_get_commit_pointer (IFBEngineMemoryManager* ptr_memory_manager, const IFBMemoryCommitId commit_id, const ifb_u32 offset);
          ifb_ptr            memory_manager_get_pointer        (IFBEngineMemoryManager* ptr_memory_manager, const IFBEngineHandle&  ref_handle);
          IFBMemoryCommitId* memory_manager_get_commit_array   (IFBEngineMemoryManager* ptr_memory_manager);
};

/**********************************************************************************/
/* TAG MANAGER                                                                    */
/**********************************************************************************/

struct IFBEngineTagManager {
    ifb_u32 tag_c_str_length;
    ifb_u32 tag_count_max;
    struct {
        IFBEngineHandle char_buffer; // ifb_char
        IFBEngineHandle hash_array;  // IFBHash
    } handles;
};

namespace ifb_engine {

    const IFBEngineGlobalHandleTagManager 
    tag_manager_create(
        const ifb_u32 tag_c_str_length,
        const ifb_u32 tag_count_max);

    const IFBTagId  tag_manager_reserve_tag             (IFBEngineTagManager* ptr_tag_manager, const ifb_cstr tag_c_str);
          ifb_void  tag_manager_release_tag             (IFBEngineTagManager* ptr_tag_manager, const IFBTagId tag_id);
    const ifb_cstr  tag_manager_get_tag_c_str           (IFBEngineTagManager* ptr_tag_manager, const IFBTagId tag_id);
    const IFBHash   tag_manager_get_hash                (IFBEngineTagManager* ptr_tag_manager, const IFBTagId tag_id);
          ifb_char* tag_manager_get_pointer_char_buffer (IFBEngineTagManager* ptr_tag_manager);
          IFBHash*  tag_manager_get_pointer_hash_array  (IFBEngineTagManager* ptr_tag_manager);
};

/**********************************************************************************/
/* ARENA MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineArenaManager {
    ifb_u32 arena_minimum_size;
    ifb_u32 arena_minimum_pages;
    ifb_u32 arena_count_max;
    ifb_u32 arena_count_committed;
    struct {
        IFBEngineGlobalHandle commit_id_array; // IFBMemoryCommitId
        IFBEngineGlobalHandle tag_id_array;    // IFBTagId
    } global_handles;
};

namespace ifb_engine {

    const IFBEngineGlobalHandleArenaManager 
    arena_manager_create(
        const ifb_u32 arena_minimum_size,
        const ifb_u32 arena_count_max);

    const IFBArenaId 
    arena_manager_create_arena(
              IFBEngineArenaManager* ptr_arena_manager, 
        const IFBMemoryCommitId      arena_commit_id,
        const IFBTagId               arena_tag_id);

    const ifb_u32            arena_manager_align_size_to_arena         (IFBEngineArenaManager* ptr_arena_manager, const ifb_u32    size);
    const IFBMemoryCommitId  arena_manager_get_arena_commit_id         (IFBEngineArenaManager* ptr_arena_manager, const IFBArenaId arena_id);
    const IFBTagId           arena_manager_get_arena_tag_id            (IFBEngineArenaManager* ptr_arena_manager, const IFBArenaId arena_id);
          IFBMemoryCommitId* arena_manager_get_pointer_commit_id_array (IFBEngineArenaManager* ptr_arena_manager);
          IFBTagId*          arena_manager_get_pointer_tag_id_array    (IFBEngineArenaManager* ptr_arena_manager);
};

#endif //IFB_ENGINE_INTERNAL_MANAGERS_HPP