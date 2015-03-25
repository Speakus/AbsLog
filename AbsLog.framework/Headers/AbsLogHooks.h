//
//  AbsLogHooks.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 24.01.13.
//  Copyright (c) 2013 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN

typedef enum {
    // helpers
    AbsLogCategoryBitNone       = 0,
    AbsLogCategoryBitJustLog    = (1 << LogCategoryNotice) + (1 << LogCategoryInfo),
    AbsLogCategoryBitNoIssue    = AbsLogCategoryBitJustLog | (1 << LogCategoryManualInitiatedWarning),
    AbsLogCategoryBitAll        = (1 << LogCategoryMax) - 1,

    AbsLogCategoryBitDoCrash    = (1 << LogCategoryDoCrashNow),
    AbsLogCategoryBitTimeIssue  = (1 << LogCategoryLongTimeIssue),
    AbsLogCategoryBitSomeIssue  = (AbsLogCategoryBitAll & ~AbsLogCategoryBitNoIssue),
    AbsLogCategoryBitSomeAlert  = (AbsLogCategoryBitAll & ~AbsLogCategoryBitJustLog),
} AbsLogCategoryBitT;

enum {
    AbsLogHookPriorityMin       = 1,
    AbsLogHookPriorityLow       = 64,
    AbsLogHookPriorityDefault   = 128, // for regular log to file
    AbsLogHookPriorityAboveNorm = 160,
    AbsLogHookPriorityHigh      = 192,
    AbsLogHookPriorityVeryHigh  = 224, // for debug proposal
    AbsLogHookPriorityMax       = 255, // for debug proposal
};
typedef int AbsLogHookPriorityT;

// return true if other hooks (with less priority) should continue processing log
// be carefull - hook must not LOG anything with LogCategoryT which handled
typedef bool (*shouldStopAnyOtherHook)(SOURCE_LOG_T log_source, LogCategoryT LogCategory, const char * error_data);
ABS_EXTERN_C absStatusT setupLogHook(AbsLogCategoryBitT categories, AbsLogHookPriorityT priority, shouldStopAnyOtherHook hook);
ABS_EXTERN_C absStatusT clearLogHook(shouldStopAnyOtherHook hook);

ABS_HEADER_C_END
