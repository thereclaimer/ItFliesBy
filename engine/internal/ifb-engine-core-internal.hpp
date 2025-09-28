#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-memory-internal.hpp"

namespace ifb {

    constexpr eng_u32 ENG_CORE_XML_PARSER_SIZE = sld::size_megabytes(1);
    
    static eng_byte _eng_core_xml_parser_memory[ENG_CORE_XML_PARSER_SIZE];

    struct eng_core_static_memory_t {
        static inline sld::memory_t xml_parser = {(eng_addr)_eng_core_xml_parser_memory, ENG_CORE_XML_PARSER_SIZE};
    } static _eng_core_static_memory;

    struct eng_core_t {
        struct {
            eng_mem_arena_t* xml;
        } arenas;
    };

};