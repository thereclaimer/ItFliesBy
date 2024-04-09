#pragma once

#include "itfliesby-guesstimater.hpp"

internal bool
itfliesby_guesstimater_processor_info_get(
    ItfliesbyGuesstimaterProcessorInfo* processor_info) {

    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION win32_processor_info_buffer        = NULL;
    DWORD                                 win32_processor_info_buffer_length = 0;                                 

    //we call this the first time to get the length of the buffer
    b8 processor_info_result = 
        GetLogicalProcessorInformation(
            win32_processor_info_buffer,
            &win32_processor_info_buffer_length);

    if (!processor_info_result) {
        return(false);
    }

    //allocate space for the info buffer
    win32_processor_info_buffer =  
        (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(win32_processor_info_buffer_length);
    
    if (!win32_processor_info_buffer) {
        return(false);
    }

    //get the number of processor infos
    u32 num_entries = win32_processor_info_buffer_length / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);

    //now get the actual processor info
    processor_info_result = 
        GetLogicalProcessorInformation(
            win32_processor_info_buffer,
            &win32_processor_info_buffer_length);

    SYSTEM_LOGICAL_PROCESSOR_INFORMATION processor_info_entry;
    for (
        u32 index = 0;
        index < num_entries;
        ++num_entries) {

        processor_info_entry = win32_processor_info_buffer[index];

        ITFLIESBY_NOP();

    }

    return(true);
}

internal s32
itfliesby_guesstimater_main(
    HINSTANCE instance,
    HINSTANCE prev_isntance,
    PWSTR     cmd_line,
    int       cmd_show) {

    ItfliesbyGuesstimater guesstimater = {0};

    //get processor info
    itfliesby_guesstimater_processor_info_get(&guesstimater.processor_info);

    return(0);
}