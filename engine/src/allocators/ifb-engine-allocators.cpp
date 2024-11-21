#pragma once

#include "ifb-engine-allocator-stack.cpp"

inline ifb_void 
ifb_engine::allocator_tables_initialize(
    ifb_void) {

    IFBEngineTableStackAllocator stack_allocator_table;
    ifb_engine::table_stack_allocator(stack_allocator_table);

    ifb_engine::stack_allocator_table_initialize(stack_allocator_table);
}

