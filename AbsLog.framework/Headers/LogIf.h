//
//  LogIf.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 2014-07-15
//  Copyright (c) 2014 Absalt. All rights reserved.
//
ABS_HEADER_C_BEGIN

#define AbsLogFileMember(x) FILE_IDX_##x
#define AbsLogFileMemberSeparator ,
typedef enum {
#include "AbsLogFiles.h"
} FILE_IDX_T;
#undef AbsLogFileMember
#undef AbsLogFileMemberSeparator

typedef enum {
	LogCategoryInfo,					// debug info
	LogCategoryNotice,					// key info
	LogCategoryManualInitiatedWarning,
	LogCategoryLongTimeIssue,			// it's info under debugger and Warning without
	LogCategoryWarning,					// it's strange but it's not problem
	LogCategoryError,
	LogCategoryCustomMsg,				// inform customer with msg fmt 'title:msg:-hiddenmsg'
	LogCategoryDoCrashNow,
	LogCategoryMax,

	LogCategoryLastRegular = LogCategoryError,
	LogCategoryNumBits = 4,
	LogCategoryShift = 0,
	LogCategoryMask = ((1 << LogCategoryNumBits) - 1) << LogCategoryShift,
} LogCategoryT;

typedef enum {
	LogDataNothing,
	LogDataHex,			// long
	LogDataDouble,		// double
	LogDataOsStatus,	// OSStatus
	LogDataAbsStatus,	// absStatusT
	LogDataAppTime,		// CFAbsoluteTime
	LogDataCStr,		// const char *
	LogDataObjDescr,	// NSObject *
	LogDataDump,		// const void *
	LogDataLogableObj,  // LogableObj *
	LogDataMax,
	
	LogDataNumBits	= 4,
	LogDataShift	= LogCategoryNumBits,
	LogDataMask = ((1 << LogDataNumBits) - 1) << LogDataShift,
} LogDataT;
	
typedef uint32_t SOURCE_LOG_T;
typedef uint32_t LogTypeT;
	
#if (!defined(LIB_ID))
#error LIB_ID is not defined!
#endif // (!defined(LIB_ID))
// LIB_ID - Each library must define id
// absFileIdx - usually defined via ABS_UT_CODE_FILE_BEGIN_WITH_IDX()
#define SOURCE_LOG() ((SOURCE_LOG_T)\
(((LIB_ID \
	* MAX_FILES_ALLOWED + absFileIdx \
		) * MAX_SOURCE_LINES_ALLOWED) + __LINE__) \
)

static inline LogTypeT getLogType(LogDataT LogData, LogCategoryT LogCategory)
{
	return ((uint32_t)LogCategory << LogCategoryShift) + ((uint32_t)LogData << LogDataShift);
}

ABS_EXTERN_C void
log_now(SOURCE_LOG_T	sourceLog,	// contain LIB_ID, absFileIdx, __LINE__ (via macros SOURCE_LOG())
		LogTypeT		LogType,	// created via getLogType()
		const void *data);			// additional data (depends from type)

typedef struct
{
	const void * pointer;
	int size;
} LOG_HERE_DUMP_T;

#pragma mark Internal Log macroses
// should not be used directly
#define _ABS_LOG(LogData, LogCategory, p_data) \
	log_now(SOURCE_LOG(), getLogType(LogData, LogCategory), p_data)

#ifndef _ABS_POSSIBLE_LOG
#define _ABS_POSSIBLE_LOG() DO_NOTHING()
#endif
	
#pragma mark Log macroses
#define LOG_IF(condition, LogCategory) \
	if (condition) { \
		_ABS_LOG(LogDataNothing, LogCategory, NULL); \
	} else _ABS_POSSIBLE_LOG()

#define LOG_STR_IF(condition, LogCategory, cstr) \
	if (condition) { \
		const char * abs_log_d = (cstr); /* check for correct argument type */ \
		_ABS_LOG(LogDataCStr, LogCategory, abs_log_d); \
	} else _ABS_POSSIBLE_LOG()

#define LOG_NUM_IF(condition, LogCategory, num) \
	if (condition) { \
		double abs_log_d = (num); /* check for correct argument type */ \
		_ABS_LOG(LogDataDouble, LogCategory, &abs_log_d); \
	} else _ABS_POSSIBLE_LOG()

#define LOG_HEX_IF(condition, LogCategory, num) \
	if (condition) { \
		uint64_t abs_log_d = (num); /* check for correct argument type */ \
		_ABS_LOG(LogDataHex, LogCategory, &abs_log_d); \
	} else _ABS_POSSIBLE_LOG()
	
#define LOG_ABS_TIME_IF(condition, LogCategory, absTime) \
	if (condition) { \
		CFAbsoluteTime abs_log_d = (absTime); /* check for correct argument type */ \
		_ABS_LOG(LogDataAppTime, LogCategory, &abs_log_d); \
	} else _ABS_POSSIBLE_LOG()

// pass NSString for fast or NSAutoreleasedPool will be created and drained in this point
#define LOG_OBJC_IF(condition, LogCategory, object) \
	if (condition) { \
		NSObject * abs_log_data = (object); /* check for correct argument type */ \
        const void * abs_log_d = objc_unretainedPointer(abs_log_data); \
		_ABS_LOG(LogDataObjDescr, LogCategory, abs_log_d); \
	} else _ABS_POSSIBLE_LOG()
		
#define LOG_OS_STATUS_FAIL(LogCategory, os_status) \
	do { \
		OSStatus abs_log_d = (os_status); /* check for correct argument type */ \
		if (noErr != abs_log_d) { \
			_ABS_LOG(LogDataOsStatus, LogCategory, &abs_log_d); \
		} else _ABS_POSSIBLE_LOG(); \
	} while (0)

#define LOG_ABS_STATUS_IF(condition, LogCategory, abs_status) \
	if (condition) { \
		absStatusT abs_log_d = (abs_status); /* check for correct argument type */ \
		_ABS_LOG(LogDataAbsStatus, LogCategory, &abs_log_d); \
	} else _ABS_POSSIBLE_LOG()
	
#define LOG_ABS_STATUS_FAIL(LogCategory, abs_status) \
	do { \
		absStatusT abs_log_d = (abs_status); /* check for correct argument type */ \
		if (absStatusOk != abs_log_d) { \
			_ABS_LOG(LogDataAbsStatus, LogCategory, &abs_log_d); \
		} else _ABS_POSSIBLE_LOG(); \
	} while (0)

#if !defined(__cplusplus)
#define LOG_DUMP_IF(condition, LogCategory, ptr_arg, size_arg) \
    if (condition) { \
        LOG_HERE_DUMP_T data; \
        data.pointer = (ptr_arg); \
        data.size = (size_arg); \
        _ABS_LOG(LogDataDump, LogCategory, &data); \
    } else _ABS_POSSIBLE_LOG()
#else // defined(__cplusplus)
#define LOG_DUMP_IF(condition, LogCategory, ptr_arg, size_arg) \
    if (condition) { \
        LOG_HERE_DUMP_T data; \
        data.pointer = static_cast<void *>(ptr_arg); \
        data.size = (size_arg); \
        _ABS_LOG(LogDataDump, LogCategory, &data); \
    } else _ABS_POSSIBLE_LOG()
#endif // defined(__cplusplus)
		
#define LOG_CPP_IF(condition, LogCategory, p_object) \
	if (condition) \
	{ \
		const LogableObj * abs_log_data = (p_object); /* check for correct argument type */ \
		_ABS_LOG(LogDataLogableObj, LogCategory, abs_log_data); \
	} else _ABS_POSSIBLE_LOG()

static inline uint64_t hexFromStatusAndErrno(int32_t status, int32_t errnoArg) {
    uint64_t result = (uint32_t)errnoArg;
    if (-1 != status) {
        uint64_t status2 = (uint32_t)status;
        result |= (status2 << 32);
    }
    return result;
}

static inline uint64_t hexFrom2uint32(uint32_t first, uint32_t second) {
    uint64_t high_dword = first;
    high_dword <<= 32;
    return high_dword | second;
}

#pragma mark LOG with BREAK macroses
// two macros for use BREAK_LOG_IF() macros
#define ONE_LOOP_BEGIN do
#define ONE_LOOP_END while (0);

#define BREAK_LOG_IF(condition, LogCategory) \
	if (condition) \
	{ \
		LOG_IF(1, LogCategory); \
		break; \
	} else _ABS_POSSIBLE_LOG()

#define BREAK_LOG_STR_IF(condition, LogCategory, cstr) \
	if (condition) \
	{ \
		LOG_STR_IF(1, LogCategory, cstr); \
		break; \
	} else _ABS_POSSIBLE_LOG()

#define BREAK_LOG_OBJC_IF(condition, LogCategory, object) \
	if (condition) \
	{ \
		LOG_OBJC_IF(1, LogCategory, object); \
		break; \
	} else _ABS_POSSIBLE_LOG()

#define BREAK_LOG_NUM_IF(condition, LogCategory, num) \
	if (condition) \
	{ \
		LOG_NUM_IF(1, LogCategory, num); \
		break; \
	} else _ABS_POSSIBLE_LOG()

#define BREAK_LOG_HEX_IF(condition, LogCategory, num) \
    if (condition) \
    { \
        LOG_HEX_IF(1, LogCategory, num); \
        break; \
    } else _ABS_POSSIBLE_LOG()

#pragma mark break without LOG macroses
#define BREAK_ON(condition) \
	if (condition) { \
		break; \
	} else DO_NOTHING()

#define BREAK_SAVE_IF(condition, sourceLogVar) \
	if (condition) { \
		(sourceLogVar) = SOURCE_LOG(); \
		break; \
	} else DO_NOTHING()

ABS_HEADER_C_END

#if !defined(__cplusplus) // pure C
// NB! pure C version of this cast will not check overflow for same size
// ex: from int to unsigned and vice versa
// cause sizeof the same (and no other way to exclude check at compile time)
#define CAST_AND_LOG_OVERFLOW(castType, origValue, LogCategory) ( { \
    const __typeof__(origValue) _origValue = (origValue); /* read from macros only once */ \
    const castType _newValue = (castType)_origValue; \
    enum { _isPossibleBadCastWhileAssign = sizeof(castType) != sizeof(_origValue) }; \
    LOG_NUM_IF( ( _isPossibleBadCastWhileAssign \
                && _origValue != (__typeof__(_origValue))_newValue \
                ), LogCategory, _origValue); \
    _newValue; \
} )
#else // c++
#if __cplusplus < 201103L
// need to extend std to use as c++11 - for checking types the same
// based on http://stackoverflow.com/a/15200682/751932
namespace std {
    template<typename T, typename U> struct is_same    { enum { value = false }; };
    template<typename T>        struct is_same<T, T>   { enum { value = true }; };
};
#endif // pre c++11
// C++ version allow to check even from int to unsigned overflow
// based on http://stackoverflow.com/a/999032/751932
#define CAST_AND_LOG_OVERFLOW(castType, origValue, LogCategory) ( { \
    const __typeof__(origValue) _origValue = (origValue); /* read from macros only once */ \
    const castType _newValue = static_cast<castType>(_origValue); \
    enum { _isPossibleBadCastWhileAssign = std::is_same<castType, __typeof__(origValue)>::value }; \
    LOG_NUM_IF( ( _isPossibleBadCastWhileAssign && \
                    ( _origValue != static_cast<__typeof__(_origValue)>(_newValue) \
                    || (_origValue > 0 && _newValue < 0) \
                    || (_origValue < 0 && _newValue > 0) \
                    ) \
                ), LogCategory, _origValue); \
    _newValue; \
} )

#include <ostream>

class LogableObj {
public:
    virtual void get_description(std::ostream & out_stream) const = 0;
    virtual ~LogableObj() {}
};

#endif // c++
