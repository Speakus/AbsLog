//
//  LogingFunc.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 2009
//  Copyright (c) 2009 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN
#include <CoreFoundation/CoreFoundation.h>

// This function should be called first.
// Any logging before this function call will be
// logged as error in time of first call of this function
//
// recommended place to call in the method
// - (BOOL)application:(UIApplication *)app didFinishLaunchingWithOptions:(NSDictionary *)options
ABS_EXTERN_C void start_new_app_log(void);

ABS_EXTERN_C int AbsCurThreadId(void);
ABS_EXTERN_C CFAbsoluteTime getLogStartTime(void);
ABS_EXTERN_C const char * get_log_start_time(void);

static inline LogDataT getLogData(LogTypeT typeLog)
{
	return (LogDataT)((typeLog & LogDataMask) >> LogDataShift);
}

static inline LogCategoryT getLogCategory(LogTypeT typeLog)
{
	return (LogCategoryT)((typeLog & LogCategoryMask) >> LogCategoryShift);
}

ABS_HEADER_C_END
