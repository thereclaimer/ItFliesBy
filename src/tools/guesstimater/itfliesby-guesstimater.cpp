#pragma once

#include "itfliesby-guesstimater.hpp"

internal u32
itfliesby_guesstimater_cache_line_size_get() {

    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION win32_processor_info_buffer        = NULL;
    DWORD                                 win32_processor_info_buffer_length = 0;                                 

    //we call this the first time to get the length of the buffer
    GetLogicalProcessorInformation(NULL,&win32_processor_info_buffer_length);

    //allocate space for the info buffer
    win32_processor_info_buffer =  
        (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(win32_processor_info_buffer_length);
    
    if (!win32_processor_info_buffer) {
        return(0);
    }

    //get the number of processor infos
    u32 num_entries = win32_processor_info_buffer_length / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);

    //now get the actual processor info
    b8 processor_info_result = GetLogicalProcessorInformation(win32_processor_info_buffer,&win32_processor_info_buffer_length);
    if (!processor_info_result) {
        free(win32_processor_info_buffer);
        return(0);
    }

    SYSTEM_LOGICAL_PROCESSOR_INFORMATION processor_info_entry;
    s32 cache_line_bytes = 0;
    for (
        u32 index = 0;
        index < num_entries;
        ++index) {

        processor_info_entry = win32_processor_info_buffer[index];
        
        //save the largest cache line size, that is our target
        cache_line_bytes = 
            processor_info_entry.Cache.LineSize > cache_line_bytes
            ? processor_info_entry.Cache.LineSize
            : cache_line_bytes;
    }

    free(win32_processor_info_buffer);

    return(cache_line_bytes);
}

internal u32
itfliesby_guesstimater_cpu_speed_get(
    const u32 cores_count) {

    u32 cpu_speed = 0;

    Win32ProcessorPowerInformation* core_power_info = 
        (Win32ProcessorPowerInformation*)malloc(sizeof(Win32ProcessorPowerInformation) * cores_count);
    
     if (!core_power_info) {
        return(0);
    }


    u32 core_power_info_bytes = sizeof(Win32ProcessorPowerInformation) * cores_count;

    NTSTATUS result = 
        CallNtPowerInformation(
            ProcessorInformation,
            NULL,
            0,
            core_power_info,
            core_power_info_bytes
    );

    free(core_power_info);

    return(cpu_speed);
}

internal u32
itfliesby_guesstimater_cores_count_get() {

    SYSTEM_INFO system_info = {0};

    GetSystemInfo(&system_info);

    return(system_info.dwNumberOfProcessors);
}

internal s32
itfliesby_guesstimater_main(
    HINSTANCE instance,
    HINSTANCE prev_isntance,
    PWSTR     cmd_line,
    int       cmd_show) {

    ItfliesbyGuesstimater guesstimater = {0};

    //get processor info
    u32 cache_line_size = itfliesby_guesstimater_cache_line_size_get();
    u32 cores_count     = itfliesby_guesstimater_cores_count_get();
    u32 cpu_speed       = itfliesby_guesstimater_cpu_speed_get(cores_count);

    return(0);
}