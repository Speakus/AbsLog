//
//  LogStream.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 25.01.12.
//  Copyright 2012 Absalt. All rights reserved.
//
ABS_HEADER_CPP_BEGIN

#include <fstream>
#include <CoreFoundation/CoreFoundation.h>

// App assume result of length of this function <= 30
ABS_EXTERN_CPP void logTimeWithDate(std::ostream & out);
ABS_EXTERN_CPP void logTime(std::ostream & out);
ABS_EXTERN_CPP void logTime(std::ostream & out, CFAbsoluteTime time);
ABS_EXTERN_CPP void log_bld_data(std::ostream & out);

ABS_HEADER_CPP_END
