#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::memory_arena_create_pool(
    const ifb_cstr                         in_arena_tag,
    const ifb_size                         in_arena_size,
    const ifb_size                         in_arena_count,
          IFBEngineMemoryArenaPoolHandle& out_arena_pool_handle_ref) {

    ifb_b8 result = true;
    
    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //create the header
    const ifb_u32 arena_header_index = ifb_engine::memory_arena_header_create(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.reservation,
        in_arena_tag,
        in_arena_size,
        in_arena_count);

    //create the batch of arenas
    const ifb_u32 starting_arena_detail_index = 
    ifb_engine::memory_arena_detail_table_insert(
        memory_manager_ref.arena_tables.detail,
        arena_header_index,
        in_arena_count);

    //initialize the struct
    out_arena_pool_handle_ref.header_index       = arena_header_index;
    out_arena_pool_handle_ref.detail_start_index = starting_arena_detail_index;

    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::memory_arena_commit(
    IFBEngineMemoryArenaPoolHandle& in_arena_pool_handle_ref,
    IFBEngineMemoryArenaHandle&    out_arena_handle_ref) {

    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //get the next available arena index
    ifb_b8 result = ifb_engine::memory_arena_detail_next_available_index(
        memory_manager_ref.arena_tables.detail,
        in_arena_pool_handle_ref.detail_start_index,
        in_arena_pool_handle_ref.header_index,
        out_arena_handle_ref.detail_index);

    //if no arena is available, we're done
    if (!result) {
        return(false);
    }

    //get the arena pages
    IFBEngineMemoryArenaPages arena_pages;
    ifb_engine::memory_arena_pages(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        out_arena_handle_ref,
        arena_pages);

    //commit the arena_memory
    const ifb_b8 commit_result = ifb_engine::memory_manager_page_commit(
        memory_manager_ref,
        arena_pages.page_number,
        arena_pages.page_count);

    //if that worked, set this arena as committed
    if (commit_result) {
        ifb_engine::memory_arena_detail_committed_set_true(
            memory_manager_ref.arena_tables.detail,
            out_arena_handle_ref.detail_index);
    }

    //we're done
    return(commit_result);
}

ifb_api const ifb_b8 
ifb_engine::memory_arena_decommit(
    IFBEngineMemoryArenaHandle& arena_ref) {

    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //validate the pre-committed arena
    IFBEngineMemoryArenaPages arena_pages;
    const ifb_b8 arena_valid = ifb_engine::memory_arena_validate_commit(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        arena_ref,
        arena_pages);

    if (!arena_valid) {
        return(false);
    }

    //decommit the memory
    const ifb_b8 result = ifb_engine::memory_manager_page_decommit(
        memory_manager_ref,
        arena_pages.page_number,
        arena_pages.page_count);

    //if that worked, update the arena detail
    if (result) {

        ifb_engine::memory_arena_detail_committed_set_false(
            memory_manager_ref.arena_tables.detail,
            arena_ref.detail_index);
    }

    //we're done
    return(result);
}

ifb_api const ifb_b8 
ifb_engine::memory_arena_push(
          IFBEngineMemoryArenaHandle& in_memory_arena_handle_ref, 
    const ifb_size                    in_memory_size,
          IFBEngineMemoryHandle&     out_memory_handle_ref) {

    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //validate the pre-committed arena
    IFBEngineMemoryArenaPages arena_pages;
    const ifb_b8 arena_valid = ifb_engine::memory_arena_validate_commit(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        in_memory_arena_handle_ref,
        arena_pages);

    //get the current used size
    const ifb_size arena_used_size_current = ifb_engine::memory_arena_detail_size_used(
        memory_manager_ref.arena_tables.detail,
        in_memory_arena_handle_ref.detail_index);

    //get the arena size
    const ifb_size arena_size_max = ifb_engine::memory_reservation_pages_size(
        memory_manager_ref.reservation,
        arena_pages.page_count);

    //make sure that the arena can fit this push
    const ifb_size arena_used_size_new = arena_used_size_current + in_memory_size;
    if (arena_used_size_new > arena_size_max) {
        
        //if we can't, we're done    
        return(false);
    }

    //add the push size to the detail table
    ifb_engine::memory_arena_detail_used_size_update(
        memory_manager_ref.arena_tables.detail,
        in_memory_arena_handle_ref.detail_index,
        arena_used_size_new);

    //initialize the struct
    out_memory_handle_ref.detail_index = in_memory_arena_handle_ref.detail_index;
    out_memory_handle_ref.page_number  = arena_pages.page_number;
    out_memory_handle_ref.page_offset  = arena_used_size_current;
    out_memory_handle_ref.size         = in_memory_size;

    //we're done
    return(true);
}

ifb_api const ifb_memory
ifb_engine::memory_arena_push_immediate(
          IFBEngineMemoryArenaHandle& memory_arena_handle_ref,
    const ifb_size                    memory_size) {
    
    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //validate the pre-committed arena
    IFBEngineMemoryArenaPages arena_pages;
    const ifb_b8 arena_valid = ifb_engine::memory_arena_validate_commit(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        memory_arena_handle_ref,
        arena_pages);

    //get the current used size
    const ifb_size arena_used_size_current = ifb_engine::memory_arena_detail_size_used(
        memory_manager_ref.arena_tables.detail,
        memory_arena_handle_ref.detail_index);

    //get the arena size
    const ifb_size arena_size_max = ifb_engine::memory_reservation_pages_size(
        memory_manager_ref.reservation,
        arena_pages.page_count);

    //make sure that the arena can fit this push
    const ifb_size arena_used_size_new = arena_used_size_current + memory_size;
    if (arena_used_size_new > arena_size_max) {
        
        //if we can't, we're done    
        return(false);
    }

    //add the push size to the detail table
    ifb_engine::memory_arena_detail_used_size_update(
        memory_manager_ref.arena_tables.detail,
        memory_arena_handle_ref.detail_index,
        arena_used_size_new);

    //get the pointer at this location in the arena
    const ifb_memory arena_pointer = ifb_engine::memory_reservation_get_pointer(
        memory_manager_ref.reservation,
        arena_pages.page_number,
        arena_used_size_new);

    //we're done
    return(arena_pointer);
}

ifb_api const ifb_b8 
ifb_engine::memory_arena_push_aligned(
          IFBEngineMemoryArenaHandle&  in_memory_arena_handle_ref, 
    const ifb_size                     in_memory_size, 
    const ifb_size                     in_memory_alignment,
          IFBEngineMemoryHandle&      out_memory_handle_ref) {
    
    //calculate the aligned push size
    const ifb_size push_size_aligned = ifb_engine_macro_align_a_to_b(
        in_memory_size,
        in_memory_alignment);

    //do the push 
    const ifb_b8 push_result = ifb_engine::memory_arena_push(
        in_memory_arena_handle_ref,
        push_size_aligned,
        out_memory_handle_ref);

    //we're done
    return(push_result);
}

ifb_api const ifb_memory 
ifb_engine::memory_arena_push_aligned_immediate(
          IFBEngineMemoryArenaHandle& memory_arena_handle_ref,
    const ifb_size                    memory_size,
    const ifb_size                    memory_alignment) {

    //calculate the aligned push size
    const ifb_size push_size_aligned = ifb_engine_macro_align_a_to_b(
        memory_size,
        memory_alignment);

    //do the push 
    const ifb_memory arena_pointer = ifb_engine::memory_arena_push_immediate(
        memory_arena_handle_ref,
        push_size_aligned);

    //we're done
    return(arena_pointer);
}

ifb_api const ifb_b8 
ifb_engine::memory_arena_pull(
          IFBEngineMemoryArenaHandle& in_memory_arena_handle_ref, 
    const ifb_size                    in_memory_size,
          IFBEngineMemoryHandle&     out_memory_handle_ref) {

    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //validate the pre-committed arena
    IFBEngineMemoryArenaPages arena_pages;
    const ifb_b8 arena_valid = ifb_engine::memory_arena_validate_commit(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        in_memory_arena_handle_ref,
        arena_pages);

    //if the arena is not valid or committed, we're done
    if (!arena_valid) {
        return(NULL);
    }
    
    //get the current used size
    const ifb_size arena_used_size_current = ifb_engine::memory_arena_detail_size_used(
        memory_manager_ref.arena_tables.detail,
        in_memory_arena_handle_ref.detail_index);

    //make sure we can do this pull
    if (arena_used_size_current < in_memory_size) {
        return(false);
    }

    //calculate the new used size
    const ifb_size arena_used_size_new = arena_used_size_current - in_memory_size;

    //update the arena detail table
    ifb_engine::memory_arena_detail_used_size_update(
        memory_manager_ref.arena_tables.detail,
        in_memory_arena_handle_ref.detail_index,
        arena_used_size_new);

    //initialize the struct
    out_memory_handle_ref.detail_index = in_memory_arena_handle_ref.detail_index;
    out_memory_handle_ref.page_number  = arena_pages.page_number;
    out_memory_handle_ref.page_offset  = arena_used_size_new;
    out_memory_handle_ref.size         = in_memory_size;

    //we're done
    return(true);
}

ifb_api const ifb_memory 
memory_arena_pull_immediate(
          IFBEngineMemoryArenaHandle& memory_arena_handle_ref, 
    const ifb_size                    memory_size) {
    

    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //validate the pre-committed arena
    IFBEngineMemoryArenaPages arena_pages;
    const ifb_b8 arena_valid = ifb_engine::memory_arena_validate_commit(
        memory_manager_ref.arena_tables.header,
        memory_manager_ref.arena_tables.detail,
        memory_arena_handle_ref,
        arena_pages);

    //if the arena is not valid or committed, we're done
    if (!arena_valid) {
        return(NULL);
    }
    
    //get the current used size
    const ifb_size arena_used_size_current = ifb_engine::memory_arena_detail_size_used(
        memory_manager_ref.arena_tables.detail,
        memory_arena_handle_ref.detail_index);

    //make sure we can do this pull
    if (arena_used_size_current < memory_size) {
        return(false);
    }

    //calculate the new used size
    const ifb_size arena_used_size_new = arena_used_size_current - memory_size;

    //update the arena detail table
    ifb_engine::memory_arena_detail_used_size_update(
        memory_manager_ref.arena_tables.detail,
        memory_arena_handle_ref.detail_index,
        arena_used_size_new);

    //get the pointer to this location in the arena
    const ifb_memory arena_pointer = ifb_engine::memory_reservation_get_pointer(
        memory_manager_ref.reservation,
        arena_pages.page_number,
        arena_used_size_new);

    //we're done
    return(arena_pointer);
}

ifb_api const ifb_b8 
ifb_engine::memory_arena_pull_aligned(
          IFBEngineMemoryArenaHandle&  in_memory_arena_handle_ref, 
    const ifb_size                     in_memory_size, 
    const ifb_size                     in_memory_alignment,
          IFBEngineMemoryHandle&      out_memory_handle_ref) {
    
    //calculate the aligned pull size
    const ifb_size pull_size_aligned = ifb_engine_macro_align_a_to_b(
        in_memory_size,
        in_memory_alignment);

    //do the pull
    const ifb_b8 pull_result = ifb_engine::memory_arena_pull(
        in_memory_arena_handle_ref,
        pull_size_aligned,
        out_memory_handle_ref);

    //we're done
    return(pull_result);
}

ifb_api const ifb_memory 
ifb_engine::memory_arena_pull_aligned_immediate(
          IFBEngineMemoryArenaHandle& memory_arena_handle_ref,
    const ifb_size                    memory_size,
    const ifb_size                    memory_alignment) {

    //calculate the aligned pull size
    const ifb_size pull_size_aligned = ifb_engine_macro_align_a_to_b(
        memory_size,
        memory_alignment);

    //do the pull
    const ifb_memory arena_memory = ifb_engine::memory_arena_pull_immediate(
        memory_arena_handle_ref,
        pull_size_aligned);

    //we're done
    return(arena_memory);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const ifb_b8
ifb_engine::memory_arena_validate(
    IFBEngineMemoryTableArenaHeader& arena_table_header_ref,
    IFBEngineMemoryArenaDetailTable& arena_table_detail_ref,
    IFBEngineMemoryArenaHandle&      arena_ref) {

    ifb_b8 arena_valid = true;

    //valid indexes
    arena_valid &= ifb_engine::memory_arena_detail_valid(arena_ref);
    
    //indexes fit in table
    arena_valid &= arena_ref.detail_index <= arena_table_detail_ref.arena_count_current;

    //we're done
    return(arena_valid);
}

inline const ifb_b8
ifb_engine::memory_arena_validate_commit(
    IFBEngineMemoryTableArenaHeader&    in_arena_table_header_ref,
    IFBEngineMemoryArenaDetailTable&    in_arena_table_detail_ref,
    IFBEngineMemoryArenaHandle&         in_arena_ref,
    IFBEngineMemoryArenaPages&         out_arena_pages) {

    //base validation
    ifb_b8 result = ifb_engine::memory_arena_validate(
        in_arena_table_header_ref,
        in_arena_table_detail_ref,
        in_arena_ref);
    
    //make sure the arena is committed
    result &= ifb_engine::memory_arena_detail_committed(
        in_arena_table_detail_ref,
        in_arena_ref.detail_index);
    
    //get the size and offset
    ifb_engine::memory_arena_pages(
        in_arena_table_header_ref,
        in_arena_table_detail_ref,
        in_arena_ref,
        out_arena_pages);

    //we're done
    return(result);
}

inline ifb_void
ifb_engine::memory_arena_pages(
    IFBEngineMemoryTableArenaHeader& in_arena_table_header_ref,
    IFBEngineMemoryArenaDetailTable& in_arena_table_detail_ref,        
    IFBEngineMemoryArenaHandle&      in_arena_handle_ref,
    IFBEngineMemoryArenaPages&      out_arena_pages_ref) {

    //get the header index
    const IFBEngineMemoryTableIndexArenaHeader arena_table_index_header = ifb_engine::memory_arena_detail_header_index(
        in_arena_table_detail_ref,
        in_arena_handle_ref.detail_index);

    //get the starting page number
    const ifb_u32 arena_header_page_start = ifb_engine::memory_arena_header_page_start(
        in_arena_table_header_ref,
        arena_table_index_header);

    //get the number of pages per arena
    const ifb_u32 arena_header_page_count = ifb_engine::memory_arena_header_arena_page_count(
        in_arena_table_header_ref,
        arena_table_index_header);

    //get the index of this arena in the pool
    const ifb_u32 arena_detail_pool_index = ifb_engine::memory_arena_detail_pool_index(
        in_arena_table_detail_ref,
        in_arena_handle_ref.detail_index);

    //the page number is the pages per arena times the pool index plus the starting index
    const ifb_u32 arena_page_offset = arena_header_page_count * arena_detail_pool_index; 
    const ifb_u32 arena_page_number = arena_header_page_start + arena_page_offset; 

    //initialize the strucf
    out_arena_pages_ref.page_number = arena_page_number;
    out_arena_pages_ref.page_count  = arena_header_page_count;
}