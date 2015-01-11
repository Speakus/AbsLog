//
//  AbsLogUnitTestPrivate.h
//  AbsLog
//
//  Created by Maxim Nikolaevich on 11.01.15.
//  Copyright (c) 2015 Absalt. All rights reserved.
//
ABS_HEADER_OBJC_BEGIN

typedef void (*AbsTestIteration)(absUtFunc ut_func, NSString * funcDescription, void * context);

ABS_EXTERN_C void AbsLogUnitTestingIterateAllTest(AbsTestIteration iterationFunc, void * context);

ABS_EXTERN_C bool
AbsLogUnitTesting_saveAnyError(SOURCE_LOG_T log_source,
                               LogCategoryT LogCategory,
                               const char * error_data);

ABS_EXTERN_C NSError * AbsLogUnitTesting_get_and_reset_data__test_error(void);

ABS_EXTERN_C BOOL AbsLogUnitTesting_get_and_reset_data__is_last_test_can_work_long_time(void);
ABS_EXTERN_C bool AbsLogUnitTesting_get_and_reset_data__is_last_test_skipped(void);

ABS_HEADER_OBJC_END
