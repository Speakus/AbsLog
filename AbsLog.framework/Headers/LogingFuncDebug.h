//
//  LogingFuncDebug.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 2009-01-24
//  Copyright (c) 2009 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN

ABS_EXTERN_C const char * resolve_file_name_if_possible(SOURCE_LOG_T log_source);

typedef void (*AbsLogGetUtFunc)(absUtFunc * utFuncArray);

typedef struct {
    FILE_IDX_T      file_index;
    const char      * file_name;
    AbsLogGetUtFunc ut_get_callback; // NULL is not allowed
} AbsUtFilesT;

struct AbsLogLibFilesStruct {
    const AbsUtFilesT * filesArray;
    unsigned libId;          // == LIB_ID
    unsigned maxFilesCnt;    // == FILE_IDX__MAX;
};

ABS_EXTERN_C const AbsLogLibFilesT AbsLogLibFiles4LibraryAbsLog;

ABS_HEADER_C_END

#ifdef __cplusplus
#include <ostream>

ABS_EXTERN_CPP void
log_additional_data(std::ostream & error_data, LogDataT type_log, const void* data);
#endif //__cplusplus
