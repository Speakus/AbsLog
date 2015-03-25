//
//  AbsAutoClasses.hpp
//  AbsLog lib
//
//  Created by Maxim Nikolaevich on 2013-10-15
//  Copyright 2013 Absalt. All rights reserved.
//
ABS_HEADER_CPP_BEGIN

#include <pthread.h>
#include <string>
#include <cstddef> // for __GLIBCXX__

class AutoLogFile;
#ifdef __GLIBCXX__
#  include <tr1/memory>
typedef std::tr1::shared_ptr<const std::string> shared_ptr2str;
typedef std::tr1::shared_ptr<AutoLogFile> shared_ptr2file;
#else
#  include <memory>
typedef std::shared_ptr<const std::string> shared_ptr2str;
typedef std::shared_ptr<AutoLogFile> shared_ptr2file;
#endif

class AutoLogFile {
    FILE * openedFile;
    mutable absBoolT copy2stdout;
    ABS_ATTR_VISIBILITY(hidden) void bindWithStdoutAndStderr(void) const;

    // disallow implicit constructors - define function without implementation
    AutoLogFile( AutoLogFile const& );
    AutoLogFile& operator =( AutoLogFile const& );
public:
    typedef enum {
        OpenModeTruncate,
        OpenModeAppend,
        OpenModeTruncateWithStdoutBinding,
    } OpenModeT;
    ABS_ATTR_VISIBILITY(default) explicit AutoLogFile(const char * filename, OpenModeT mode = OpenModeTruncate);
    ABS_ATTR_VISIBILITY(default) void atomicLog(const std::string & log_string) const;
    ABS_ATTR_VISIBILITY(default) ~AutoLogFile();
};

// based on http://www.rsdn.ru/forum/cpp/2292136?tree=tree
class AutoLock {
    pthread_mutex_t& myMutex;
    int lock_status;
    // disallow implicit constructors - define function without implementation
    AutoLock( AutoLock const& );
    AutoLock& operator =( AutoLock const& );
public:
    typedef enum {
        lockTypeWaitUntilLockDone = false,
        lockTypeJustOneTry = true,
    } lockTypeT;
    ABS_ATTR_VISIBILITY(default) explicit AutoLock(pthread_mutex_t& myLock, lockTypeT justTry = lockTypeWaitUntilLockDone);
    ABS_ATTR_VISIBILITY(default) bool isLocked(void);
    ABS_ATTR_VISIBILITY(default) ~AutoLock();
};

/* local classes and functions */
class AutoRWLock {
    pthread_rwlock_t& myRwLock;
    int lock_status;
    // disallow implicit constructors - define function without implementation
    AutoRWLock( AutoRWLock const& );
    AutoRWLock& operator =( AutoRWLock const& );
    bool isLocked(void);
public:
    typedef enum {
        lock4read = false,
        lock4write = true,
    } lock4T;
    ABS_ATTR_VISIBILITY(default) explicit AutoRWLock(pthread_rwlock_t& myLock, lock4T isWriteLock = lock4read);
    ABS_ATTR_VISIBILITY(default) ~AutoRWLock();
};

typedef std::tr1::shared_ptr<const std::string> shared_ptr2str;
typedef std::tr1::shared_ptr<AutoLogFile> shared_ptr2file;

ABS_HEADER_CPP_END
