#pragma once

#include <stdio.h>

#include "ifb-engine-internal-devtools.hpp"
#include "ifb-engine-internal-context.hpp"

inline ifb_void
ifb_engine::devtools_memory_render(
    IFBEngineDevToolsFlagsMemory& memory_flags_ref) {

    bool enabled = memory_flags_ref > IFBEngineDevToolsFlagsMemory_None; 

    if (!enabled || !ImGui::Begin("Memory",&enabled)) {
        return;
    }

    //get the memory reference
    IFBEngineMemory* context_memory_ptr = ifb_engine::context_get_memory();
    ifb_macro_assert(context_memory_ptr);

    if (ImGui::BeginTabBar("memory-tab-bar")) {

        //render the controls
        ifb_engine::devtools_memory_render_global_stack       (memory_flags_ref,context_memory_ptr);
        ifb_engine::devtools_memory_render_system_reservation (memory_flags_ref,context_memory_ptr);
        ifb_engine::devtools_memory_render_system_info        (memory_flags_ref,context_memory_ptr);

        ImGui::EndTabBar();
    }
    //if the window was closed, turn off the flags
    if (!enabled) {
        memory_flags_ref = IFBEngineDevToolsFlagsMemory_None;
    }

    ImGui::End();
}

inline ifb_void
ifb_engine::devtools_memory_render_global_stack(
    IFBEngineDevToolsFlagsMemory& memory_flags_ref,
    IFBEngineMemory*              engine_memory_ptr) {

    //get the flag, if its not enabled we're done
    bool enabled = ifb_engine::devtools_memory_flags_get_global_stack(memory_flags_ref);
    if (!enabled) return;

    //make sure our engine memory is valid
    ifb_macro_assert(engine_memory_ptr);

    if (ImGui::BeginTabItem("Global Stack",&enabled)) {

        IFBEngineDevToolsMemoryGlobalStack dev_global_stack;
        ifb_engine::devtools_memory_get_global_stack_info(
            dev_global_stack,
            engine_memory_ptr);

        const ifb_char* global_stack_table_name      = "global-stack-table";
        const ifb_u32   global_stack_table_row_count = 3;
        
        const ifb_char* global_stack_property_names[global_stack_table_row_count] = {
            dev_global_stack.names.size,
            dev_global_stack.names.position,
            dev_global_stack.names.percent            
        };

        const ifb_char* global_stack_property_values[global_stack_table_row_count] = {
            dev_global_stack.values.size,
            dev_global_stack.values.position,
            dev_global_stack.values.percent
        };

        ifb_engine::devtools_render_property_table(
            global_stack_table_name,
            global_stack_table_row_count,
            global_stack_property_names,
            global_stack_property_values);

        ImGui::EndTabItem();
    }

    //update the flag
    ifb_engine::devtools_memory_flags_set_global_stack(memory_flags_ref,enabled);
}

inline ifb_void
ifb_engine::devtools_memory_render_system_reservation(
    IFBEngineDevToolsFlagsMemory& memory_flags_ref,
    IFBEngineMemory*              engine_memory_ptr) {

    //get the flag, if its not enabled we're done
    bool enabled = ifb_engine::devtools_memory_flags_get_system_reservation(memory_flags_ref);
    if (!enabled) return;

    //make sure our engine memory is valid
    ifb_macro_assert(engine_memory_ptr);

    if (ImGui::BeginTabItem("System Reservation",&enabled)) {

        //get the system reservation properties
        IFBEngineDevToolsMemorySystemReservation dev_reservation_info;
        ifb_engine::devtools_memory_get_system_reservation_info(dev_reservation_info,engine_memory_ptr);

        const ifb_char* table_name      = "memory-reservation-table";
        const ifb_u32   table_row_count = 5;
        
        const ifb_char* table_property_names[table_row_count] = {
            dev_reservation_info.names.start,
            dev_reservation_info.names.page_count_total,
            dev_reservation_info.names.page_count_committed,
            dev_reservation_info.names.commit_count_max,
            dev_reservation_info.names.commit_count_current  
        };
        const ifb_char* table_property_values[table_row_count] = {
            dev_reservation_info.values.start,
            dev_reservation_info.values.page_count_total,
            dev_reservation_info.values.page_count_committed,
            dev_reservation_info.values.commit_count_max,
            dev_reservation_info.values.commit_count_current  
        };

        ifb_engine::devtools_render_property_table(
            table_name,
            table_row_count,
            table_property_names,
            table_property_values);

        ImGui::EndTabItem();
    }

    //update the flag
    ifb_engine::devtools_memory_flags_set_system_reservation(memory_flags_ref,enabled);
}

inline ifb_void
ifb_engine::devtools_memory_render_system_info(
    IFBEngineDevToolsFlagsMemory& memory_flags_ref,
    IFBEngineMemory*              engine_memory_ptr) {

    //get the flag, if its not enabled we're done
    bool enabled = ifb_engine::devtools_memory_flags_get_system_info(memory_flags_ref);
    if (!enabled) return;

    //make sure our engine memory is valid
    ifb_macro_assert(engine_memory_ptr);

    if (ImGui::BeginTabItem("System Info",&enabled)) {

        //get the system reservation properties
        IFBEngineDevToolsMemorySystemInfo dev_system_info;
        ifb_engine::devtools_memory_get_system_info(dev_system_info,engine_memory_ptr);

        const ifb_char* table_name      = "memory-sysinfo-table";
        const ifb_u32   table_row_count = 2;
        
        const ifb_char* table_property_names[table_row_count] = {
            dev_system_info.names.page_size,
            dev_system_info.names.allocation_granularity
        };
        const ifb_char* table_property_values[table_row_count] = {
            dev_system_info.values.page_size,
            dev_system_info.values.allocation_granularity
        };

        ifb_engine::devtools_render_property_table(
            table_name,
            table_row_count,
            table_property_names,
            table_property_values);

        ImGui::EndTabItem();
    }

    //update the flag
    ifb_engine::devtools_memory_flags_set_system_info(memory_flags_ref,enabled);
}

inline ifb_void 
ifb_engine::devtools_memory_get_global_stack_info(
    IFBEngineDevToolsMemoryGlobalStack& dev_global_stack_ref,
    IFBEngineMemory*                    engine_memory_ptr) {

    ifb_macro_assert(engine_memory_ptr);

    IFBEngineMemoryGlobalStack& global_stack_ref = engine_memory_ptr->global_stack;

    sprintf(dev_global_stack_ref.names.size,     "%s", "Stack Size");
    sprintf(dev_global_stack_ref.names.position, "%s", "Stack Position");
    sprintf(dev_global_stack_ref.names.percent,  "%s", "Percentage Used");

    const ifb_f32 stack_percent_used = 
        (ifb_f32)global_stack_ref.position /
        (ifb_f32)global_stack_ref.size;

    sprintf(dev_global_stack_ref.values.size,     "%d",     global_stack_ref.size);
    sprintf(dev_global_stack_ref.values.position, "%d",     global_stack_ref.position);
    sprintf(dev_global_stack_ref.values.percent,  "%.2f%%", stack_percent_used);
}

inline ifb_void
ifb_engine::devtools_memory_get_system_reservation_info(
    IFBEngineDevToolsMemorySystemReservation& dev_system_reservation_ref,
    IFBEngineMemory*                          engine_memory_ptr) {

    ifb_macro_assert(engine_memory_ptr);

    IFBEngineMemoryReservation& reservation_ref = engine_memory_ptr->reservation;

    sprintf(dev_system_reservation_ref.names.start,                "%s", "Starting Address");
    sprintf(dev_system_reservation_ref.names.page_count_total,     "%s", "Pages Total");
    sprintf(dev_system_reservation_ref.names.page_count_committed, "%s", "Pages Committed");
    sprintf(dev_system_reservation_ref.names.commit_count_max,     "%s", "Commit Count Max");
    sprintf(dev_system_reservation_ref.names.commit_count_current, "%s", "Commit Count Current");

    sprintf(dev_system_reservation_ref.values.start,                "%p", (void*)reservation_ref.start);
    sprintf(dev_system_reservation_ref.values.page_count_total,     "%d", reservation_ref.page_count_total);
    sprintf(dev_system_reservation_ref.values.page_count_committed, "%d", reservation_ref.page_count_committed);
    sprintf(dev_system_reservation_ref.values.commit_count_max,     "%d", reservation_ref.commit_count_max);
    sprintf(dev_system_reservation_ref.values.commit_count_current, "%d", reservation_ref.commit_count_current);
}

inline ifb_void
ifb_engine::devtools_memory_get_system_info(
    IFBEngineDevToolsMemorySystemInfo& dev_system_info_ref,
    IFBEngineMemory*                   engine_memory_ptr) {

    ifb_macro_assert(engine_memory_ptr);

    sprintf(dev_system_info_ref.names.page_size,              "%s", "Page Size");
    sprintf(dev_system_info_ref.names.allocation_granularity, "%s", "Allocation Granularity");
    
    sprintf(dev_system_info_ref.values.page_size,             "%d",engine_memory_ptr->system_info.page_size);
    sprintf(dev_system_info_ref.values.allocation_granularity,"%d",engine_memory_ptr->system_info.allocation_granularity);
}
