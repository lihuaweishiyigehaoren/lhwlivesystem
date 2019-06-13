#pragma once

#ifndef WIN32
#define KLOG_PREDICT_BRANCH_NOT_TAKEN(x) (__builtin_expect(x, 0))
#else
#define KLOG_PREDICT_BRANCH_NOT_TAKEN(x) x
#endif

#ifdef USE_KLOG

#define LOG(severity) (logging::Logger( \
        (severity), \
        __FILE__, \
        __LINE__ \
    ).Reference())

#define LOG_IF(severity, expr) !(KLOG_PREDICT_BRANCH_NOT_TAKEN(!(!(expr)))) ? \
    (void) 0 : \
    logging::LogMessageVoidify() & (logging::ExpressionLogger( \
            (severity), \
            __FILE__, \
            __LINE__, \
            #expr \
    ).Reference())


#define LOG_CHECK(expr) !(KLOG_PREDICT_BRANCH_NOT_TAKEN(!(expr))) ? \
    (void) 0 : \
    logging::LogMessageVoidify() & logging::CheckLogger( \
        LOG_FATAL, \
        __FILE__, \
        __LINE__, \
        #expr \
    ).Reference()

#ifndef NDEBUG
#define DLOG(severity) LOG(severity)
#define DLOG_IF(severity, expr) LOG_IF(severity, expr)
#define DLOG_CHECK(expr) LOG_CHECK(expr)
#else // NDEBUG
#define DLOG(severity) !(KLOG_PREDICT_BRANCH_NOT_TAKEN(0)) ? \
    (void) 0 : logging::LogMessageVoidify() & LOG(severity)
#define DLOG_IF(severity, expr) DLOG(severity)
#define DLOG_CHECK(expr) DLOG(LOG_FATAL)
#endif // NDEBUG

#else // USE_KLOG

#define LOG(severity) !(KLOG_PREDICT_BRANCH_NOT_TAKEN(0)) ? \
    (void) 0 : \
    logging::LogMessageVoidify() & (logging::Logger( \
        (severity), \
        __FILE__, \
        __LINE__ \
    ).Reference())
#define LOG_IF(severity, expr) LOG(severity)
#define LOG_CHECK(expr) LOG(KLOG_FATAL)

#define DLOG(severity) LOG(severity)
#define DLOG_IF(severity, expr) LOG(severity)
#define DLOG_CHECK(expr) LOG(KLOG_FATAL)

#endif /// USE_KLOG