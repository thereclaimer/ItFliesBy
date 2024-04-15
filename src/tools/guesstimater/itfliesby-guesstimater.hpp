#ifndef ITFLIESBY_GUESSTIMATER_HPP
#define ITFLIESBY_GUESSTIMATER_HPP

/**
 * Guesstimator is a tool to calculate theoretical vs actual performance
 * characteristics of a system. It will not be 100% accurate, but we 
 * can make a best guess (aka guesstimate) on how to make the best
 * use of a cache line and how many cycles per frame we can use
 * 
*/

#include <itfliesby.hpp>

#include <Windows.h>
#include <stdio.h>
#include <powerbase.h>
#include <ntstatus.h>


#define itfliesby_guesstimater_main WINAPI wWinMain

struct Win32ProcessorPowerInformation {
  u64 Number;
  u64 MaxMhz;
  u64 CurrentMhz;
  u64 MhzLimit;
  u64 MaxIdleState;
  u64 CurrentIdleState;
};

struct ItfliesbyGuesstimaterProcessorInfo {
   u32 num_cores;
   u32 cache_line_bytes;
   u32 speed_mhz;
};

struct ItfliesbyGuesstimaterFrameCycles {
    u32 cycles_per_frame_030fps;
    u32 cycles_per_frame_060fps;
    u32 cycles_per_frame_120fps;
    u32 cycles_per_frame_240fps;
};

struct ItfliesbyGuesstimater {
    ItfliesbyGuesstimaterProcessorInfo processor_info;
    ItfliesbyGuesstimaterFrameCycles   frame_cycles_theoretical;
    ItfliesbyGuesstimaterFrameCycles   frame_cycles_actual;

};

#endif//ITFLIESBY_GUESSTIMATER_HPP