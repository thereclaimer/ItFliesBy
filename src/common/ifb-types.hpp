#ifndef IFB_TYPES_HPP
#define IFB_TYPES_HPP

#define internal static
#define local    static
#define global   static
#define external extern "C" __declspec(dllexport)
#define api      extern "C" __declspec(dllimport)
#define null     0

typedef char  s8;
typedef short s16;
typedef int   s32;
typedef long  s64;

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  u64;

typedef char* str;

typedef bool b8;

typedef float  f32;
typedef double f64;

typedef void* handle;

typedef u8    byte;
typedef byte* memory;

#endif //IFB_TYPES_HPP