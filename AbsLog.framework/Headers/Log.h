//
//  Log.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 2011-04-25
//  Copyright (c) 2011 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN

ABS_EXTERN_C bool isMainThread(void);

enum
{
    // positive - is SOURCE_LOG_T of error
    // negative - is SOURCE_LOG_T of warning
    absStatusOk = 0,
};

#define absStatusFailOn(condition)      ((condition) ? ( (absStatusT)SOURCE_LOG()) : absStatusOk)
#define absStatusWarningOn(condition)   ((condition) ? (-(absStatusT)SOURCE_LOG()) : absStatusOk)
#define isErrorAbsStatus(absStatus)     (absStatus > 0)

typedef signed absStatusT;

static inline absStatusT absStatusUpdate(absStatusT curAbsStatus, absStatusT newAbsStatus)
{
    return
    (absStatusOk == curAbsStatus) ? newAbsStatus :
    (absStatusOk == newAbsStatus) ? curAbsStatus :
    (isErrorAbsStatus(curAbsStatus)) ? curAbsStatus :   // keep old error
    (isErrorAbsStatus(newAbsStatus)) ? newAbsStatus :   // reload warning to new error
    curAbsStatus;                                       // keep old warning
}

static inline LogCategoryT LogCategoryDefault(absStatusT absStatus)
{
    return (absStatus == absStatusOk) ? LogCategoryInfo
    : isErrorAbsStatus(absStatus) ? LogCategoryError : LogCategoryWarning;
}

typedef void (*absUtFunc)(void);

// attribute sentinel = to be ensure that call ended with NULL
// although probably better use other way from http://stackoverflow.com/a/10571237/751932
ABS_EXTERN_C void AbsGetVaList(absUtFunc * utFuncArray, ...) ABS_ATTR_END_WITH_NULL;

#define ABS_VA_FIRST(...) ABS_VA_FIRST_HELPER(__VA_ARGS__, throwaway)
#define ABS_VA_FIRST_HELPER(first, ...) first
#define ABS_VA_ALL(args...) {args}

#define ABS_UT_STATUS_PAIR_INCLUDE_EXPECTED 16
#define ABS_UT_STATUS_OK 0
#define ABS_UT_STATUS   ABS_UT_STATUS_OK

#define AbsLogFileMember_TestFunc_helper(fileName, libId) AbsUtGetTests_ ## libId ## fileName
#define AbsLogFileMember_TestFunc(fileName, libId) AbsLogFileMember_TestFunc_helper(fileName, libId)

#define ABS_UT_CODE_FILE_END_WITH_TESTS(...) \
    static void AbsUtGetTestsByABS_UT_CODE_FILE_END(absUtFunc * utFuncArray) \
    { \
        STOP_COMPILE_IF(ABS_UT_STATUS_OK != ABS_UT_STATUS, not_ABS_UT_STATUS_OK); \
        /* autocheck type */ \
        DEBUG_BLD_CODE(absUtFunc curFileUtFuncs[] ABS_ATTR_UNUSED = ABS_VA_ALL(__VA_ARGS__)); \
        AbsGetVaList(utFuncArray, __VA_ARGS__); \
    } \
    REQUIRE_SEMICON()

#define ABS_UT_CODE_FILE_BEGIN_WITH_IDX(fileIdx) \
    enum { \
        absFileIdx = FILE_IDX_##fileIdx \
    }; \
    static void AbsUtGetTestsByABS_UT_CODE_FILE_END(absUtFunc * utFuncArray); \
    /* need for build failed if idx will be equal already existed */ \
    ABS_LOCAL_EXTERN_C void AbsLogFileMember_TestFunc(fileIdx, LIB_ID) (absUtFunc * utFuncArray); \
    void AbsLogFileMember_TestFunc(fileIdx, LIB_ID) (absUtFunc * utFuncArray) { \
        AbsUtGetTestsByABS_UT_CODE_FILE_END(utFuncArray); \
    } \
    REQUIRE_SEMICON()

#define STOP_COMPILE_UNLESS_ONE_OF_FILES(oneFile, secondFile) \
STOP_COMPILE_IF((FILE_IDX_T)absFileIdx != FILE_IDX_##oneFile && \
                (FILE_IDX_T)absFileIdx != FILE_IDX_##secondFile, \
                thisHeaderShouldBeUsedInOneOfTwoFilesOnly)

#pragma mark function enter and exit macroses
#ifndef AbsTimeoutForOneFunctionCall
#   define AbsTimeoutForOneFunctionCall (2.0)
#endif
#ifndef AbsTimeoutForOneFunctionCallDebug
#   define AbsTimeoutForOneFunctionCallDebug    (AbsTimeoutForOneFunctionCall * 0.9)
#endif

#define AbsTimeoutUltraFastFuncCall                         (AbsTimeoutForOneFunctionCall / 16)
#define AbsTimeoutFastFunctionCall                          (AbsTimeoutForOneFunctionCall / 4)
#define AbsTimeoutForUpdateDbTmpTable                       MIN(AbsTimeoutForOneFunctionCall, 0.5)
#define AbsTimeoutForSelectFromDb                           (AbsTimeoutForOneFunctionCall / 4)
#define AbsTimeoutForUIAlertView_Show                       MAX(AbsTimeoutForOneFunctionCall, 4.0)
// sometimes change system volume take long time (HeadsetBT in log)
#define AbsTimeoutForSetSystemVolume                        (AbsTimeoutForOneFunctionCall * 2)
#define AbsTimeoutForDeleteCacheWitSubfolders               MAX(AbsTimeoutForOneFunctionCall, 2.0)
// first call only
#define AbsTimeoutForCFDateFormatterCreateDateFromString    MAX(AbsTimeoutForOneFunctionCall, 2.6)
#define AbsTimeoutForCreatingTenLocalNotification           MAX(AbsTimeoutForOneFunctionCall, 2.0)

// macroses will log workTime + on debug builds cpuTime
#define SPEED_CHECK_BEGIN_ON_MAIN_THREAD() \
    SPEED_CHECK_BEGIN(); \
    LOG_IF(NO == isMainThread(), LogCategoryError); \
    DO_NOTHING()

#define SPEED_CHECK_BEGIN() \
    const CFTimeInterval speedCheckBeginTimestamp = getSystemUptime(); \
    DEBUG_BLD_CODE(const CFTimeInterval speedCheckBeginCpuUsage = getThisThreadCpuUsedTime()); \
    CFTimeInterval absWorkTime; \
    DO_NOTHING()

#define SPEED_CHECK_END() \
    SPEED_CHECK_END_WITH_MAX_WORK_TIME(AbsTimeoutForOneFunctionCall)

#define SPEED_CHECK_END_WITH_MAX_WORK_TIME(maxPossibleWorkTime) \
    absWorkTime = speedCheck_getWorkTime(&speedCheckBeginTimestamp); \
    ONE_LOOP_BEGIN { \
        BREAK_ON(absWorkTime < maxPossibleWorkTime); \
        LOG_NUM_IF(1, LogCategoryLongTimeIssue, absWorkTime); \
        DEBUG_BLD_CODE(dbgLogCpuUsageOverflow(&speedCheckBeginCpuUsage, maxPossibleWorkTime)); \
    } ONE_LOOP_END \
    DO_NOTHING()

#define SPEED_CHECK_END_ADV(maxPossibleWorkTime, maxWorkTime4Code, some_code) \
    SPEED_CHECK_END_WITH_MAX_WORK_TIME(maxPossibleWorkTime); \
    if (absWorkTime >= maxWorkTime4Code) { some_code; } else \
    DO_NOTHING()

#if !defined(DEBUG) || 0 == DEBUG
#   define RELEASE_AND_DEBUG_BLD_CODE(code4release, code4debug) code4release; REQUIRE_SEMICON()
#   define DEBUG_BLD_CODE(some_code)    { } REQUIRE_SEMICON()
#   define RELEASE_BLD_CODE(some_code)  some_code; REQUIRE_SEMICON()
#   define CAST_AND_LOG_OVERFLOW_ON_DBG(castType, origValue, LogCategoryOnDebug) (castType)(origValue)
#else
#   define RELEASE_AND_DEBUG_BLD_CODE(code4release, code4debug) code4debug; REQUIRE_SEMICON()
#   define DEBUG_BLD_CODE(some_code)    some_code; REQUIRE_SEMICON()
#   define RELEASE_BLD_CODE(some_code)  { } REQUIRE_SEMICON()
#   define CAST_AND_LOG_OVERFLOW_ON_DBG(castType, origValue, LogCategoryOnDebug) \
    CAST_AND_LOG_OVERFLOW(castType, origValue, LogCategoryOnDebug)
#endif

static inline CFTimeInterval speedCheck_getWorkTime(const CFTimeInterval *beginTimestamp) {
    enum { absFileIdx = FILE_IDX__MAX };
    const CFTimeInterval workTime = getSystemUptime() - *beginTimestamp;
    DEBUG_BLD_CODE(LOG_NUM_IF(workTime < 0, LogCategoryError, workTime));
    return workTime;
}

static inline void dbgLogCpuUsageOverflow(const CFTimeInterval *cpuUsageOnBegin,
                                          const CFTimeInterval maxPossibleWorkTime) {
    enum { absFileIdx = FILE_IDX__MAX };
    ONE_LOOP_BEGIN {
        // this function much more longer then getSystemUptime() so use it rarely
        const CFTimeInterval cpuUsage = getThisThreadCpuUsedTime() - *cpuUsageOnBegin;
        BREAK_LOG_NUM_IF(cpuUsage < 0, LogCategoryError, cpuUsage);
        BREAK_LOG_NUM_IF(cpuUsage < maxPossibleWorkTime, LogCategoryLongTimeIssue, cpuUsage);
        BREAK_LOG_NUM_IF(1, LogCategoryWarning, cpuUsage);
        // NB: (cpuUsage > absWorkTime) possible cause getThisThreadCpuUsedTime() called with false
    } ONE_LOOP_END
}

ABS_HEADER_C_END
