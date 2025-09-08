#pragma once

#include "ifb-engine-file-internal.hpp"

namespace ifb {
    
    IFB_ENG_FUNC void 
    eng_file_mngr_close(
        const eng_u32         count,
        const eng_h32_file_t* handle) {

        static eng_file_mngr_t& file_mngr = eng_file_mngr_instance();

        if (count > file_mngr.capacity || handle == NULL) return;

        for (
            eng_u32 index = 0;
            index < count;
            ++index) {

            
        }
    }

    IFB_ENG_FUNC void
    eng_file_mngr_open_ro(
        const eng_u32          in_count,
        const eng_file_path_t* in_path,
        eng_h32_file_t*        out_handle) {

        static eng_file_mngr_t& file_mngr = eng_file_mngr_instance();

        const bool is_valid = (
            in_count   <= file_mngr.capacity &&
            in_path    != NULL               &&
            out_handle != NULL 
        );

        if (!is_valid) return;

        static const sld::os_file_flags_t open_flags = (
            os_file_flag_e_async        |
            os_file_flag_e_read         |
            os_file_flag_e_share_read   |
            os_file_flag_e_share_write  |
            os_file_flag_e_share_delete |
            os_file_flag_e_overwrite
        );

        eng_u32 in_index = 0;
        for (
            eng_file_h32_t handle = {0};
            (handle.val <= file_mngr.capacity) && count_opened < in_count;
            ++handle.val) {

            // check if the current file handle is free
            const bool is_free = eng_file_mngr_is_file_free(handle);
            if (!is_free) continue;

            // get the current args
            eng_h32_file_t&        out_handle_current = out_handle [in_index]; 
            const eng_file_path_t& in_path_current    = in_path    [in_index];
            ++in_index;

            // get the data from the file manager
            eng_file_os_context_t& ref_file_mngr_os_context = eng_file_mngr_get_os_context (file_mngr, handle); 
            eng_error_s32_t&       ref_file_mngr_last_error = eng_file_mngr_get_last_error (file_mngr, handle);
            eng_mem_arena_t*&      ref_file_mngr_arena      = eng_file_mngr_get_arena      (file_mngr, handle);
            eng_file_buffer_t&     ref_file_mngr_buffer     = eng_file_mngr_get_buffer     (file_mngr, handle);

            // attempt to open the file
            ref_file_mngr_os_context.error = sld::os_file_open(
                ref_file_mngr_os_context.handle,
                (c8*)path.cstr,
                open_flags);

            // update the error code
            ref_file_mngr_last_error = eng_file_mngr_error_os_to_eng(file_mngr_os_context.error);
            if (ref_file_mngr_last_error != eng_file_e32_error_success) {
                continue;
            }

            // get an arena
            ref_file_mngr_arena = sld::arena_commit(file_mngr.reservation);

            ref_file_mngr_last_error = (ref_file_mngr_arena != NULL)
                ? eng_file_e32_error_success
                : eng_file_e32_error_arena_commit_fail;

            ref_file_mngr_buffer.data   = sld::arena_push_bytes(ref_file_mngr_arena, file_mngr.buffer_size);
            ref_file_mngr_buffer.length = 0; 
            ref_file_mngr_buffer.offset = 0;

            ref_file_mngr_last_error = (ref_file_mngr_buffer.data != NULL)
                ? eng_file_e32_error_success
                : eng_file_e32_error_buffer_alloc_fail;
        }
    }

    IFB_ENG_FUNC void
    eng_file_mngr_open_rw(
        const eng_u32          in_count,
        const eng_file_path_t* in_path,
        eng_h32_file_t*        out_handle) {

        static eng_file_mngr_t& file_mngr = eng_file_mngr_instance();

        const bool is_valid = (
            in_count   <= file_mngr.capacity &&
            in_path    != NULL               &&
            out_handle != NULL 
        );

        if (!is_valid) return;

        static const sld::os_file_flags_t open_flags = (
            os_file_flag_e_async        |
            os_file_flag_e_read         |
            os_file_flag_e_write        |
            os_file_flag_e_share_read   |
            os_file_flag_e_share_write  |
            os_file_flag_e_share_delete |
            os_file_flag_e_overwrite
        );

        eng_u32 in_index = 0;
        for (
            eng_file_h32_t handle = {0};
            (handle.val <= file_mngr.capacity) && count_opened < in_count;
            ++handle.val) {

            // check if the current file handle is free
            const bool is_free = eng_file_mngr_is_file_free(handle);
            if (!is_free) continue;

            // get the current args
            eng_h32_file_t&        out_handle_current = out_handle [in_index]; 
            const eng_file_path_t& in_path_current    = in_path    [in_index];
            ++in_index;

            // get the data from the file manager
            eng_file_os_context_t& ref_file_mngr_os_context = eng_file_mngr_get_os_context (file_mngr, handle); 
            eng_error_s32_t&       ref_file_mngr_last_error = eng_file_mngr_get_last_error (file_mngr, handle);
            eng_mem_arena_t*&      ref_file_mngr_arena      = eng_file_mngr_get_arena      (file_mngr, handle);
            eng_file_buffer_t&     ref_file_mngr_buffer     = eng_file_mngr_get_buffer     (file_mngr, handle);

            // attempt to open the file
            ref_file_mngr_os_context.error = sld::os_file_open(
                ref_file_mngr_os_context.handle,
                (c8*)path.cstr,
                open_flags);

            // update the error code
            ref_file_mngr_last_error = eng_file_mngr_error_os_to_eng(file_mngr_os_context.error);
            if (ref_file_mngr_last_error != eng_file_e32_error_success) {
                continue;
            }

            // get an arena
            ref_file_mngr_arena = sld::arena_commit(file_mngr.reservation);

            ref_file_mngr_last_error = (ref_file_mngr_arena != NULL)
                ? eng_file_e32_error_success
                : eng_file_e32_error_arena_commit_fail;

            ref_file_mngr_buffer.data   = sld::arena_push_bytes(ref_file_mngr_arena, file_mngr.buffer_size);
            ref_file_mngr_buffer.length = 0; 
            ref_file_mngr_buffer.offset = 0;

            ref_file_mngr_last_error = (ref_file_mngr_buffer.data != NULL)
                ? eng_file_e32_error_success
                : eng_file_e32_error_buffer_alloc_fail;
        }
    }

    IFB_ENG_FUNC void
    eng_file_mngr_get_size(
        const eng_u32_t       in_count,
        const eng_h32_file_t* in_handle,
        eng_u64*              out_size) {

        const bool args_valid = (
            in_count  != 0    &&
            in_handle != NULL &&
            out_size  != NULL            
        );

        if (!args_valid) return;

        static eng_file_mngr_t& file_mngr = eng_file_mngr_instance();

        for (
            eng_u32 index = 0;
            index < in_count;
            ++index) {
            
            eng_h32_file_t& ref_in_handle = in_handle [index];
            eng_u64&        ref_out_size  = out_size  [index];

            if (ref_in_handle.val >= file_mngr.capacity) continue;

            const eng_file_os_context_t& file_mngr_os_context = eng_file_mngr_get_os_context (file_mngr, ref_in_handle);
            const eng_error_s32_t&       file_mngr_last_error = eng_file_mngr_get_last_error (file_mngr, ref_in_handle);

            file_mngr_os_context.error = sld::os_file_size             (file_mngr_os_context.handle, ref_out_size);
            file_mngr_last_error       = eng_file_mngr_error_os_to_eng (file_mngr_os_context.error);             
        }
    }

    IFB_ENG_FUNC void
    eng_file_mngr_get_buffer(
        const eng_u32         in_count,
        const eng_h32_file_t* in_handle,
        eng_file_buffer_t*    out_buffer) {

        const bool args_valid = (
            in_count    != 0    &&
            in_handle   != NULL &&
            out_buffer  != NULL            
        );

        if (!args_valid) return;

        static eng_file_mngr_t& file_mngr = eng_file_mngr_instance();

        for (
            eng_u32 index = 0;
            index < in_count;
            ++index) {
            
            eng_h32_file_t&    ref_in_handle  = in_handle  [index];
            eng_file_buffer_t& ref_out_buffer = out_buffer [index];

            if (ref_in_handle.val >= file_mngr.capacity) continue;

            ref_out_buffer = eng_file_mngr_get_buffer(file_mngr, ref_in_handle);
        }
    }

    IFB_ENG_FUNC void
    eng_file_mngr_get_flags(
        const eng_u32_t       in_count,
        const eng_h32_file_t* in_handle,
        eng_file_u32_flags_t* out_flags) {

        const bool args_valid = (
            in_count    != 0    &&
            in_handle   != NULL &&
            out_buffer  != NULL            
        );

        if (!args_valid) return;

        static eng_file_mngr_t& file_mngr = eng_file_mngr_instance();

        for (
            eng_u32 index = 0;
            index < in_count;
            ++index) {
            
            eng_h32_file_t&       ref_in_handle  = in_handle [index];
            eng_file_u32_flags_t& ref_out_flags =  out_flags [index];

            if (ref_in_handle.val >= file_mngr.capacity) continue;

            ref_out_flags = eng_file_mngr_get_flags(file_mngr, ref_in_handle);
        }
    }

    IFB_ENG_FUNC void
    eng_file_mngr_read(
        const eng_u32_t        count,
        const eng_h32_file_t*  handle) {

    }

    IFB_ENG_FUNC void
    eng_file_mngr_write(
        const eng_u32_t          count,
        const eng_h32_file_t*    handle) {

    }

    IFB_ENG_INLINE const eng_error_s32_t
    eng_file_mngr_error_os_to_eng(
        const eng_file_os_error_t os_error) {

        constexpr eng_error_s32_t os_error_map[] = {
            { eng_file_e32_error_success             }, // os_file_error_e_success
            { eng_file_e32_error_unknown             }, // os_file_error_e_unknown
            { eng_file_e32_error_invalid_args        }, // os_file_error_e_invalid_args
            { eng_file_e32_error_invalid_handle      }, // os_file_error_e_invalid_handle
            { eng_file_e32_error_invalid_disk        }, // os_file_error_e_invalid_disk
            { eng_file_e32_error_invalid_device      }, // os_file_error_e_invalid_device
            { eng_file_e32_error_invalid_buffer      }, // os_file_error_e_invalid_buffer
            { eng_file_e32_error_invalid_file        }, // os_file_error_e_invalid_file
            { eng_file_e32_error_sharing_violation   }, // os_file_error_e_sharing_violation
            { eng_file_e32_error_already_exists      }, // os_file_error_e_already_exists
            { eng_file_e32_error_not_found           }, // os_file_error_e_not_found
            { eng_file_e32_error_access_denied       }, // os_file_error_e_access_denied
            { eng_file_e32_error_pipe_busy           }, // os_file_error_e_pipe_busy
            { eng_file_e32_error_reached_end_of_file }, // os_file_error_e_reached_end_of_file
            { eng_file_e32_error_broken_pipe         }, // os_file_error_e_broken_pipe
            { eng_file_e32_error_no_data             }, // os_file_error_e_no_data
            { eng_file_e32_error_more_data           }, // os_file_error_e_more_data
            { eng_file_e32_error_io_incomplete       }, // os_file_error_e_io_incomplete
            { eng_file_e32_error_io_pending          }, // os_file_error_e_io_pending
            { eng_file_e32_error_operation_aborted   }, // os_file_error_e_operation_aborted
            { eng_file_e32_error_disk_io_failure     }, // os_file_error_e_disk_io_failure
            { eng_file_e32_error_disk_corrupt        }, // os_file_error_e_disk_corrupt
            { eng_file_e32_error_device_not_ready    }, // os_file_error_e_device_not_ready
            { eng_file_e32_error_out_of_memory       }, // os_file_error_e_out_of_memory
            { eng_file_e32_error_device_failure      }, // os_file_error_e_device_failure
        };

        constexpr eng_u32 os_error_map_count = sizeof(os_error_map) / sizeof(eng_error_s32_t);

        const eng_error_s32_t eng_error = (os_error.val < 0 || os_error.val > os_error_map_count)
            ? eng_file_e32_error_unknown
            : os_error_map[os_error.val];

        return(eng_error);
    }


    IFB_ENG_FUNC eng_void
    eng_file_mngr_async_callback_read(
        const eng_file_os_context_t* os_context) {

        static eng_file_mngr_t& file_mngr = eng_file_mngr_instance(); 
        
        const bool is_context_valid = (
            os_context             != NULL &&
            os_context->handle     != NULL &&
            os_context->eng_handle <  file_mngr.capacity
        );
        if (!is_context_valid) return;

        eng_error_s32_t& file_error = file_mngr.array.last_error[os_context->eng_handle];
        file_error = eng_file_mngr_error_os_to_eng(os_context->error);

        eng_file_u32_flags_t& flags = file_mngr.array.flags [os_context->eng_handle]; 
        flags &= ~(eng_file_e32_flag_pending);
        flags &= ~(eng_file_e32_flag_rw);
        flags &= (file_error == eng_file_e32_error_success)
            ? eng_file_e32_flag_io_complete
            : eng_file_e32_flag_error; 
    }

    IFB_ENG_INLINE eng_void
    eng_file_mngr_async_callback_read(
        const eng_file_os_context_t* async_context) {

        static eng_file_mngr_t& file_mngr = eng_file_mngr_instance(); 
        
        const bool is_context_valid = (
            os_context             != NULL &&
            os_context->handle     != NULL &&
            os_context->eng_handle <  file_mngr.capacity
        );
        if (!is_context_valid) return;

        eng_error_s32_t& file_error = file_mngr.array.last_error[os_context->eng_handle];
        file_error = eng_file_mngr_error_os_to_eng(os_context->error);

        eng_file_u32_flags_t& flags = file_mngr.array.flags [os_context->eng_handle]; 
        flags &= ~(eng_file_e32_flag_pending);
        flags &= ~(eng_file_e32_flag_read);
        flags &= (file_error == eng_file_e32_error_success)
            ? eng_file_e32_flag_io_complete
            : eng_file_e32_flag_error; 
    }

    IFB_ENG_INLINE eng_file_mngr_t&
    eng_file_mngr_instance(
        void) {

        // static arrays
        static eng_file_os_context_t os_context [IFB_ENG_FILE_TABLE_CAPACITY];
        static eng_mem_arena_t*      arena      [IFB_ENG_FILE_TABLE_CAPACITY];
        static eng_file_path_t       path       [IFB_ENG_FILE_TABLE_CAPACITY];
        static eng_error_s32_t       last_error [IFB_ENG_FILE_TABLE_CAPACITY];
        static eng_file_u32_flags_t  flags      [IFB_ENG_FILE_TABLE_CAPACITY];
        static eng_file_buffer_t     buffer     [IFB_ENG_FILE_TABLE_CAPACITY];
 
        // file manager
        static eng_file_mngr_t file_mngr;    
        static eng_bool        initialized = false;
        if (!initialized) {
            
            sld::memory_zero((eng_byte*)os_context, sizeof(os_context));
            sld::memory_zero((eng_byte*)arena,      sizeof(arena));
            sld::memory_zero((eng_byte*)path,       sizeof(path));
            sld::memory_zero((eng_byte*)last_error, sizeof(last_error));
            sld::memory_zero((eng_byte*)flags,      sizeof(flags));
            sld::memory_zero((eng_byte*)buffer,     sizeof(buffer));

            file_mngr.reservation       = eng_mem_mngr_get_res_file();
            file_mngr.os_callback_read  = eng_file_mngr_async_callback_read;
            file_mngr.os_callback_write = eng_file_mngr_async_callback_write;
            file_mngr.buffer_size       = sld::size_kilobytes(IFB_ENG_FILE_BUFFER_SIZE_KB);
            file_mngr.capacity          = IFB_ENG_FILE_TABLE_CAPACITY;
            file_mngr.array.os_context  = os_context;
            file_mngr.array.arena       = arena;
            file_mngr.array.path        = path; 
            file_mngr.array.last_error  = last_error; 
            file_mngr.array.flags       = flags;
            file_mngr.array.buffer      = buffer;
        };
        return(file_mngr);
    }

    IFB_ENG_INLINE eng_bool
    eng_file_mngr_is_file_free(
        const eng_file_h32_t file_handle) {

        static eng_file_mngr_t& file_mngr = eng_file_mngr_instance();
        
        bool is_free = true;
        is_free &= (file_mngr.array.arena      [file_handle]        == NULL);
        is_free &= (file_mngr.array.os_context [file_handle].handle == NULL);
        return(is_free);
    }

    IFB_ENG_INLINE eng_file_os_context_t&
    eng_file_mngr_get_os_context(
        const eng_file_mngr_t& file_mngr,
        const eng_file_h32_t handle) {

        return(file_mngr.array.os_context[handle.val]);
    }

    IFB_ENG_INLINE eng_mem_arena_t*&
    eng_file_mngr_get_arena(
        const eng_file_mngr_t& file_mngr,
        const eng_file_h32_t   handle) {

        return(file_mngr.array.arena[handle.val]);
    }

    IFB_ENG_INLINE eng_file_path_t&
    eng_file_mngr_get_path(
        const eng_file_mngr_t& file_mngr,
        const eng_file_h32_t   handle) {

        return(file_mngr.array.path[handle.val]);
    }

    IFB_ENG_INLINE eng_error_s32_t&
    eng_file_mngr_get_last_error(
        const eng_file_mngr_t& file_mngr,
        const eng_file_h32_t   handle) {

        return(file_mngr.array.last_error[handle.val]);
    }

    IFB_ENG_INLINE eng_file_u32_flags_t&
    eng_file_mngr_get_flags(
        const eng_file_mngr_t& file_mngr,
        const eng_file_h32_t   handle) {

        return(file_mngr.array.flags[handle.val]);
    }

    IFB_ENG_INLINE eng_file_buffer_t&
    eng_file_mngr_get_buffer(
        const eng_file_mngr_t& file_mngr,
        const eng_file_h32_t   handle) {

        return(file_mngr.array.buffer[handle.val]);
    }
};