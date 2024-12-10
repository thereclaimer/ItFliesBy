#ifndef IFB_ENGINE_INTERNAL_MANAGERS_HPP
#define IFB_ENGINE_INTERNAL_MANAGERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineGlobalHandleTagManager       : IFBEngineGlobalHandle;
struct IFBEngineGlobalHandleArenaManager     : IFBEngineGlobalHandle;
struct IFBEngineGlobalHandleStackAllocators  : IFBEngineGlobalHandle;
struct IFBEngineGlobalHandleBlockAllocators  : IFBEngineGlobalHandle;
struct IFBEngineGlobalHandleAllocatorManager : IFBEngineGlobalHandle;

struct IFBEngineTagManager;
struct IFBEngineArenaManager;

/**********************************************************************************/
/* TAG MANAGER                                                                    */
/**********************************************************************************/

struct IFBEngineTagManager {
    IFBCommitId commit_id;
    ifb_u32     tag_c_str_length;
    ifb_u32     tag_count_max;
    struct {
        ifb_u32 char_buffer; // ifb_char
        ifb_u32 hash_array;  // IFBHash
    } commit_offsets;
};

namespace ifb_engine {

    const IFBEngineGlobalHandleTagManager 
    tag_manager_create(
              IFBEngineMemory* ptr_engine_memory,
        const ifb_u32          tag_c_str_length,
        const ifb_u32          tag_count_max);

    const IFBTagId  tag_manager_reserve_tag             (IFBEngineTagManager* ptr_tag_manager, const IFBEngineMemory* ptr_engine_memory, const ifb_cstr tag_c_str);
          ifb_void  tag_manager_release_tag             (IFBEngineTagManager* ptr_tag_manager, const IFBEngineMemory* ptr_engine_memory, const IFBTagId tag_id);
    const ifb_cstr  tag_manager_get_tag_c_str           (IFBEngineTagManager* ptr_tag_manager, const IFBEngineMemory* ptr_engine_memory, const IFBTagId tag_id);
    const IFBHash   tag_manager_get_hash                (IFBEngineTagManager* ptr_tag_manager, const IFBEngineMemory* ptr_engine_memory, const IFBTagId tag_id);
          ifb_char* tag_manager_get_pointer_char_buffer (IFBEngineTagManager* ptr_tag_manager, const IFBEngineMemory* ptr_engine_memory);
          IFBHash*  tag_manager_get_pointer_hash_array  (IFBEngineTagManager* ptr_tag_manager, const IFBEngineMemory* ptr_engine_memory);
};

/**********************************************************************************/
/* ARENA MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineArenaManager {
    IFBCommitId commit_id;
    ifb_u32     arena_minimum_size;
    ifb_u32     arena_minimum_pages;
    ifb_u32     arena_count_max;
    ifb_u32     arena_count_committed;
    struct {
        ifb_u32 commit_id_array; // IFBCommitId
        ifb_u32 tag_id_array;    // IFBTagId
    } commit_offsets;
};

namespace ifb_engine {

    const IFBEngineGlobalHandleArenaManager 
    arena_manager_create(
              IFBEngineMemory* ptr_engine_memory,
        const ifb_u32          arena_minimum_size,
        const ifb_u32          arena_count_max);

    const IFBArenaId 
    arena_manager_commit_arena(
              IFBEngineArenaManager* ptr_arena_manager, 
        const IFBEngineMemory*       ptr_engine_memory,
        const IFBTagId               arena_tag_id,
        const ifb_u32                arena_commit_size_minimum);

    const ifb_u32      arena_manager_align_size_to_arena         (IFBEngineArenaManager* ptr_arena_manager, const ifb_u32 size);
    const IFBCommitId  arena_manager_get_arena_commit_id         (IFBEngineArenaManager* ptr_arena_manager, const IFBEngineMemory* ptr_engine_memory, const IFBArenaId arena_id);
    const IFBTagId     arena_manager_get_arena_tag_id            (IFBEngineArenaManager* ptr_arena_manager, const IFBEngineMemory* ptr_engine_memory, const IFBArenaId arena_id);
    const ifb_u32      arena_manager_get_arena_size              (IFBEngineArenaManager* ptr_arena_manager, const IFBEngineMemory* ptr_engine_memory, const IFBArenaId arena_id);
    const ifb_u32      arena_manager_get_arena_pointer           (IFBEngineArenaManager* ptr_arena_manager, const IFBEngineMemory* ptr_engine_memory, const IFBArenaId arena_id);
    const ifb_u32      arena_manager_get_arena_pointer           (IFBEngineArenaManager* ptr_arena_manager, const IFBEngineMemory* ptr_engine_memory, const IFBArenaId arena_id, const ifb_u32 offset);
          IFBCommitId* arena_manager_get_pointer_commit_id_array (IFBEngineArenaManager* ptr_arena_manager, const IFBEngineMemory* ptr_engine_memory);
          IFBTagId*    arena_manager_get_pointer_tag_id_array    (IFBEngineArenaManager* ptr_arena_manager, const IFBEngineMemory* ptr_engine_memory);
};

/**********************************************************************************/
/* ALLOCATOR MANAGER                                                              */
/**********************************************************************************/

//-------------------
// linear allocator
//-------------------

struct IFBEngineLinearAllocatorInfo {
    ifb_u32    position;
    ifb_u32    save_point;
};

struct IFBEngineLinearAllocators {
    ifb_u32     count_max;
    ifb_u32     count_committed;
    struct {
        ifb_u32 arena_id;              // IFBArenaId
        ifb_u32 linear_allocator_info; // IFBEngineLinearAllocatorInfo 
    } commit_offsets;
};

//-------------------
// block allocator
//-------------------

struct IFBEngineBlockAllocatorInfo {
    ifb_u32      block_size;
    ifb_u32      block_count;
    ifb_address* block_addresses;
};

struct IFBEngineBlockAllocators {
    ifb_u32     count_max;
    ifb_u32     count_committed;
    struct {
        ifb_u32 arena_id;             // IFBArenaId
        ifb_u32 block_allocator_info; // IFBEngineBlockAllocatorInfo
        ifb_u32 block_addresses_ptr;  // ifb_address*
    } commit_offsets;
};

//-------------------
// allocator manager
//-------------------

struct IFBEngineAllocatorManager {
    IFBCommit commit_id;
    struct {
        ifb_u32 linear_allocators;
        ifb_u32 block_allocators;
    } commit_offsets;
};

namespace ifb_engine {

    //-------------------
    // allocator manager
    //-------------------

    const IFBEngineGlobalHandleAllocatorManager
    allocator_manager_create(
              IFBEngineMemory* ptr_engine_memory,
        const ifb_u32          stack_allocator_count_max,
        const ifb_u32          block_allocator_count_max);

    IFBEngineLinearAllocators* allocator_manager_get_pointer_linear_allocators (const IFBEngineAllocatorManager* ptr_allocator_manager, const IFBEngineMemory* ptr_engine_memory);
    IFBEngineBlockAllocators*  allocator_manager_get_pointer_block_allocators  (const IFBEngineAllocatorManager* ptr_allocator_manager, const IFBEngineMemory* ptr_engine_memory);

    //-------------------
    // linear allocator
    //-------------------

    const IFBLinearAllocatorId
    allocator_manager_commit_linear_allocator(
        const IFBEngineAllocatorManager* ptr_allocator_manager,
              IFBEngineMemory*           ptr_engine_memory,
        const IFBArenaId                 linear_allocator_arena_id);

    IFBArenaId* 
    allocator_manager_get_pointer_linear_allocator_arena_id_array(
        const IFBEngineAllocatorManager* ptr_allocator_manager,
        const IFBEngineLinearAllocators* ptr_linear_allocators,
        const IFBEngineMemory*           ptr_engine_memory);

    IFBEngineLinearAllocatorInfo* 
    allocator_manager_get_pointer_linear_allocator_info_array(
        const IFBEngineAllocatorManager* ptr_allocator_manager,
        const IFBEngineLinearAllocators* ptr_linear_allocators,
        const IFBEngineMemory*           ptr_engine_memory);


    //-------------------
    // block allocator
    //-------------------

    const IFBBlockAllocatorId
    allocator_manager_commit_block_allocator(
        const IFBEngineAllocatorManager* ptr_allocator_manager,
              IFBEngineMemory*           ptr_engine_memory,
        const IFBArenaId                 block_allocator_arena_id,
        const ifb_u32                    block_size_minimum,
        const ifb_u32                    block_count);

    IFBArenaId* 
    allocator_manager_get_pointer_block_allocator_arena_id_array(
        const IFBEngineAllocatorManager* ptr_allocator_manager,
        const IFBEngineBlockAllocators*  ptr_blcok_allocators,
        const IFBEngineMemory*           ptr_engine_memory);


    IFBEngineBlockAllocatorInfo* 
    allocator_manager_get_pointer_block_allocator_info_array(
        const IFBEngineAllocatorManager* ptr_allocator_manager,
        const IFBEngineBlockAllocators*  ptr_blcok_allocators,
        const IFBEngineMemory*           ptr_engine_memory);

    ifb_address** 
    allocator_manager_get_pointer_block_allocator_address_pointer_array(
        const IFBEngineAllocatorManager* ptr_allocator_manager,
        const IFBEngineBlockAllocators*  ptr_blcok_allocators,
        const IFBEngineMemory*           ptr_engine_memory);
}

#endif //IFB_ENGINE_INTERNAL_MANAGERS_HPP