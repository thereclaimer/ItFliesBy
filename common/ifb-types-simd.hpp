#ifndef IFB_TYPES_SIMD_HPP
#define IFB_TYPES_SIMD_HPP

#include <xmmintrin.h>

#include "ifb-types-primitives.hpp"

#if _MSC_VER
    #if !defined(__clang__)
        #define INSTRUCTION_REORDER_BARRIER _ReadWriteBarrier()
    #endif //!defined(__clang__)
    #include <intrin.h>
#else //_MSC_VER
    #include <x86intrin.h>
#endif //_MSC_VER

typedef __m128 IFBXMMF128;


#endif //IFB_TYPES_SIMD_HPP