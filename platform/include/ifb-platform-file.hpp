#ifndef IFB_PLATFORM_FILE_HPP
#define IFB_PLATFORM_FILE_HPP

#include <ifb.hpp>

/**********************************************************************************/
/* FILES                                                                          */                            
/**********************************************************************************/

struct IFBPlatformFileRequest {
    IFBPtr x; //TEMPORARY
};

typedef const IFBU32 (*IFBPlatformFileROContextSize)    (IFBVoid);
typedef const IFBB8  (*IFBPlatformFileROOpen)           (IFBPlatformFileRequest* file_ro_request);
typedef const IFBB8  (*IFBPlatformFileROReadImmediate)  (IFBPlatformFileRequest* file_ro_request);
typedef const IFBB8  (*IFBPlatformFileROReadAsync)      (IFBPlatformFileRequest* file_ro_request);
typedef const IFBB8  (*IFBPlatformFileROClose)          (IFBPlatformFileRequest* file_ro_request);

typedef const IFBU32 (*IFBPlatformFileRWContextSize)    (IFBVoid);
typedef const IFBB8  (*IFBPlatformFileRWOpen)           (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWReadImmediate)  (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWReadAsync)      (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWWriteImmediate) (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWWriteAsync)     (IFBPlatformFileRequest* file_rw_request);
typedef const IFBB8  (*IFBPlatformFileRWClose)          (IFBPlatformFileRequest* file_rw_request);

#endif //IFB_PLATFORM_FILE_HPP