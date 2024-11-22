#ifndef IFB_ENGINE_TABLES_HPP
#define IFB_ENGINE_TABLES_HPP

#include <ifb-common.hpp>

enum IFBEngineTableId_ {
    IFBEngineTableId_Tag            = 0,
    IFBEngineTableId_StackAllocator = 1,
    IFBEngineTableId_BlockAllocator = 2,
    IFBEngineTableId_Arena          = 3,
    IFBEngineTableId_ShaderProgram  = 4, 
    IFBEngineTableId_Stack          = 5,
    IFBEngineTableId_Block          = 6,
    IFBEngineTableId_Count          = 7
};

typedef ifb_u32 IFBEngineTableId;

struct IFBEngineTagId {
    ifb_index tag_table_index;    
};

struct IFBEngineStackAllocatorId {
    ifb_index stack_allocator_table_index;
};

struct IFBEngineArenaId {
    ifb_index arena_table_index;
};

#endif //IFB_ENGINE_TABLES_HPP