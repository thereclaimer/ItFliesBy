#pragma once

#include "ifb-io.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

#define IFB_FILE_TABLE_MAX_SIZE 0xFFFFFFFF

struct IFBFileTable;
struct IFBFile;

struct IFBFileArrayList : IFBDS64ArrayList { };

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

struct IFBFileTable {
    IFBU32 memory_size;
};
