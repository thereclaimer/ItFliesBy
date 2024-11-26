#ifndef IFB_ENGINE_TABLES_HPP
#define IFB_ENGINE_TABLES_HPP

#include <ifb-common.hpp>

struct IFBEngineTableIndex {
    ifb_index value;
};

struct IFBEngineTableIndexTag   { IFBEngineTableIndex index; };
struct IFBEngineTableIndexArena { IFBEngineTableIndex index; };

#endif //IFB_ENGINE_TABLES_HPP