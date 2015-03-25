//
//  LogObjective.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 2011-01-18
//  Copyright (c) 2011 Absalt. All rights reserved.
//
ABS_HEADER_OBJC_BEGIN

@class UIControl;

ABS_ATTR_VISIBILITY(default) @interface ConvertAnyMessageToException : NSObject
{
    int     preventedRelease;
}
+ (id)sharedInstance;
+ (void)exceptionOnControlEvents:(UIControl *)control removeTarget:(id)oldTarget;
@end

ABS_EXTERN_C void LogCallStack(NSException * exception_obj);

ABS_HEADER_OBJC_END
