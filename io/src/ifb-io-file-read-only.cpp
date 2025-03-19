#pragma once

#include "ifb-io.hpp"


const IFBB8
ifb_file_ro::file_open(
    const IFBFileRequest* request) {

    return(false);
}

const IFBB8
ifb_file_ro::file_close(
    const IFBFileRequest* request) {
    return(false);

}

const IFBB8
ifb_file_ro::file_read_immediate(
    const IFBFileRequest* request) {
    return(false);

}

const IFBB8
ifb_file_ro::file_read_async(
    const IFBFileRequest* request) {

    return(false);
}