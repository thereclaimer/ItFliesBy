#ifndef IFB_STRING_HPP
#ifndef IFB_STRING_HPP

#include <ifb.hpp>
#include <ifb-memory.hpp>

struct IFBHNDStringC32;
struct IFBHNDStringC255;

struct IFBHNDStringW32;
struct IFBHNDStringW255;

namespace ifb_string {

    const IFBHNDStringC32 c32_reserve    (const IFBHNDArena, const IFBChar* c_str_buffer);
    const IFBChar*        c32_get_c_str  (const IFBHNDStringC32 string_32_handle);
    const IFBChar*        c32_get_length (const IFBHNDStringC32 string_32_handle);

};

#ifndef //IFB_STRING_HPP  