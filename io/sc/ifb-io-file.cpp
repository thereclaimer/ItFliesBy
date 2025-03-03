#pragma once

#include "ifb-io.hpp"

/**********************************************************************************/
/* READ ONLY                                                                      */
/**********************************************************************************/

const IFBB8
ifb_file::open(
          IFBFileReadOnly* file_read_only,
    const IFBChar*         file_path_cstr) {

}
const IFBB8
ifb_file::read(
          IFBFileReadOnly* file_read_only,
    const IFBHNDArena      arena_handle,
    const IFBU32           offset) {

}

const IFBB8
ifb_file::close(
          IFBFileReadOnly* file_read_only,
    const IFBHNDArena       arena_handle,
    const IFBU32            offset) {

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