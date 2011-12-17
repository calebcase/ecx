
#define _GNU_SOURCE
#include <ec/ec.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <ecx_stdlib.h>

static const char STRTO_POSITIVE[] = "Positive overflow.";
static const char STRTO_NEGATIVE[] = "Negative overflow.";
static const char STRTO_UNDERFLOW[] = "Underflow.";

#define STRTO(type,name) \
    type \
    ecx_strto##name(const char *nptr, char **endptr) \
    { \
        char *temp_endptr = NULL; \
        errno = 0; \
        type value = strto##name(nptr, &temp_endptr); \
        if (endptr != NULL) *endptr = temp_endptr; \
        \
        if (value == 0.0 && nptr == temp_endptr) { \
            char *msg = NULL; \
            int status = asprintf(&msg, "Unable to convert '%s'.", nptr); \
            if (status == -1) msg = NULL; \
            \
            ec_throw_str(ECX_EC) msg; \
        } \
        if (errno != 0) { \
            if (value == HUGE_VAL) { \
                ec_throw_errno(errno, NULL) (void *)STRTO_POSITIVE; \
            } \
            else if (value == -HUGE_VAL) { \
                ec_throw_errno(errno, NULL) (void *)STRTO_NEGATIVE; \
            } \
            else { \
                ec_throw_errno(errno, NULL) (void *)STRTO_UNDERFLOW; \
            } \
        } \
        return value; \
    } \

STRTO(double,d)
STRTO(float,f)
STRTO(long double,ld)

char *
ecx_initstate(unsigned int seed, char *state, size_t n)
{
    errno = 0;
    char *previous = initstate(seed, state, n);
    if (errno != 0) {
        /* EINVAL */
        static const char INITSTATE_EINVAL[] =
            "A state array of less than 8 bytes was specified to initstate().";
        ec_throw_errno(errno, NULL) (void *)INITSTATE_EINVAL;
    }
    return previous;
}

char *
ecx_setstate(char *state)
{
    char *previous = setstate(state);
    if (previous == NULL) {
        ec_throw_str_static(ECX_NULL, "Failed to update the state array.");
    }
    return previous;
}

void *
ecx_calloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);
    if (ptr == NULL && nmemb != 0 && size != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }
    return ptr;
}

void *
ecx_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL && size != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }
    return ptr;
}

void *
ecx_realloc(void *ptr, size_t size)
{
    void *new_ptr = realloc(ptr, size);
    if (new_ptr == NULL && size != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }
    return ptr;
}

int
ecx_atexit(void (*function)(void))
{
    int status = atexit(function);
    if (status != 0) {
        ec_throw_str_static(ECX_EC, "Failed to register exit function.");
    }
    return status;
}

const char ECX_GETENV_NOT_FOUND[] = "getenv(...): Not Found";

char *
ecx_getenv(const char *name)
{
    char *value = getenv(name);
    if (value == NULL) {
        char *msg = NULL;
        int status = asprintf(&msg, "Environment variable '%s' not found.", name);
        if (status == -1) {
            msg = NULL;
        }
        ec_throw_str(ECX_GETENV_NOT_FOUND) msg;
    }
    return value;
}

const char ECX_SYSTEM_FAILURE[] = "system(...): Failure";

int
ecx_system(const char *command)
{
    errno = 0;
    int status = system(command);
    if (status == -1) {
        int errsv = errno;

        char *msg = NULL;
        int status = asprintf(&msg, "An internal error occured while attempting to run '%s'.", command);
        if (status == -1) {
            msg = NULL;
        }

        if (errsv != 0) {
            ec_throw_errno(errsv, free) msg;
        }
        else {
            ec_throw_str(ECX_SYSTEM_FAILURE) msg;
        }
    }
    return status;
}

const char ECX_BSEARCH_NOT_FOUND[] = "bsearch(...): Not Found";

void *
ecx_bsearch(
        const void *key,
        const void *base,
        size_t nmemb,
        size_t size,
        int (*compar)(const void *, const void *))
{
    void *found = bsearch(key, base, nmemb, size, compar);
    if (found == NULL) {
        ec_throw_str_static(ECX_BSEARCH_NOT_FOUND, "Entry not found.");
    }
    return found;
}

const char ECX_MBLEN_INVALID[] = "mblen(...): Invalid";

int
ecx_mblen(const char *s, size_t n)
{
    int status = mblen(s, n);
    if (status == -1) {
        ec_throw_str_static(ECX_MBLEN_INVALID,
                "An invalid or incomplete multibyte sequence was encountered.");
    }
    return status;
}

const char ECX_MBTOWC_INVALID[] = "mbtowc(...): Invalid";

int
ecx_mbtowc(wchar_t *pwc, const char *s, size_t n)
{
    int status = mbtowc(pwc, s, n);
    if (s != NULL && status == -1) {
        ec_throw_str_static(ECX_MBTOWC_INVALID,
                "An invalid or incomplete multibyte sequence was encountered.");
    }
    return status;
}

const char ECX_WCTOMB_FAILURE[] = "wctomb(...): Failure";

int
ecx_wctomb(char *s, wchar_t wc)
{
    int status = wctomb(s, wc);
    if (s != NULL && status == -1) {
        ec_throw_str_static(ECX_WCTOMB_FAILURE,
                "Unable to represent wc as a multibyte sequence (according to"
                " the current locale).");
    }
    return status;
}

const char ECX_MBSTOWCS_INVALID[] = "mbstowcs(...): Invalid";

size_t
ecx_mbstowcs(wchar_t *dest, const char *src, size_t n)
{
    size_t status = mbstowcs(dest, src, n);
    if (status == (size_t)-1) {
        ec_throw_str_static(ECX_MBSTOWCS_INVALID,
                "An invalid or incomplete multibyte sequence was encountered.");
    }
    return status;
}

const char ECX_WCSTOMBS_INVALID[] = "wcstombs(...): Invalid";

size_t
ecx_wcstombs(char *dest, const wchar_t *src, size_t n)
{
    size_t status = wcstombs(dest, src, n);
    if (status == (size_t)-1) {
        ec_throw_str_static(ECX_WCSTOMBS_INVALID,
                "An invalid or incomplete multibyte sequence was encountered.");
    }
    return status;
}
