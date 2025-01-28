#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

inline const IFBMemoryArenaHandle
ifb_memory::arena_commit(
          IFBMemory* memory_ptr,
    const ifb_u32    arena_size_minimum);

inline const IFBMemoryArenaHandle
ifb_memory::arena_commit(
          IFBMemory*                   memory_ptr,
    const IFBMemoryArenaCommitRequest& arena_commit_request_ref,
          IFBMemoryArenaCommitResult&  arena_commit_result_ref);

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

inline const ifb_b8 ifb_memory::arena_reset_all            (const IFBMemoryArenaId arena_id);
inline const ifb_b8 ifb_memory::arena_reset_allocators     (const IFBMemoryArenaId arena_id);
inline const ifb_b8 ifb_memory::arena_reset_scratch_space  (const IFBMemoryArenaId arena_id);

/**********************************************************************************/
/* PUSH / PULL                                                                    */
/**********************************************************************************/

inline const ifb_ptr ifb_memory::arena_scratch_push         (const IFBMemoryArenaId arena_id, const ifb_u32 size);
inline const ifb_ptr ifb_memory::arena_scratch_pull         (const IFBMemoryArenaId arena_id, const ifb_u32 size);
inline const ifb_ptr ifb_memory::arena_scratch_push_aligned (const IFBMemoryArenaId arena_id, const ifb_u32 size, const ifb_u32 alignment);
inline const ifb_ptr ifb_memory::arena_scratch_pull_aligned (const IFBMemoryArenaId arena_id, const ifb_u32 size, const ifb_u32 alignment);

/**********************************************************************************/
/* SIZE / COUNT                                                                   */
/**********************************************************************************/

inline const ifb_u32 ifb_memory::arena_get_page_count       (const IFBMemoryArenaId arena_id);
inline const ifb_u32 ifb_memory::arena_get_page_start       (const IFBMemoryArenaId arena_id);    
inline const ifb_u32 ifb_memory::arena_get_size_total       (const IFBMemoryArenaId arena_id);    
inline const ifb_u32 ifb_memory::arena_get_size_allocators  (const IFBMemoryArenaId arena_id);    
inline const ifb_u32 ifb_memory::arena_get_size_scratch     (const IFBMemoryArenaId arena_id);   