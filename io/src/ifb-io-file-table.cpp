#pragma once

#include "ifb-io.hpp"

#include "ifb-io-file-table-initialization.cpp"

/**********************************************************************************/
/* READ ONLY                                                                      */
/**********************************************************************************/

const IFBHNDFileTable 
ifb_file_table::commit_read_only(const IFBFileTableArgs* args) {

    //create our initalization struct
    IFBFileTableReadOnlyInit init;
    init.args          = (IFBFileTableArgs*)args;
    init.sizes         = NULL;
    init.table         = NULL;
    init.handle.offset = 0;

    //file table initialization steps
    ifb_file_table::read_only_init_step_0_validate_args      (init);
    ifb_file_table::read_only_init_step_1_reserve_size_cache (init);
    ifb_file_table::read_only_init_step_2_commit_table       (init);
    ifb_file_table::read_only_init_step_3_set_table_header   (init);
    ifb_file_table::read_only_init_step_4_set_table_handles  (init);
    ifb_file_table::read_only_init_step_5_set_table_lists    (init);
    ifb_file_table::read_only_init_step_6_set_table_contexts (init);
    ifb_file_table::read_only_init_step_7_release_size_cache (init);

    //we're done
    return(init.handle);
} 