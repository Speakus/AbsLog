//
//  LogingFunc.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 2009
//  Copyright (c) 2009 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN
#include <CoreFoundation/CoreFoundation.h>

ABS_EXTERN_C int AbsCurThreadId(void);
ABS_EXTERN_C CFAbsoluteTime getLogStartTime(void);
ABS_EXTERN_C const char * get_log_start_time(void);
ABS_EXTERN_C void init_loging(void);
ABS_EXTERN_C void reinit_loging(void);

static inline LogDataT getLogData(LogTypeT typeLog)
{
	return (LogDataT)((typeLog & LogDataMask) >> LogDataShift);
}

static inline LogCategoryT getLogCategory(LogTypeT typeLog)
{
	return (LogCategoryT)((typeLog & LogCategoryMask) >> LogCategoryShift);
}

ABS_HEADER_C_END
