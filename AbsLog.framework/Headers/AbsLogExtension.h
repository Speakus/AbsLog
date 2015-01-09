//
//  AbsLogExtension.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich
//  Copyright (c) 2014 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN
#include <AbsLog/LogingFunc.h>
#include <AbsLog/AbsLogHooks.h>
#include <AbsLog/AbsLogCrash.h>
#include <AbsLog/LogingFuncDebug.h>
#include <AbsLog/CodeProperty.h>

#ifdef __OBJC__
#include <AbsLog/AbsError.h>
#include <AbsLog/LogObjective.h>
#endif

ABS_HEADER_C_END

#ifdef __cplusplus
#include <AbsLog/LogStream.h>
#include <AbsLog/AbsAutoClasses.hpp>
#endif
