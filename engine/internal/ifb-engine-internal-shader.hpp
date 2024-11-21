#ifndef IFB_ENGINE_SHADER_HPP
#define IFB_ENGINE_SHADER_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef ifb_index ifb_index_shader_program_t;
typedef ifb_index ifb_index_shader_uniform_t;
typedef ifb_index ifb_index_shader_vertex_array_object_t;

struct IFBEngineShader {
    ifb_index_shader_program_t program_index;
};

/**********************************************************************************/
/* SHADER STAGE                                                                   */
/**********************************************************************************/

enum IFBEngineShaderStageType_ {
    IFBEngineShaderStageType_Vertex   = 0,
    IFBEngineShaderStageType_Fragment = 1,
    IFBEngineShaderStageType_Count    = 2,
};

typedef ifb_u32 IFBEngineShaderStageType;


/**********************************************************************************/
/* SHADER PROGRAM                                                                 */
/**********************************************************************************/

union IFBEngineShaderProgramTableHandles {
    struct {
        ifb_handle_memory handle_table;
        ifb_handle_memory handle_column_gl_program;
        ifb_handle_memory handle_column_gl_stage_vertex;
        ifb_handle_memory handle_column_gl_stage_fragment;
        ifb_handle_memory handle_column_gl_vertex_array;
    };
    ifb_handle_memory array[5];
};


struct IFBEngineShaderProgramTable {
    ifb_u32 count_total;
    ifb_u32 count_used;
    union {
        struct {
            GLuint* gl_program;
            GLuint* gl_stage_vertex;
            GLuint* gl_stage_fragment;
            GLuint* gl_vertex_array;
        };
    } column_ptrs;
};

/**********************************************************************************/
/* SHADER MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineShaderManager {
    struct {
        IFBEngineShaderProgramTableHandles program;
    } table_handles;
};

#endif //IFB_ENGINE_SHADER_HPP