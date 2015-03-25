//
//  AbsLogFiles.mm
//  template for app which used AbsLog lib
//

ABS_UT_CODE_FILE_BEGIN_WITH_IDX(AbsLogFiles);

#import <AbsLog/AbsLogExtension.h>
#include <mach/mach_time.h>

#define AbsLogFileMember(x) ABS_LOCAL_EXTERN_C void AbsLogFileMember_TestFunc(x, LIB_ID) (absUtFunc * utFuncs)
#define AbsLogFileMemberSeparator ;
#include "AbsLogFiles.h"
;
#undef AbsLogFileMember
#undef AbsLogFileMemberSeparator

void AbsLogFileMember_TestFunc(_MAX, LIB_ID)(absUtFunc * funcs) {
    LOG_IF(1, LogCategoryError);
    *funcs = NULL;
}

#if defined(DEBUG) && (DEBUG > 0)
#   define AbsLogFileMember(x) {FILE_IDX_##x, #x, AbsLogFileMember_TestFunc(x, LIB_ID)}
#else // !DEBUG
#   define AbsLogFileMember(x) {FILE_IDX_##x, NULL, AbsLogFileMember_TestFunc(x, LIB_ID)}
#endif // !DEBUG
#define AbsLogFileMemberSeparator ,
static const AbsUtFilesT app_files_array[] = {
#   include "AbsLogFiles.h"
};
#undef AbsLogFileMember
#undef AbsLogFileMemberSeparator

enum { MAX_LIB_ID = LIB_ID };
static const AbsLogLibFilesT stub = { NULL, MAX_LIB_ID, 0 };
static const AbsLogLibFilesT appFiles = {app_files_array, LIB_ID, FILE_IDX__MAX};
const AbsLogLibFilesT * AbsLogAllFiles[] = { &stub, &AbsLogLibFiles4LibraryAbsLog, &appFiles };
STOP_COMPILE_IF(MAX_LIB_ID + 1 != COUNT_ARRAY_ELEMS(AbsLogAllFiles), fix_MAX_LIB_ID);

unsigned bldAppId(bool getCleanAppId) {
    return 1;
}

static NSString * getNSFolder(NSSearchPathDirectory nsFolderType) {
    NSString * result = nil;
    ONE_LOOP_BEGIN {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(nsFolderType,
                                                             NSUserDomainMask,
                                                             TRUE);
        BREAK_LOG_NUM_IF(nil == paths, LogCategoryError, nsFolderType);
        BREAK_LOG_NUM_IF(0 == [paths count], LogCategoryError, nsFolderType);
        result = [paths objectAtIndex: 0];
    } ONE_LOOP_END
    return result;
}

const char * getPath4Logs(void) {
    NSString * folder = getNSFolder(NSCachesDirectory);
    folder = [folder stringByAppendingPathComponent: @"AbsLogData/Logs"];
    
    NSFileManager * fm = [NSFileManager defaultManager];
    [fm createDirectoryAtPath: folder
  withIntermediateDirectories: YES
                   attributes: nil
                        error: nil];
    
    return [folder UTF8String];
}

const char * getFullPath4ExceptionFile(const char * exception_timestr) {
    NSString * folder = getNSFolder(NSCachesDirectory);
    folder = [folder stringByAppendingPathComponent: @"AbsLogData"];
    NSString * exPath = [NSString stringWithFormat: @"%@/ex%s.log", folder, exception_timestr];
    return [exPath UTF8String];
}

// return system power on time
AbsUpTimeT getSystemUptime(void) {
    // use 'static' to be little faster than CACurrentMediaTime()
    static double multiply = 0.0;
    
    ONE_LOOP_BEGIN {
        BREAK_ON(0.0 != multiply);
        mach_timebase_info_data_t s_timebase_info;
        kern_return_t result = mach_timebase_info(&s_timebase_info);
        BREAK_LOG_IF(KERN_SUCCESS != result, LogCategoryError);
        // multiply to get value in the nano seconds
        multiply = (double)s_timebase_info.numer / (double)s_timebase_info.denom;
        // multiply to get value in the seconds
        enum { NANOSECONDS_IN_SEC = 1000 * 1000 * 1000 };
        multiply /= NANOSECONDS_IN_SEC;
        BREAK_LOG_IF(multiply <= 0.0, LogCategoryError);
    } ONE_LOOP_END
    
    return mach_absolute_time() * multiply;
}

CFTimeInterval getThisThreadCpuUsedTime(void) {
    return 0.0;
}

ABS_UT_CODE_FILE_END_WITH_TESTS(NULL);
