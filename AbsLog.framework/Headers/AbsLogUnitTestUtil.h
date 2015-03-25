//
//  AbsLogUnitTestUtil.h
//  AbsLog
//
//  Created by Maxim Nikolaevich on 10.01.15.
//  Copyright (c) 2015 Absalt. All rights reserved.
//
ABS_HEADER_OBJC_BEGIN

#ifdef __OBJC__
ABS_EXTERN_C absStatusT
AbsLogUnitTest_is_array_sorted(const void   *first_sort_value,
                               size_t           array_elem_size,
                               size_t           value_size, // now only 4 = sizeof(enum) supported
                               int          last_value);

ABS_EXTERN_C absStatusT
AbsLogUnitTest_String_is_unique(NSString * const * first_sort_value,
                                size_t array_elem_size,
                                size_t array_size);

ABS_EXTERN_C absStatusT
AbsLogUnitTest_array_has_string(NSString *str,
                                NSString *const *first_str,
                                size_t array_elem_size, size_t array_size);
#endif

ABS_EXTERN_C void AbsLogUnitTest_expectedLongTestTime(void);
// to mark test as skiped
ABS_EXTERN_C void AbsLogUnitTest_skipped(void);

ABS_HEADER_OBJC_END
