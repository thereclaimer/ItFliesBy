#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    const IFBByte* 
    singletons_buffer_get_pointer(
        const IFBEngineSingletonBuffer& singleton_buffer,
        const IFBHNDSingleton           singleton_handle);
};

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

inline IFBEngineSingletons*
ifb_engine::singletons_create(
    IFBEngineCore* ptr_core) {

    //sanity check
    ifb_macro_assert(ptr_core);
    
    //commmit the singletons structure
    IFBEngineSingletons* ptr_singletons = (IFBEngineSingletons*)ifb_engine::core_memory_commit_bytes_absolute(
        ptr_core,
        sizeof(IFBEngineSingletons),
        alignof(IFBEngineSingletons));

    ifb_macro_assert(ptr_singletons);

    //calculate all the singleton sizes
    const IFBU32 size_array[] = {
        ifb_macro_align_size_struct(IFBEngineConfig),
        ifb_macro_align_size_struct(IFBInput),
        ifb_macro_align_size_struct(IFBEngineDevTools),
        ifb_macro_align_size_struct(IFBEngineGraphics),
        ifb_macro_align_size_struct(IFBEngineRenderer)
    };
    
    //calculate the singleton count
    const IFBU32 singletons_count = ifb_macro_array_count(IFBU32,size_array); 

    //cast the singleton handles to an array
    IFBU16* singlegon_handles_array = (IFBU16*)&ptr_singletons->handles;
    IFBU16  buffer_position_u16 = 0;

    //calculate all the handles
    for (
        IFBU32 singleton_index = 0;
        singleton_index < singletons_count;
        ++singleton_index) {

        //get the current singleton size
        const IFBU32 singleton_size_u32 = size_array[singleton_index];

        //calculate the new buffer position
        const IFBU32 new_buffer_position_u32 = 
            singleton_size_u32 + buffer_position_u16;
    
        //sanity check
        ifb_macro_assert(singleton_size_u32      < IFB_ENGINE_SINGLETON_STACK_SIZE);
        ifb_macro_assert(new_buffer_position_u32 < IFB_ENGINE_SINGLETON_STACK_SIZE);

        //set the handle of the current singleton to the buffer position
        singlegon_handles_array[singleton_index] = buffer_position_u16;
        buffer_position_u16                      = (IFBU16)new_buffer_position_u32;
    }

    return(ptr_singletons);
}

/**********************************************************************************/
/* LOAD                                                                           */
/**********************************************************************************/

inline IFBEngineConfig*
ifb_engine::singletons_load_config(
    const IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //get the pointer
    IFBEngineConfig* ptr_config = (IFBEngineConfig*)ifb_engine::singletons_buffer_get_pointer(
            ptr_singletons->buffer,
            ptr_singletons->handles.config);

    //we're done
    return(ptr_config);
}

inline IFBInput*
ifb_engine::singletons_load_input(
    const IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //get the pointer
    IFBInput* ptr_input = (IFBInput*)ifb_engine::singletons_buffer_get_pointer(
            ptr_singletons->buffer,
            ptr_singletons->handles.input);

    //we're done
    return(ptr_input);
}

inline IFBEngineDevTools*
ifb_engine::singletons_load_devtools(
    const IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //get the pointer
    IFBEngineDevTools* ptr_devtools = (IFBEngineDevTools*)ifb_engine::singletons_buffer_get_pointer(
            ptr_singletons->buffer,
            ptr_singletons->handles.dev_tools);

    //we're done
    return(ptr_devtools);
}

inline IFBEngineGraphics*
ifb_engine::singletons_load_graphics(
    const IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //get the pointer
    IFBEngineGraphics* ptr_graphics = (IFBEngineGraphics*)ifb_engine::singletons_buffer_get_pointer(
            ptr_singletons->buffer,
            ptr_singletons->handles.graphics);

    //we're done
    return(ptr_graphics);
}

inline IFBEngineRenderer*
ifb_engine::singletons_load_renderer(
    const IFBEngineSingletons* ptr_singletons) {

    //sanity check
    ifb_macro_assert(ptr_singletons);
    
    //get the pointer
    IFBEngineRenderer* ptr_renderer = (IFBEngineRenderer*)ifb_engine::singletons_buffer_get_pointer(
            ptr_singletons->buffer,
            ptr_singletons->handles.renderer);

    //we're done
    return(ptr_renderer);
}


/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

inline const IFBByte* 
ifb_engine::singletons_buffer_get_pointer(
    const IFBEngineSingletonBuffer& singleton_buffer,
    const IFBHNDSingleton           singleton_handle) {

    const IFBByte* pointer = &singleton_buffer.memory[singleton_handle.offset];
    return(pointer);
}