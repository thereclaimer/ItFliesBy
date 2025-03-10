#pragma once

#include "ifb-io.hpp"

#include <ifb-data-structures.hpp>

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

IFBFileReadOnly* 
ifb_file_ro::arena_load_pointer(
    const IFBHNDArena arena_handle,
    const IFBU32      arena_offset) {

    IFBFileReadOnly* file_pointer = (IFBFileReadOnly*)ifb_memory::arena_get_pointer(
        arena_handle,
        arena_offset);

    return(file_pointer);
}

IFBFileReadOnly* 
ifb_file_ro::arena_commit_absolute(
    const IFBHNDArena arena_handle,
    const IFBU32      platform_stack_size) {

    //commit the file
    const IFBU32     commit_size   = ifb_macro_align_size_struct(IFBFileReadOnly);
    IFBFileReadOnly* file_ptr      = ifb_memory::arena_commit_bytes_absolute(arena_handle,commit_size);
    ifb_macro_assert(file_ptr);

    //commit the platform stack
    file_ptr->platform_context_stack = ifb_stack::arena_commit_absolute(arena_handle,platform_stack_size);
    ifb_macro_assert(file_ptr->platform_context_stack);

    //we're done
    return(file_ptr);
}

const IFBU32     
ifb_file_ro::arena_commit_relative(
    const IFBHNDArena arena_handle,
    const IFBU32      platform_stack_size) {
    
    //commit the file
    const IFBU32 commit_size       = ifb_macro_align_size_struct(IFBFileReadOnly);
    const IFBU32 file_offset       = ifb_memory::arena_commit_bytes_relative(arena_handle,commit_size);
    const IFBB8  file_offset_valid = ifb_macro_hnd32_is_valid(file_offset);
    ifb_macro_assert(file_offset_valid); 

    //get the pointer
    IFBFileReadOnly* file_ptr = ifb_memory::arena_get_pointer(file_offset);
    ifb_macro_assert(file_ptr);

    //commit the stack
    file_ptr->platform_context_stack = ifb_stack::arena_commit_absolute(arena_handle,platform_stack_size);
    ifb_macro_assert(file_ptr->platform_context_stack);

    //we're done
    return(file_ptr);
}

/**********************************************************************************/
/* OPEN/CLOSE                                                                     */
/**********************************************************************************/

const IFBB8
ifb_file_ro::open(
          IFBFileReadOnly* file_read_only,
    const IFBChar*         file_path_cstr) {

}

const IFBB8
ifb_file_ro::close(
          IFBFileReadOnly* file_read_only,
    const IFBHNDArena       arena_handle,
    const IFBU32            read_offset) {

}

/**********************************************************************************/
/* READ                                                                           */
/**********************************************************************************/

const IFBB8
ifb_file_ro::read_immediate(
          IFBFileReadOnly* file_read_only,
    const IFBHNDArena      arena_handle,
    const IFBU32           read_offset) {

}

const IFBB8
ifb_file_ro::read_async(
          IFBFileReadOnly* file_read_only,
    const IFBHNDArena      arena_handle,
    const IFBU32           read_offset) {

}

