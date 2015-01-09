//
//  AbsLog.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich
//  Copyright (c) 2014 Absalt. All rights reserved.
//
_Pragma("once");

// next example for use AbsLog framework
// create AbsLogFiles.h with next content:

/*
AbsLogFileMember(SomeFileName1          ) AbsLogFileMemberSeparator
// add new files before this line
AbsLogFileMember(_MAX                   )
 */

// and after this you can use:
// #include <AbsLog/AbsLog.h>

// SomeFileName1 - should start with
// ABS_UT_CODE_FILE_BEGIN_WITH_IDX(SomeFileName1);
// and end with:
// ABS_UT_CODE_FILE_END_WITH_TESTS(NULL);

#include <AbsLog/BasicTypes.h>
#include <AbsLog/LogIf.h>
#include <AbsLog/AbsLogRequiredExternalSymbols.h>
#include <AbsLog/Log.h>
