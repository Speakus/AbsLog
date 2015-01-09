//
// look to AbsLog.framework/Resources/AbsLogFiles.mm for details of declaration
//
ABS_HEADER_C_BEGIN

typedef struct AbsLogLibFilesStruct AbsLogLibFilesT;
ABS_EXTERN_C const AbsLogLibFilesT * AbsLogAllFiles[];

// for first line in the log (getCleanAppId always false)
ABS_EXTERN_C unsigned bldAppId(bool getCleanAppId);
// called once at first call start_new_app_log()
ABS_EXTERN_C const char * getPath4Logs(void);
// useful to save each exception to separate file
// return NULL for disabling feature
ABS_EXTERN_C const char * getFullPath4ExceptionFile(const char * exception_timestr);

typedef CFTimeInterval AbsUpTimeT;

// wrapper for CACurrentMediaTime() is expected
// required for SPEED_CHECK_BEGIN()
ABS_EXTERN_C AbsUpTimeT getSystemUptime(void);

// could return 0
ABS_EXTERN_C CFTimeInterval getThisThreadCpuUsedTime(void);

ABS_HEADER_C_END
