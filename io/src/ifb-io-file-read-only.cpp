#pragma once

#include "ifb-io.hpp"


const IFBB8
ifb_file_ro::file_open(
    const IFBFileReadOnlyRequest* request) {

    return(false);
}

const IFBB8
ifb_file_ro::file_close(
    const IFBFileReadOnlyRequest* request) {
    return(false);

}

const IFBB8
ifb_file_ro::file_read_immediate(
    const IFBFileReadOnlyRequest* request) {
    return(false);

}

const IFBB8
ifb_file_ro::file_read_async(
    const IFBFileReadOnlyRequest* request) {

    return(false);
}