#pragma once

#include "ifb-win32.hpp"

ifb_internal const IFBB8
ifb_win32::system_get_info(
    IFBSystemInfo* system_info) {

    IFBB8 result = true;

    //static buffer for logical processor info
    //      NOTE(SAM): I pulled this number out of my ass
    //      I honestly don't know what the upper bound
    //      size of this buffer could be, but given
    //      we are just querying for a couple of numbers
    //      I don't expect this to be a wumbo size buffer
    const IFBU32 result_buffer_size = 4096;
    IFBByte      result_buffer[result_buffer_size];

    //get the win32 system info
    SYSTEM_INFO win32_sys_info;
    GetSystemInfo(&win32_sys_info);

    //memory info
    system_info->memory.page_size              = win32_sys_info.dwPageSize;
    system_info->memory.allocation_granularity = win32_sys_info.dwAllocationGranularity;

    //make sure the information we need will fit in the result buffer
    DWORD result_length;
    result &= GetLogicalProcessorInformationEx(RelationCache,NULL,&result_length);
    ifb_macro_assert(result_length <= result_buffer_size);

    //cast the result buffer to the thing win32 needs
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX processor_info_buffer  = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)result_buffer;

    //get the processor info
    result &= GetLogicalProcessorInformationEx(
        RelationCache,
        processor_info_buffer,
        &result_length);

    result &= result_length > 0;

    //because the win32 api isn't the best designed api, we need to 
    //iterate through the entire buffer of processor information
    //where the current info pointer will give us the size we need
    //to advance by
    //
    //do that until we get to the end of the buffer, or we hit the
    //max number of iterations we could reasonably expect

    const IFBU32 max_iterations  = 64;
    IFBU32 iteration_count       = 0;
    IFBU32 processor_info_offset = 0;

    //if we have an invalid result at this point, 
    //don't bother going any further
    IFBB8  advance_buffer = result;

    //advance through the buffer
    while (advance_buffer) {

        //get the current processor info
        PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX current_processor_info = 
            (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)(&result_buffer[processor_info_offset]);

        //if we have cache info, read it
        if (current_processor_info->Relationship == RelationCache) {

            CACHE_RELATIONSHIP& cache_info = current_processor_info->Cache;
            switch(cache_info.Level) {

                case 1: {
                    system_info->cpu.cache_l1.size_line  = cache_info.LineSize;
                    system_info->cpu.cache_l1.size_total = cache_info.CacheSize;
                } break;

                case 2: {
                    system_info->cpu.cache_l2.size_line  = cache_info.LineSize;
                    system_info->cpu.cache_l2.size_total = cache_info.CacheSize;
                } break;

                case 3: {
                    system_info->cpu.cache_l3.size_line  = cache_info.LineSize;
                    system_info->cpu.cache_l3.size_total = cache_info.CacheSize;
                } break;

                default: break;
            }
        }

        //update the iteration counter and offset
        ++iteration_count;
        processor_info_offset += current_processor_info->Size;

        //we will continue to advance if...
        advance_buffer &= (iteration_count < max_iterations);            //...we are below max iterations AND
        advance_buffer &= (processor_info_offset < result_length); //...we are within the buffer size 
    }

    //cpu info

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