#pragma once

#include "ifb-graphics-internal.hpp"

const IFBHNDLinearAllocator
ifb_graphics::memory_get_linear_arena(IFBVoid) {

    IFBGraphicsMemory& ref_memory = ifb_graphics::context_get_memory();
    return(ref_memory.linear_arena_handle);
}

IFBGraphicsWindow*
ifb_graphics::memory_commit_window(
    IFBVoid) {

    IFBGraphicsMemory& ref_memory = ifb_graphics::context_get_memory();

    //do the commit
    const IFBU32 commit_size   = ifb_macro_align_size_struct(IFBGraphicsWindow);
    const IFBU32 commit_offset = ifb_memory::linear_arena_reserve_bytes_relative(
        ref_memory.linear_arena_handle,
        commit_size);
    
    //if that failed, we're done
    if (commit_offset == 0) return(NULL);

    //get the pointer
    IFBGraphicsWindow* ptr_window = (IFBGraphicsWindow*)ifb_memory::linear_arena_get_pointer_at_offset(
        ref_memory.linear_arena_handle,
        commit_offset);

    //we should always be able to get a pointer
    //to memory we just committed
    ifb_macro_assert(ptr_window);

    //set the handle
    ptr_window->handle.offset = commit_offset;

    //we're done
    return(ptr_window);
}

const IFBB8
ifb_graphics::memory_commit_window_lists(
    IFBVoid) {

    //get the memory
    IFBGraphicsMemory& ref_memory = ifb_graphics::context_get_memory();

    //calculate the commit size
    const IFBU32 window_list_size        = ifb_macro_align_size_struct(IFBGraphicsWindowList);
    const IFBU32 window_list_commit_size = window_list_size * 2; 

    //commit the memory
    const IFBU32 commit_offset = ifb_memory::linear_arena_reserve_bytes_relative(
        ref_memory.linear_arena_handle,
        window_list_commit_size);
    
    //if that failed, we're done
    if (commit_offset == 0) return(false);

    //update the handles
    ref_memory.offsets.window_list_active   = commit_offset;
    ref_memory.offsets.window_list_inactive = commit_offset + window_list_size;

    //we're done
    return(true);
}

IFBGraphicsWindow*
ifb_graphics::memory_get_window(
    const IFBHNDGraphicsWindow window_handle) {
    
    //get the memory
    IFBGraphicsMemory& ref_memory = ifb_graphics::context_get_memory();
    
    //sanity check
    if (window_handle.offset == 0) return(NULL);

    //get the pointer
    IFBGraphicsWindow* ptr_window = (IFBGraphicsWindow*)ifb_memory::linear_arena_get_pointer_at_offset(
        ref_memory.linear_arena_handle,
        window_handle.offset);

    //if we have an offset, we should always be able to get the pointer
    ifb_macro_assert(ptr_window);

    //we're done
    return(ptr_window);
}

IFBGraphicsWindowList*
ifb_graphics::memory_get_window_list_active(
    IFBVoid) {

    //get the memory
    IFBGraphicsMemory& ref_memory = ifb_graphics::context_get_memory();
 
    //get the offset, if there is one
    const IFBU32 list_offset = ref_memory.offsets.window_list_active;
    if (list_offset == 0) return (NULL);

    //get the pointer
    IFBGraphicsWindowList* ptr_list = (IFBGraphicsWindowList*)ifb_memory::linear_arena_get_pointer_at_offset(
        ref_memory.linear_arena_handle,
        list_offset);

    //we're done
    return(ptr_list);
}

IFBGraphicsWindowList*
ifb_graphics::memory_get_window_list_inactive(
    IFBVoid) {

    //get the memory
    IFBGraphicsMemory& ref_memory = ifb_graphics::context_get_memory();
 
    //get the offset, if there is one
    const IFBU32 list_offset = ref_memory.offsets.window_list_inactive;
    if (list_offset == 0) return (NULL);

    //get the pointer
    IFBGraphicsWindowList* ptr_list = (IFBGraphicsWindowList*)ifb_memory::linear_arena_get_pointer_at_offset(
        ref_memory.linear_arena_handle,
        list_offset);

    //we're done
    return(ptr_list);
}