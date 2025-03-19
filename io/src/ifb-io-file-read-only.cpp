#pragma once

#include "ifb-io.hpp"


const IFBB8
ifb_file_ro::file_open(
    const IFBFileRequestReadOnly* request) {

    return(false);
}

const IFBB8
ifb_file_ro::file_close(
    const IFBFileRequestReadOnly* request) {
    return(false);

}

const IFBB8
ifb_file_ro::file_read_immediate(
    const IFBFileRequestReadOnly* request) {
    return(false);

}

const IFBB8
ifb_file_ro::file_read_async(
    const IFBFileRequestReadOnly* request) {

    return(false);
}