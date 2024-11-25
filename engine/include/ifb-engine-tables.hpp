#ifndef IFB_ENGINE_TABLES_HPP
#define IFB_ENGINE_TABLES_HPP

#include <ifb-common.hpp>

struct IFBEngineTableIndex {
    ifb_index row;
};

struct IFBEngineTableIndexTag   : IFBEngineTableIndex { };
struct IFBEngineTableIndexArena : IFBEngineTableIndex { };

#endif //IFB_ENGINE_TABLES_HPP