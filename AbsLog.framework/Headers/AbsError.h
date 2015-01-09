//
//  AbsError.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 25.01.12.
//  Copyright 2012 Absalt. All rights reserved.
//
ABS_HEADER_OBJC_BEGIN

@interface NSError (AbsaltExtension)
+ (id)errorWithError:(NSError*)error AbsStatus:(absStatusT)absStatusArg;
+ (NSError*)errorWithAbsStatus:(absStatusT)absStatusArg UserInfo:(NSDictionary*)userInfo;
- (BOOL)isAbsaltError;
- (BOOL)isAbsaltErrorWithStatus:(absStatusT)status;
- (LogCategoryT)defaultLogCategory;
@end

ABS_HEADER_OBJC_END
