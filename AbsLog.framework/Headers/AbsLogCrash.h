//
//  AbsLogCrash.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 17.01.13.
//  Copyright (c) 2013 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN

ABS_EXTERN_C void setCurThreadName(const char * name);
ABS_EXTERN_C void AbsLogCrashUpdateOurUncaughtExHandler(bool isThirdPartyUsed);

// function enable loging on any exceptions
// recommended place to call main();
ABS_EXTERN_C void AbsLogCrashInit(void);

ABS_HEADER_C_END
