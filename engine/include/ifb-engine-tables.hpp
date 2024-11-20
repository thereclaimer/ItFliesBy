#ifndef IFB_ENGINE_TABLES_HPP
#define IFB_ENGINE_TABLES_HPP

#include <ifb-common.hpp>

enum IFBEngineTableId_ {
    IFBEngineTableId_Tag            = 0,
    IFBEngineTableId_StackAllocator = 1,
    IFBEngineTableId_BlockAllocator = 2,
    IFBEngineTableId_Arena          = 3,
    IFBEngineTableId_ShaderProgram  = 4, 
    IFBEngineTableId_Count          = 5
};

typedef ifb_u32 IFBEngineTableId;

typedef ifb_index ifb_table_index_tag;
typedef ifb_index ifb_table_index_stack_allocator;
typedef ifb_index ifb_table_index_block_allocator;
typedef ifb_index ifb_table_index_arena;
typedef ifb_index ifb_table_index_shader_program;

#endif //IFB_ENGINE_TABLES_HPP