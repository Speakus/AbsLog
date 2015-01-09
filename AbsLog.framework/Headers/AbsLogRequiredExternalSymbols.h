//
//  AbsLogRequiredExternalSymbols.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich
//  Copyright (c) 2014 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN

ABS_EXTERN_C unsigned bldAppId(bool getCleanAppId);
ABS_EXTERN_C const char * getPath4Logs(void);
ABS_EXTERN_C const char * getFullPath4ExceptionFile(const char * exception_timestr);

typedef CFTimeInterval AbsUpTimeT;

// return system power on time
ABS_EXTERN_C AbsUpTimeT getSystemUptime(void);
ABS_EXTERN_C CFTimeInterval getThisThreadCpuUsedTime(void);

// This var defined in the app, like this:
// static const AbsUtFilesT stub = { NULL, maxLibs, 0 };
// const AbsLogLibFilesT * AbsLogAllFiles[] = { &stub, &appFiles, &AbsLogLibFiles4LibraryAbsLog };
typedef struct AbsLogLibFilesStruct AbsLogLibFilesT;
ABS_EXTERN_C const AbsLogLibFilesT * AbsLogAllFiles[];

ABS_HEADER_C_END
