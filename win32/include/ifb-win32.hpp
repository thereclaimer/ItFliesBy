#ifndef IFB_WIN32_HPP
#define IFB_WIN32_HPP

#include <r-libs.hpp>
#include <ifb-engine.hpp>

struct IFBWin32 {
    RMemoryReservationHandle memory_reservation;
    RMemoryRegionHandle      win32_region;
};

#define ifb_win32_main r_win32_main

#endif //IFB_WIN32_HPP