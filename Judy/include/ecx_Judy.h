#ifndef ECX_JUDY_H
#define ECX_JUDY_H 1

extern const char ECX_JU_ERRNO_NOMEM[];
extern const char ECX_JU_ERRNO_NULLPPARRAY[];
extern const char ECX_JU_ERRNO_NONNULLPARRAY[];
extern const char ECX_JU_ERRNO_NULLPINDEX[];
extern const char ECX_JU_ERRNO_NULLPVALUE[];
extern const char ECX_JU_ERRNO_NOTJUDY1[];
extern const char ECX_JU_ERRNO_NOTJUDYL[];
extern const char ECX_JU_ERRNO_NOTJUDYSL[];
extern const char ECX_JU_ERRNO_UNSORTED[];
extern const char ECX_JU_ERRNO_OVERRUN[];
extern const char ECX_JU_ERRNO_CORRUPT[];

#define JUDYERROR(CallerFile, CallerLine, JudyFunc, JudyErrno, JudyErrID) \
{ \
    switch(JudyErrno) { \
        case JU_ERRNO_NOMEM: \
            ec_throw_str(ECX_JU_ERRNO_ENOMEM, NULL); \
        case JU_ERRNO_NULLPPARRAY: \
            ec_throw_str_static(ECX_JU_ERRNO_NULLPPARRAY, \
                    "PPArray was null; perhaps &PArray was intended."); \
        case JU_ERRNO_NONNULLPARRAY: \
            ec_throw_str_static(ECX_JU_ERRNO_NONNULLPARRAY, \
                    "A non-NULL array was passed in where a NULL pointer was" \
                    " required."); \
        case JU_ERRNO_NULLPINDEX: \
            ec_throw_str_static(ECX_JU_ERRNO_NULLPINDEX, \
                    "PIndex was null; perhaps &Index was intended."); \
        case JU_ERRNO_NULLPVALUE: \
            ec_throw_str_static(ECX_JU_ERRNO_NULLPVALUE, \
                    "PValue was null; perhaps &Value was intended."); \
        case JU_ERRNO_NOTJUDY1: \
            ec_throw_str_static(ECX_JU_ERRNO_NOTJUDY1, \
                    "PArray is not a Judy1 array."); \
        case JU_ERRNO_NOTJUDYL: \
            ec_throw_str_static(ECX_JU_ERRNO_NOTJUDYL, \
                    "PArray is not a JudyL array."); \
        case JU_ERRNO_NOTJUDYSL: \
            ec_throw_str_static(ECX_JU_ERRNO_NOTJUDYSL, \
                    "PArray is not a JudySL array."); \
        case JU_ERRNO_UNSORTED: \
            ec_throw_str_static(ECX_JU_ERRNO_UNSORTED, \
                    "Unsorted indexes were detected."); \
        case JU_ERRNO_OVERRUN: \
            ec_throw_str_static(ECX_JU_ERRNO_OVERRUN, \
                    "A block of memory was modified after being freed."); \
        case JU_ERRNO_CORRUPT: \
            ec_throw_str_static(ECX_JU_ERRNO_CORRUPT, \
                    "Impossible value detected; Data is corrupt."); \
    } \
}

#include <Judy.h>

#endif /* ECX_JUDY_H */
