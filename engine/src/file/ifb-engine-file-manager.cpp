#pragma once

#include <sld-memory.hpp>
#include "ifb-engine-file-internal.hpp"

namespace ifb {

    //-------------------------------------------------------------------
    // STATIC
    //-------------------------------------------------------------------

    static eng_file_mngr_t             _file_mngr;
    static eng_file_os_context_t       _os_context       [IFB_ENG_FILE_TABLE_CAPACITY];
    static eng_file_callback_context_t _callback_context [IFB_ENG_FILE_TABLE_CAPACITY];
    static eng_file_t                  _file             [IFB_ENG_FILE_TABLE_CAPACITY];
    static eng_c8                      _path_buffer      [IFB_ENG_FILE_TABLE_CAPACITY * IFB_ENG_FILE_PATH_SIZE];

    //-------------------------------------------------------------------
    // DECLARATIONS
    //-------------------------------------------------------------------
 
    eng_file_t*           eng_file_mngr_get_next_closed      (void);
    eng_file_t*           eng_file_mngr_get_next_open        (void);
    void                  eng_file_mngr_add_closed           (eng_file_t* file);
    void                  eng_file_mngr_add_open             (eng_file_t* file);
    eng_void              eng_file_mngr_async_callback_read  (const eng_void* data, const eng_file_os_error_t error, const eng_u32 bytes_transferred);
    eng_void              eng_file_mngr_async_callback_write (const eng_void* data, const eng_file_os_error_t error, const eng_u32 bytes_transferred);
    const eng_error_s32_t eng_file_mngr_error_os_to_eng      (const eng_file_os_error_t    os_error);  

    //-------------------------------------------------------------------
    // API
    //-------------------------------------------------------------------

    IFB_ENG_FUNC const eng_file_h32_t
    eng_file_mngr_open_ro(
        const eng_c8* file_path) {

        eng_file_h32_t handle = { IFB_ENG_FILE_H32_INVALID };
        eng_file_t*    file   = eng_file_mngr_get_next_closed ();

        if (file == NULL) return(handle);

        static const sld::os_file_flags_t os_flags = {
            sld::os_file_flag_e_async        |
            sld::os_file_flag_e_read         |
            sld::os_file_flag_e_share_read   |
            sld::os_file_flag_e_share_write  |
            sld::os_file_flag_e_share_delete |
            sld::os_file_flag_e_overwrite
        };

        sld::os_file_error_t os_error = sld::os_file_open(
            file->os_handle,
            file_path,
            os_flags);

        _file_mngr.last_error = eng_file_mngr_error_os_to_eng(os_error); 

        if (_file_mngr.last_error.val != eng_file_error_e32_success) {
            eng_file_mngr_add_closed(file);
            return(handle);
        }        

        eng_mem_arena_t* arena = sld::arena_commit(_file_mngr.reservation);
        if (file->arena == NULL) {
            _file_mngr.last_error.val = eng_file_error_e32_arena_commit_fail;
            eng_file_mngr_add_closed(file);
            return(handle);            
        }

        file->arena              = arena;
        file->buffer.data        = (byte*)arena->stack.start;
        file->buffer.size        = arena->stack.size;
        file->buffer.length      = 0;
        file->buffer.offset      = 0;
        file->buffer.transferred = 0;

        for (
            eng_u32 index = 0;
            index < _file_mngr.path_size;
            ++index) {

            const eng_c8 c = file_path[index];
            file->path.cstr[index] = c;

            if (c == 0) break;
        }

        handle.val = file->index;
        return(handle);
    }

    IFB_ENG_FUNC const eng_file_h32_t
    eng_file_mngr_open_rw(
        const eng_c8* file_path) {

        eng_file_h32_t handle = {IFB_ENG_FILE_H32_INVALID};
        eng_file_t*    file   = eng_file_mngr_get_next_closed ();

        if (file == NULL) return(handle);

        static const sld::os_file_flags_t os_flags = {
            sld::os_file_flag_e_async        |
            sld::os_file_flag_e_read         |
            sld::os_file_flag_e_write        |
            sld::os_file_flag_e_share_read   |
            sld::os_file_flag_e_share_write  |
            sld::os_file_flag_e_share_delete |
            sld::os_file_flag_e_overwrite
        };

        sld::os_file_error_t os_error = sld::os_file_open(
            file->os_handle,
            file_path,
            os_flags);

        _file_mngr.last_error = eng_file_mngr_error_os_to_eng(os_error); 


        if (_file_mngr.last_error.val != eng_file_error_e32_success) {
            eng_file_mngr_add_closed(file);
            return(handle);
        }        
        
        eng_mem_arena_t* arena = sld::arena_commit(_file_mngr.reservation);
        if (file->arena == NULL) {
            _file_mngr.last_error.val = eng_file_error_e32_arena_commit_fail;
            eng_file_mngr_add_closed(file);
            return(handle);          
        }

        file->arena              = arena;
        file->buffer.data        = (byte*)arena->stack.start;
        file->buffer.size        = arena->stack.size;
        file->buffer.length      = 0;
        file->buffer.offset      = 0;
        file->buffer.transferred = 0;

        for (
            eng_u32 index = 0;
            index < _file_mngr.path_size;
            ++index) {

            const eng_c8 c = file_path[index];
            file->path.cstr[index] = c;

            if (c == 0) break;
        }

        handle.val = file->index; 
        return(handle);
    }

    IFB_ENG_FUNC bool
    eng_file_mngr_close(
        const eng_file_h32_t file_handle) {

    }

    IFB_ENG_FUNC bool
    eng_file_mngr_get_size(
        const eng_file_h32_t file_handle,
        eng_u64&             size) {

        eng_file_t* file = eng_file_mngr_get_file(file_handle);
        if (file == NULL) {
            _file_mngr.last_error.val = eng_file_error_e32_invalid_file;
            return(false);
        } 

        const eng_file_os_error_t os_error = sld::os_file_size(
            file->os_handle,
            size
        );

        file->last_error = eng_file_mngr_error_os_to_eng(os_error);
        
        const eng_bool result = (file->last_error.val == eng_file_error_e32_success);  
        return(result);
    }

    IFB_ENG_FUNC bool
    eng_file_mngr_get_flags(
        const eng_file_h32_t  file_handle,
        eng_file_flags_u32_t& flags) {

        eng_file_t* file = eng_file_mngr_get_file(file_handle);
        if (file == NULL) {
            _file_mngr.last_error.val = eng_file_error_e32_invalid_file;
            return(false);
        } 
        
        flags = file->flags;
        return(true);
    }

    IFB_ENG_FUNC bool
    eng_file_mngr_get_path(
        const eng_file_h32_t file_handle,
        eng_file_path_t&     path) {

        eng_file_t* file = eng_file_mngr_get_file(file_handle);
        if (file == NULL) {
            _file_mngr.last_error.val = eng_file_error_e32_invalid_file;
            return(false);
        } 
        
        path = file->path;
        return(true);
    }

    IFB_ENG_API bool
    eng_file_mngr_get_buffer (
        const eng_file_h32_t file_handle,
        eng_file_buffer_t&   file_buffer) {

        eng_file_t* file = eng_file_mngr_get_file(file_handle);
        if (file == NULL) {
            _file_mngr.last_error.val = eng_file_error_e32_invalid_file;
            return(false);
        } 
        
        file_buffer = file->buffer;
        return(true);
    }

    IFB_ENG_API const eng_file_error_s32_t
    eng_file_mngr_get_last_error(
        const eng_file_h32_t file_handle) {

        if (file_handle.val == IFB_ENG_FILE_H32_INVALID) {
            return(_file_mngr.last_error);    
        }

        const eng_file_t* file = eng_file_mngr_get_file(file_handle);

        eng_file_error_s32_t last_error;
        last_error.val = (file != NULL)
            ? file->last_error.val
            : eng_file_error_e32_invalid_file;
    
        return(last_error);
    }

    IFB_ENG_FUNC bool
    eng_file_mngr_read(
        const eng_file_h32_t file_handle) {

        // validate the file and make sure there's no pending operation
        eng_file_t* file = eng_file_mngr_get_file(file_handle);
        if (!file) {
            _file_mngr.last_error.val = eng_file_error_e32_invalid_file;
            return(false);
        }
        if (file->flags.val & eng_file_flag_e32_io_pending) {
            return(false);
        }

        // set the read and pending io flags
        file->flags.val |= (eng_file_flag_e32_read | eng_file_flag_e32_io_pending);

        // initialize the async context
        eng_file_os_async_context_t& async_context = file->os_async_context;
        async_context.callback->data  = (eng_void*)file;
        async_context.callback->func  = _file_mngr.os_callback_read; 

        // do the async read
        const sld::os_file_error_t os_error = sld::os_file_read_async(
            file->os_handle,
            file->buffer,
            async_context
        );

        // set the last error
        // update flags if we didn't succeed
        file->last_error      = eng_file_mngr_error_os_to_eng(os_error);
        const bool is_success = (file->last_error.val != eng_file_error_e32_success);
        if (!is_success) {
            file->flags.val &= ~(eng_file_flag_e32_read | eng_file_flag_e32_io_pending);
            file->flags.val |= ~(eng_file_flag_e32_error);
        }
        return(is_success);
    }

    IFB_ENG_FUNC bool
    eng_file_mngr_write(
        const eng_file_h32_t     file_handle,
        const eng_file_buffer_t& file_buffer) {

        // validate the file and make sure there's no pending operation
        eng_file_t* file = eng_file_mngr_get_file(file_handle);
        if (!file) {
            _file_mngr.last_error.val = eng_file_error_e32_invalid_file;
            return(false);
        }
        if (file->flags.val & eng_file_flag_e32_io_pending) {
            return(false);
        }

        // set the write and pending io flags
        file->flags.val |= eng_file_flag_e32_write | eng_file_flag_e32_io_pending;

        // initialize the async context
        eng_file_os_async_context_t& async_context = file->os_async_context;
        async_context.callback->data  = (eng_void*)file;
        async_context.callback->func  = _file_mngr.os_callback_write;
        
        // do the async read
        const sld::os_file_error_t os_error = sld::os_file_write_async(
            file->os_handle,
            file->buffer,
            async_context
        );

        // set the last error
        // update flags if we didn't succeed
        file->last_error      = eng_file_mngr_error_os_to_eng(os_error);
        const bool is_success = (file->last_error.val != eng_file_error_e32_success);
        if (!is_success) {
            file->flags.val &= ~(eng_file_flag_e32_write | eng_file_flag_e32_io_pending);
            file->flags.val |= ~(eng_file_flag_e32_error);
        }
        return(is_success);
    }

    //-------------------------------------------------------------------
    // INTERNAL
    //-------------------------------------------------------------------

    IFB_ENG_INTERNAL void
    eng_file_mngr_init(
        void) {

        const bool is_initialized = (_file_mngr.capacity != 0);  
        if (is_initialized) return;

        _file_mngr.reservation       = eng_mem_mngr_get_res_file();
        _file_mngr.os_callback_read  = eng_file_mngr_async_callback_read;
        _file_mngr.os_callback_write = eng_file_mngr_async_callback_write;
        _file_mngr.buffer_size       = sld::size_kilobytes(IFB_ENG_FILE_BUFFER_SIZE_KB);
        _file_mngr.capacity          = IFB_ENG_FILE_TABLE_CAPACITY;
        _file_mngr.path_size         = IFB_ENG_FILE_PATH_SIZE;
        _file_mngr.list.closed       = _file;

        for (
            eng_u32 file_index = 0;
            file_index < _file_mngr.capacity;
            ++file_index) {

            eng_file_t* current = &_file[file_index];

            current->next                      = (file_index < (_file_mngr.capacity - 1)) ? &_file[file_index + 1] : NULL;
            current->prev                      = (file_index > 0)                         ? &_file[file_index - 1] : NULL;
            current->path.cstr                 = &_path_buffer      [file_index * _file_mngr.path_size];
            current->os_async_context.callback = &_callback_context [file_index];
            current->os_async_context.os       = &_os_context       [file_index]; 
            current->index                     = file_index;
        }
    }

    IFB_ENG_INTERNAL eng_void
    eng_file_mngr_async_callback_read(
        const eng_void*           data,
        const eng_file_os_error_t os_error,
        const eng_u32             bytes_transferred) {
        
        if (!data) return;

        eng_file_t* file = (eng_file_t*)data;

        file->last_error          = eng_file_mngr_error_os_to_eng(os_error);
        file->buffer.transferred  = bytes_transferred;
        file->flags.val          &= ~(eng_file_flag_e32_io_pending | eng_file_flag_e32_read);
        file->flags.val          |=  (file->last_error.val == eng_file_error_e32_success)
            ? eng_file_flag_e32_io_complete
            : eng_file_flag_e32_error; 
    }

    IFB_ENG_INTERNAL eng_void
    eng_file_mngr_async_callback_write(
        const eng_void*           data,
        const eng_file_os_error_t os_error,
        const eng_u32             bytes_transferred) {

        if (!data) return;

        eng_file_t* file = (eng_file_t*)data;

        file->last_error          = eng_file_mngr_error_os_to_eng(os_error);
        file->buffer.transferred  = bytes_transferred;
        file->flags.val          &= ~(eng_file_flag_e32_io_pending | eng_file_flag_e32_write);
        file->flags.val          |=  (file->last_error.val == eng_file_error_e32_success)
            ? eng_file_flag_e32_io_complete
            : eng_file_flag_e32_error; 
    }

    IFB_ENG_INTERNAL const eng_error_s32_t
    eng_file_mngr_error_os_to_eng(
        const eng_file_os_error_t os_error) {

        constexpr eng_error_s32_t os_error_map[] = {
            { eng_file_error_e32_success             }, // os_file_error_e_success
            { eng_file_error_e32_unknown             }, // os_file_error_e_unknown
            { eng_file_error_e32_invalid_args        }, // os_file_error_e_invalid_args
            { eng_file_error_e32_invalid_handle      }, // os_file_error_e_invalid_handle
            { eng_file_error_e32_invalid_disk        }, // os_file_error_e_invalid_disk
            { eng_file_error_e32_invalid_device      }, // os_file_error_e_invalid_device
            { eng_file_error_e32_invalid_buffer      }, // os_file_error_e_invalid_buffer
            { eng_file_error_e32_invalid_file        }, // os_file_error_e_invalid_file
            { eng_file_error_e32_sharing_violation   }, // os_file_error_e_sharing_violation
            { eng_file_error_e32_already_exists      }, // os_file_error_e_already_exists
            { eng_file_error_e32_not_found           }, // os_file_error_e_not_found
            { eng_file_error_e32_access_denied       }, // os_file_error_e_access_denied
            { eng_file_error_e32_pipe_busy           }, // os_file_error_e_pipe_busy
            { eng_file_error_e32_reached_end_of_file }, // os_file_error_e_reached_end_of_file
            { eng_file_error_e32_broken_pipe         }, // os_file_error_e_broken_pipe
            { eng_file_error_e32_no_data             }, // os_file_error_e_no_data
            { eng_file_error_e32_more_data           }, // os_file_error_e_more_data
            { eng_file_error_e32_io_incomplete       }, // os_file_error_e_io_incomplete
            { eng_file_error_e32_io_pending          }, // os_file_error_e_io_pending
            { eng_file_error_e32_operation_aborted   }, // os_file_error_e_operation_aborted
            { eng_file_error_e32_disk_io_failure     }, // os_file_error_e_disk_io_failure
            { eng_file_error_e32_disk_corrupt        }, // os_file_error_e_disk_corrupt
            { eng_file_error_e32_device_not_ready    }, // os_file_error_e_device_not_ready
            { eng_file_error_e32_out_of_memory       }, // os_file_error_e_out_of_memory
            { eng_file_error_e32_device_failure      }, // os_file_error_e_device_failure
        };

        constexpr eng_u32 os_error_map_count = sizeof(os_error_map) / sizeof(eng_error_s32_t);


        const eng_error_s32_t eng_error = {(os_error.val < 0 || os_error.val > os_error_map_count)
            ? eng_file_error_e32_unknown
            : os_error_map[os_error.val].val
        };

        return(eng_error);
    }

    IFB_ENG_INTERNAL eng_file_t*
    eng_file_mngr_get_file(
        const eng_file_h32_t file_handle) {

        if (file_handle.val >= _file_mngr.capacity) return(NULL);

        eng_file_t* file     = &_file[file_handle.val]; 
        const bool  is_valid = (file->index == file_handle.val);
        
        return(is_valid ? file : NULL);
    }
    
    IFB_ENG_INTERNAL eng_file_t*
    eng_file_mngr_get_next_closed(
        void) {

        eng_file_t* closed = _file_mngr.list.closed;

        if (closed) {

            eng_file_t* next = closed->next;
            if (next) next->prev = NULL;
            _file_mngr.list.closed = next;
            closed->next = NULL;
            closed->prev = NULL;
        }

        return(closed);
    } 
    
    IFB_ENG_INTERNAL eng_file_t*
    eng_file_mngr_get_next_open(
        void) {

        eng_file_t* open = _file_mngr.list.opened;

        if (open) {

            eng_file_t* next = open->next;
            if (next) next->prev   = NULL;
            _file_mngr.list.opened = next;
            open->next = NULL;
            open->prev = NULL;
        }

        return(open);
    }

    IFB_ENG_INTERNAL void
    eng_file_mngr_add_closed(
        eng_file_t* file) {

        eng_file_t* next = file->next; 
        eng_file_t* prev = file->prev;

        if (next) next->prev = prev;
        if (prev) prev->next = next;
        
        next = _file_mngr.list.closed;
        if (next) next->prev = file;
        file->next = next;
        _file_mngr.list.closed = file;
    }

    IFB_ENG_INTERNAL void
    eng_file_mngr_add_open(
        eng_file_t* file) {

        eng_file_t* next = file->next; 
        eng_file_t* prev = file->prev;

        if (next) next->prev = prev;
        if (prev) prev->next = next;
        
        next = _file_mngr.list.opened;
        if (next) next->prev = file;
        file->next = next;
        _file_mngr.list.opened = file;
    }
};