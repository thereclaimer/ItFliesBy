#pragma once

#include "ifb-io.hpp"

/**********************************************************************************/
/* READ ONLY                                                                      */
/**********************************************************************************/

IFBFileReadOnly* ifb_file_ro::arena_load_pointer    (const IFBHNDArena arena_handle, const IFBU32 arena_offset);
IFBFileReadOnly* ifb_file_ro::arena_commit_absolute (const IFBHNDArena arena_handle);
const IFBU32     ifb_file_ro::arena_commit_relative (const IFBHNDArena arena_handle);


const IFBB8
ifb_file_ro::open(
          IFBFileReadOnly* file_read_only,
    const IFBChar*         file_path_cstr) {

}
const IFBB8
ifb_file_ro::read(
          IFBFileReadOnly* file_read_only,
    const IFBHNDArena      arena_handle,
    const IFBU32           read_offset) {

}

const IFBB8
ifb_file_ro::close(
          IFBFileReadOnly* file_read_only,
    const IFBHNDArena       arena_handle,
    const IFBU32            read_offset) {

}

/**********************************************************************************/
/* READ WRITE                                                                     */
/**********************************************************************************/

const IFBB8
ifb_file::open(
          IFBFileReadWrite* file_read_only,
    const IFBChar*          file_path_cstr) {

}
const IFBB8
ifb_file::read(
          IFBFileReadWrite* file_read_only,
    const IFBHNDArena       arena_handle,
    const IFBU32            offset) {

}

const IFBB8
ifb_file::write(
          IFBFileReadWrite* file_read_only,
    const IFBHNDArena       arena_handle,
    const IFBU32            offset) {

}

const IFBB8
ifb_file::close(
          IFBFileReadWrite* file_read_only,
    const IFBHNDArena       arena_handle,
    const IFBU32            offset) {

}