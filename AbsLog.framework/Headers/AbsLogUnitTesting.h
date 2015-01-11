//
//  AbsLogUnitTesting.h
//  AbsLog
//
//  Created by Maxim Nikolaevich on 10.01.15.
//  Copyright (c) 2015 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN

// return count of fails
// category for logging = LogCategoryManualInitiatedWarning
ABS_EXTERN_C uint32_t AbsLogUnitTestAllFilesAndLogErrors(uint32_t * cntOfPassNonSkipped);

#ifdef __OBJC__
ABS_EXTERN_C NSDictionary * AbsLogUnitTestAllFilesAndGetErrors(uint32_t * cntOfPassNonSkipped);
#endif

ABS_HEADER_C_END
