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
    u32 power_info_buffer_size_bytes = sizeof(Win32ProcessorPowerInformation) * cores_count;
    void* power_info_buffer = malloc(power_info_buffer_size_bytes);
    
    if (!power_info_buffer) {
        return(0);
    }

    NTSTATUS result = 
        CallNtPowerInformation(
            ProcessorInformation,
            NULL,
            0,
            power_info_buffer,
            power_info_buffer_size_bytes
    );

    if (result != 0) {
        free(power_info_buffer);
        return(0);
    }

    for (
        u32 processor_index = 0;
        processor_index < cores_count;
        ++processor_index) {

        Win32ProcessorPowerInformation processor_info = ((Win32ProcessorPowerInformation*)power_info_buffer)[processor_index];
        cpu_speed = processor_info.max_mhz > cpu_speed ? processor_info.max_mhz : cpu_speed;
    }

    free(power_info_buffer);

    return(cpu_speed);
}

internal u32
itfliesby_guesstimater_cores_count_get() {

    SYSTEM_INFO system_info = {0};

    GetSystemInfo(&system_info);

    return(system_info.dwNumberOfProcessors);
}

internal void
itfliesby_guesstimater_frame_cycles_get(
    ItfliesbyGuesstimaterFrameCycles* frame_cycles,
    u32                               speed_mhz) {

    frame_cycles->cycles_per_frame_fps_030 = (u32)(speed_mhz / 30)  * 1000000;
    frame_cycles->cycles_per_frame_fps_060 = (u32)(speed_mhz / 60)  * 1000000;
    frame_cycles->cycles_per_frame_fps_120 = (u32)(speed_mhz / 120) * 1000000;
    frame_cycles->cycles_per_frame_fps_240 = (u32)(speed_mhz / 240) * 1000000;
}

internal s32
itfliesby_guesstimater_main(
    HINSTANCE instance,
    HINSTANCE prev_isntance,
    PWSTR     cmd_line,
    int       cmd_show) {

    ItfliesbyGuesstimater guesstimater = {0};

    //get processor info
    ItfliesbyGuesstimaterProcessorInfo* processor_info = &guesstimater.processor_info;
    processor_info->cache_line_size_bytes = itfliesby_guesstimater_cache_line_size_get();
    processor_info->cores_count           = itfliesby_guesstimater_cores_count_get();
    processor_info->speed_mhz             = itfliesby_guesstimater_cpu_speed_get(processor_info->cores_count);

    //get our theoretical speeds
    ItfliesbyGuesstimaterFrameCycles* frame_cycles_theoretical = &guesstimater.frame_cycles_theoretical;
    itfliesby_guesstimater_frame_cycles_get(
        frame_cycles_theoretical,
        processor_info->speed_mhz
    );

    return(0);
}