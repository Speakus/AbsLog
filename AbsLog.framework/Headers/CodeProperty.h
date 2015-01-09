//
//  CodeProperty.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 2011-04-19
//  Copyright (c) 2011 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN

// real declaration is:
// cpu_type_t bldCpuType(cpu_subtype_t *cpuSubtypeRef);
// but using int - allow us to check on compile time
// these typedefs is same
// and use this header without #include <mach/machine.h>
ABS_EXTERN_C int32_t bldCpuType(int32_t *cpuSubtypeRef);
ABS_EXTERN_C bool CodeProperty_Encrypted(void);
ABS_EXTERN_C uint32_t CodeProperty_compilerSdkHex(void);
ABS_EXTERN_C const char * CodeProperty_UUID(void);
#if !(defined(__IPHONE_OS_VERSION_MAX_ALLOWED))
STOP_COMPILE_IF(true, __IPHONE_OS_VERSION_MAX_ALLOWED);
#endif

ABS_EXTERN_C bool AmIBeingDebugged(void);
ABS_EXTERN_C void runDebugger(void);

ABS_HEADER_C_END
