#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <sld.hpp>
#include <sld-buffer.hpp>
#include <sld-hash.hpp>
#include <sld-string.hpp>
#include <sld-xml.hpp>

#define IFB_ENG_API      __declspec(dllexport)
#define IFB_ENG_FUNC     static
#define IFB_ENG_INTERNAL static
#define IFB_ENG_INLINE   static inline

namespace ifb {

    //-------------------------------------------------------------------
    // PRIMITIVES
    //-------------------------------------------------------------------

    // signed integers
    typedef sld::s8  eng_s8;
    typedef sld::s16 eng_s16;
    typedef sld::s32 eng_s32;
    typedef sld::s64 eng_s64;

    // unsigned integers
    typedef sld::u8  eng_u8;
    typedef sld::u16 eng_u16;
    typedef sld::u32 eng_u32;
    typedef sld::u64 eng_u64;
    
    // floats
    typedef sld::f32 eng_f32;
    typedef sld::f64 eng_f64;
    
    // booleans
    typedef bool     eng_bool;
    typedef sld::b8  eng_b8;
    typedef sld::b16 eng_b16;
    typedef sld::b32 eng_b32;
    typedef sld::b64 eng_b64;

    // chars  
    typedef sld::c8  eng_c8;
    typedef sld::c16 eng_c16;
    typedef sld::c32 eng_c32;

    // memory
    typedef void       eng_void;
    typedef sld::byte  eng_byte;
    typedef sld::addr  eng_addr;
    typedef sld::vptr  eng_vptr;
    typedef sld::pad8  eng_pad8;
    typedef sld::pad16 eng_pad16;
    typedef sld::pad32 eng_pad32;
    typedef sld::pad64 eng_pad64;

    // structured
    typedef sld::s8_t   eng_s8_t;
    typedef sld::s16_t  eng_s16_t;
    typedef sld::s32_t  eng_s32_t;
    typedef sld::s64_t  eng_s64_t;
    typedef sld::u8_t   eng_u8_t;
    typedef sld::u16_t  eng_u16_t;
    typedef sld::u32_t  eng_u32_t;
    typedef sld::u64_t  eng_u64_t;
    typedef sld::f32_t  eng_f32_t;
    typedef sld::f64_t  eng_f64_t;
    typedef sld::b8_t   eng_b8_t;
    typedef sld::b16_t  eng_b16_t;
    typedef sld::b32_t  eng_b32_t;
    typedef sld::b64_t  eng_b64_t;
    typedef sld::c8_t   eng_c8_t;
    typedef sld::c16_t  eng_c16_t;
    typedef sld::c32_t  eng_c32_t;
    typedef sld::byte_t eng_byte_t;
    typedef sld::addr_t eng_addr_t;
    typedef sld::vptr_t eng_vptr_t;

    // handles
    struct eng_h8_t  : eng_u8_t  { };
    struct eng_h16_t : eng_u16_t { };
    struct eng_h32_t : eng_u32_t { };
    struct eng_h64_t : eng_u64_t { };

    //-------------------------------------------------------------------
    // ERROR
    //-------------------------------------------------------------------

    struct eng_error_s32_t : eng_s32_t { };

    enum eng_error_e32_type_ {
        eng_error_e32_type_success = 0x10000000,
        eng_error_e32_type_warning = 0x00000000,
        eng_error_e32_type_failure = 0x80000000,
    };

    enum eng_error_e32_module_ {
        eng_error_e32_module_platform = 0x00000000, 
        eng_error_e32_module_core     = 0x00010000, 
        eng_error_e32_module_memory   = 0x00020000, 
        eng_error_e32_module_file     = 0x00030000,
        eng_error_e32_module_file     = 0x00040000
    };

    //-------------------------------------------------------------------
    // STRINGS
    //-------------------------------------------------------------------
    
    typedef sld::cstr_t  eng_cstr_t;
    typedef sld::wstr_t eng_wstr_t;

    //-------------------------------------------------------------------
    // DATA STRUCTURES
    //-------------------------------------------------------------------
    
    typedef sld::buffer_t eng_buffer_t;

    //-------------------------------------------------------------------
    // DATA FORMATS
    //-------------------------------------------------------------------

    typedef sld::xml_hnd_doc_t    eng_xml_h32_doc_t;
    typedef sld::xml_hnd_node_t   eng_xml_h32_node_t;
    typedef sld::xml_hnd_attrib_t eng_xml_h32_attrib_t;

    //-------------------------------------------------------------------
    // API
    //-------------------------------------------------------------------

    IFB_ENG_API bool eng_init (void);

};

#endif //IFB_ENGINE_HPP