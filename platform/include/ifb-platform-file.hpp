#ifndef IFB_PLATFORM_FILE_HPP
#define IFB_PLATFORM_FILE_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FILES                                                                          */                            
/**********************************************************************************/

struct IFBPlatformFileRequest {
    ifb::ptr x; //TEMPORARY
};

typedef const ifb::u32 (*IFBPlatformFileROContextSize)    (void);
typedef const ifb::b8  (*IFBPlatformFileROOpen)           (IFBPlatformFileRequest* file_ro_request);
typedef const ifb::b8  (*IFBPlatformFileROReadImmediate)  (IFBPlatformFileRequest* file_ro_request);
typedef const ifb::b8  (*IFBPlatformFileROReadAsync)      (IFBPlatformFileRequest* file_ro_request);
typedef const ifb::b8  (*IFBPlatformFileROClose)          (IFBPlatformFileRequest* file_ro_request);

typedef const ifb::u32 (*IFBPlatformFileRWContextSize)    (void);
typedef const ifb::b8  (*IFBPlatformFileRWOpen)           (IFBPlatformFileRequest* file_rw_request);
typedef const ifb::b8  (*IFBPlatformFileRWReadImmediate)  (IFBPlatformFileRequest* file_rw_request);
typedef const ifb::b8  (*IFBPlatformFileRWReadAsync)      (IFBPlatformFileRequest* file_rw_request);
typedef const ifb::b8  (*IFBPlatformFileRWWriteImmediate) (IFBPlatformFileRequest* file_rw_request);
typedef const ifb::b8  (*IFBPlatformFileRWWriteAsync)     (IFBPlatformFileRequest* file_rw_request);
typedef const ifb::b8  (*IFBPlatformFileRWClose)          (IFBPlatformFileRequest* file_rw_request);

#endif //IFB_PLATFORM_FILE_HPP