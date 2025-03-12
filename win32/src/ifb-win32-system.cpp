#pragma once

#include "ifb-win32.hpp"


ifb_internal const IFBB8
ifb_win32::system_get_info(
    IFBSystemInfo* system_info) {


    IFBB8 result = true;

    //sanity check
    if (!system_info) return(false);

    //buffer for logical processor info
    //
    // NOTE(SAM): I pulled this number out of my ass
    // I honestly don't know what the upper bound
    // size of this buffer could be, but given
    // we are just querying for a couple of numbers
    // I don't expect this to be a wumbo size buffer

    const IFBU32 result_buffer_size = 4096;
    IFBByte      result_buffer[result_buffer_size];

    //get the win32 system info and processor count
    SYSTEM_INFO win32_sys_info;
    GetSystemInfo(&win32_sys_info);
    const IFBU32 memory_page_size              = win32_sys_info.dwPageSize;
    const IFBU32 memory_allocation_granularity = win32_sys_info.dwAllocationGranularity;
    const IFBU32 parent_core_number            = GetCurrentProcessorNumber();

    //get the cpu speed from the registry
    IFBWin32RegKeyU32 reg_key_cpu_mhz;
    result &= ifb_win32::registry_key_read_value_cpu_speed_mhz(reg_key_cpu_mhz);

    //make sure the information we need will fit in the result buffer
    DWORD result_length = 0;
    GetLogicalProcessorInformationEx(RelationAll,NULL,&result_length);
    ifb_macro_assert(result_length <= result_buffer_size);

    //cast the result buffer to the thing win32 needs
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX processor_info_buffer  = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)result_buffer;

    //get the processor info
    result &= GetLogicalProcessorInformationEx(
        RelationAll,
        processor_info_buffer,
        &result_length);

    result &= result_length > 0;

    // because the win32 api isn't the best designed api, we need to 
    // iterate through the entire buffer of processor information
    // where the current info pointer will give us the size we need
    // to advance by
    // 
    // do that until we get to the end of the buffer, or we hit the
    // max number of iterations we could reasonably expect

    const IFBU32 max_iterations  = 64;
    IFBU32 iteration_count       = 0;
    IFBU32 processor_info_offset = 0;
    IFBU32 l1_cache_size, l2_cache_size, l3_cache_size = 0;
    IFBU32 l1_cache_line, l2_cache_line, l3_cache_line = 0;
    IFBU32 count_cores_physical = 0;
    IFBU32 count_cores_logical  = 0;

    //if we have an invalid result at this point, 
    //don't bother going any further
    IFBB8  advance_buffer = result;

    //advance through the buffer
    while (advance_buffer) {

        //get the current processor info
        PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX current_processor_info = 
            (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)(&result_buffer[processor_info_offset]);

        switch (current_processor_info->Relationship) {

            case (RelationProcessorCore): {

                //get the processor info
                PROCESSOR_RELATIONSHIP& processor_info = current_processor_info->Processor;

                //getting to this point means another physical core
                ++count_cores_physical;

                //the number of logical cores is in the group mask
                count_cores_logical += __popcnt(processor_info.GroupMask->Mask);

            } break;

            case(RelationCache): {

                //get the cache info                
                CACHE_RELATIONSHIP& cache_info = current_processor_info->Cache;
                
                switch(cache_info.Level) {

                    case 1: {
                        l1_cache_line = cache_info.LineSize;
                        l1_cache_size = cache_info.CacheSize;
                    } break;

                    case 2: {
                        l2_cache_line = cache_info.LineSize;
                        l2_cache_size = cache_info.CacheSize;
                    } break;

                    case 3: {
                        l3_cache_line = cache_info.LineSize;
                        l3_cache_size = cache_info.CacheSize;
                    } break;

                    default: break;
                }
            
            } break;
        }

        //update the iteration counter and offset
        ++iteration_count;
        processor_info_offset += current_processor_info->Size;

        //we will continue to advance if...
        advance_buffer &= (iteration_count < max_iterations);            //...we are below max iterations AND
        advance_buffer &= (processor_info_offset < result_length); //...we are within the buffer size 
    }

    //update system info
    system_info->memory.page_size              = memory_page_size;
    system_info->memory.allocation_granularity = memory_allocation_granularity;
    system_info->cpu.parent_core_number        = parent_core_number;
    system_info->cpu.core_count_logical        = count_cores_logical;
    system_info->cpu.core_count_physical       = count_cores_physical;
    system_info->cpu.cache_l1.size_total       = l1_cache_size;
    system_info->cpu.cache_l1.size_line        = l1_cache_line;
    system_info->cpu.cache_l2.size_total       = l2_cache_size;
    system_info->cpu.cache_l2.size_line        = l2_cache_line;
    system_info->cpu.cache_l3.size_total       = l3_cache_size;
    system_info->cpu.cache_l3.size_line        = l3_cache_line;

    //we're done
    return(result);
}

ifb_internal const IFBU64
ifb_win32::system_time_ms(
    IFBVoid) {

    ifb_macro_panic();
    return(0L);
}

ifb_internal IFBVoid 
ifb_win32::system_sleep(
    const IFBU32 ms) {

    ifb_macro_panic();
}

ifb_internal IFBVoid
ifb_win32::system_debug_out(
    const IFBChar* debug_string) {

    OutputDebugString(debug_string);
    OutputDebugString("\n");
}
