#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <r-libs.hpp>
#include <ifb-engine.hpp>

struct IFBWin32 {
    RHNDMemoryReservation memory_reservation;
    RHNDMemoryRegion      win32_region;
};

#define ifb_win32_main r_win32_main

#endif //IFB_WIN32_HPP