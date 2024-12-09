#pragma once

#include "ifb-engine-internal-managers.hpp"

inline const IFBEngineGlobalHandleArenaManager 
ifb_engine::arena_manager_create(
          IFBEngineMemory* ptr_engine_memory,
    const ifb_u32          arena_minimum_size,
    const ifb_u32          arena_count_max) {

}

inline const IFBArenaId 
ifb_engine::arena_manager_create_arena(
          IFBEngineArenaManager* ptr_arena_manager, 
    const IFBCommitId            arena_commit_id,
    const IFBTagId               arena_tag_id) {

}

inline const ifb_u32
ifb_engine::arena_manager_align_size_to_arena(
          IFBEngineArenaManager* ptr_arena_manager, 
    const IFBEngineMemory*       ptr_engine_memory, 
    const ifb_u32                size) {

}

inline const IFBCommitId
ifb_engine::arena_manager_get_arena_commit_id(
          IFBEngineArenaManager* ptr_arena_manager, 
    const IFBEngineMemory*       ptr_engine_memory, 
    const IFBArenaId             arena_id) {

}

inline const IFBTagId
ifb_engine::arena_manager_get_arena_tag_id(
          IFBEngineArenaManager* ptr_arena_manager, 
    const IFBEngineMemory*       ptr_engine_memory, 
    const IFBArenaId             arena_id) {

}

inline IFBCommitId*
ifb_engine::arena_manager_get_pointer_commit_id_array(
          IFBEngineArenaManager* ptr_arena_manager, 
    const IFBEngineMemory*       ptr_engine_memory) {

}

inline IFBTagId*
ifb_engine::arena_manager_get_pointer_tag_id_array(
          IFBEngineArenaManager* ptr_arena_manager, 
    const IFBEngineMemory*       ptr_engine_memory) {

}