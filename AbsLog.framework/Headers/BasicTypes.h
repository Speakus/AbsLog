//
//  BasicTypes.h
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 2012-04-13
//  Copyright (c) 2012 Absalt. All rights reserved.
//

// since pragma once supported by any compiler
// http://en.wikipedia.org/wiki/Pragma_once
// we can use it for any header
#define ABS_PREPROCESS_TO_STR(x) #x
#define ABS_PRAGMA(x) _Pragma(ABS_PREPROCESS_TO_STR(x))

#ifdef __cplusplus
    #define ABS_HEADER_C_BEGIN ABS_PRAGMA(once); extern "C" {
    #define ABS_HEADER_C_END }
#else
    #define ABS_HEADER_C_BEGIN ABS_PRAGMA(once);
    #define ABS_HEADER_C_END
#endif //__cplusplus

ABS_HEADER_C_BEGIN

#ifdef __OBJC__
    #define ABS_HEADER_OBJC_BEGIN	ABS_HEADER_C_BEGIN
    #define ABS_HEADER_OBJC_END		ABS_HEADER_C_END
#else // !__OBJC__
    #define ABS_HEADER_OBJC_BEGIN	typedef int header_only_for_objc[-1];
    #define ABS_HEADER_OBJC_END		typedef int header_only_for_objc[-1];
#endif // !__OBJC__

#ifdef __cplusplus
    #define ABS_LOCAL_EXTERN_C extern "C" ABS_ATTR_VISIBILITY(hidden)
    #define ABS_LOCAL_EXTERN_CPP  extern  ABS_ATTR_VISIBILITY(hidden)
    #define ABS_EXTERN_C extern "C" ABS_ATTR_VISIBILITY(default)
    #define ABS_EXTERN_CPP  extern  ABS_ATTR_VISIBILITY(default)
    #define ABS_HEADER_CPP_BEGIN	ABS_PRAGMA(once);
    #define ABS_HEADER_CPP_END
#else
    #define ABS_LOCAL_EXTERN_C extern ABS_ATTR_VISIBILITY(hidden)
    #define ABS_LOCAL_EXTERN_CPP typedef int only_for_cpp[-1];
    #define ABS_EXTERN_C extern ABS_ATTR_VISIBILITY(default)
    #define ABS_EXTERN_CPP typedef int only_for_cpp[-1];
    #define ABS_HEADER_CPP_BEGIN	typedef int header_only_for_cpp[-1];
    #define ABS_HEADER_CPP_END		typedef int header_only_for_cpp[-1];
#endif //__cplusplus

#if (__IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_5_0) && defined(__clang__)
    #define NEW_AUTORELEASE_POOL_BEGIN()	@autoreleasepool { DO_NOTHING()
    #define NEW_AUTORELEASE_POOL_END()		} DO_NOTHING()
#else
    #define NEW_AUTORELEASE_POOL_BEGIN()	NSAutoreleasePool *dontUseThisVarDirectly = \
                                                [[NSAutoreleasePool alloc] init]; { DO_NOTHING()
    #define NEW_AUTORELEASE_POOL_END()		} [dontUseThisVarDirectly drain]/* release is no-op in GC */
#endif

//simple macros for do nothing (requires semicolon at end of macros)
#define DO_NOTHING() ((void)0)
#define REQUIRE_SEMICON_HELPER2(line) enum { requreSemicolonAtTheEndOfMacros ## line }
#define REQUIRE_SEMICON_HELPER1(line) REQUIRE_SEMICON_HELPER2(line)
// it's possible require semicolon outside any functions
#define REQUIRE_SEMICON() REQUIRE_SEMICON_HELPER1(__LINE__)

// based on CR_DEFINE_STATIC_LOCAL from
// http://src.chromium.org/svn/trunk/src/base/basictypes.h
// to use without args:
// STATIC_VAR_WITHOUT_DESTRUCTOR(type, var, ());
// to use with several args:
// STATIC_VAR_WITHOUT_DESTRUCTOR(type, var, (0, 0));
#define STATIC_VAR_WITHOUT_DESTRUCTOR(type, variable, args) \
    static type & variable = *new type args

// NULL is not allowed in params
#define ABS_ATTR_NOT_NULL(...) __attribute__((nonnull(__VA_ARGS__)))
// only for ... in params
#define ABS_ATTR_END_WITH_NULL __attribute__((sentinel))
// https://gcc.gnu.org/wiki/Visibility
#define ABS_ATTR_VISIBILITY(x) __attribute__ ((visibility (ABS_PREPROCESS_TO_STR(x))))
// TODO remove
#define ABS_ATTR_UNUSED __attribute__ ((unused))
// http://stackoverflow.com/a/12199209/751932
#define ABS_MARK_AS_UNUSED(parameter_) ABS_PRAGMA(unused(parameter_))

#if defined(__cplusplus)
#   define IS_SIGNED_VAR_TYPE(var) (std::numeric_limits<__typeof__(var)>::is_signed)
#   define IS_SIGNED_TYPE(T) (std::numeric_limits<T>::is_signed)
#else
#   define IS_SIGNED_VAR_TYPE(var) ( (__typeof__(var))(-1) < 1 )
#   define IS_SIGNED_TYPE(T) ( (T)(-1) < 1 )
#endif

#include <stddef.h> // for define NULL, size_t, ptrdiff_t, etc
#include <stdbool.h> // for define bool
#include <stdint.h> // for uint8_t, uint16_t, etc

typedef enum
{
	absBoolFalse	= false,
	absBoolTrue		= true,
	absBoolMaybe	= -1,
} absBoolT; // use this type only if absBoolMaybe required for you

static inline bool isAbsBoolMaybe(absBoolT value) {
    // fastest way to check
    return (value < 0);
}

enum {
	AbsEnum_SPECIAL = 0x7FFFFFFE,
	AbsEnum_INVALID = 0x7FFFFFFF
};
typedef unsigned AbsEnumT;

enum {
	MAX_SOURCE_LINES_ALLOWED	= 1000,
	MAX_FILES_ALLOWED			= 1000,
	ABS_UT_MAX_POSSIBLE_TESTS_PER_FILE = 100,
};

ABS_HEADER_C_END
