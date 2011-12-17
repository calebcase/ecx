#ifndef ECX_STDLIB_H
#define ECX_STDLIB_H

#include <stdlib.h>

/*** Type Conversion ***/

/* double atof(const char *nptr); */
/* int atoi(const char *nptr); */
/* long atol(const char *nptr); */
/* long long atoll(const char *nptr); */
/* NOT IN GLIBC: long long atoq(const char *nptr); */

/* STD */
double ecx_strtod(const char *nptr, char **endptr);

/* ISOC99 */
float ecx_strtof(const char *nptr, char **endptr);
long double ecx_strtold(const char *nptr, char **endptr);

/* STD
long int ecx_strtol(const char *nptr, char **endptr, int base);
unsigned long int ecx_strtoul(const char *nptr, char **endptr, int base);
*/

/* BSD
long long int ecx_strtoq(const char *nptr, char **endptr, int base);
unsigned long long int ecx_strtouq(const char *nptr, char **endptr, int base);
*/

/* ISOC99 || MISC
long long int ecx_strtoll(const char *nptr, char **endptr, int base);
unsigned long long int ecx_strtoull(const char *nptr, char **endptr, int base);
*/

/* GNU
long int strtol_l (const char *nptr, char **endptr, int base, locale_t loc);
unsigned long int strtoul_l (const char *nptr, char **endptr, int base, locale_t loc);

long long int strtoll_l (const char *nptr, char **endptr, int base, locale_t loc);
unsigned long long int strtoull_l (const char *nptr, char **endptr, int base, locale_t loc);

double strtod_l (const char *nptr, char **endptr, locale_t loc);
float strtof_l (const char *nptr, char **endptr, locale_t loc);

long double strtold_l (const char *nptr, char **endptr, locale_t loc);
*/

/* SVID || XOPEN_EXTENDED
char *l64a (long int n);
long int a64l (const char *s);
*/

/*** Pseudo-random Sequence Generation ***/

/* SVID || XOPEN_EXTENDED || BSD */
/* long int random(void); */
/* void srandom(unsigned int seed); */
char *ecx_initstate(unsigned int seed, char *state, size_t n);
char *ecx_setstate(char *state);

/* MISC
int random_r (struct random_data *buf, int32_t *result);

int srandom_r (unsigned int seed, struct random_data *buf);

int initstate_r (unsigned int seed, char *statebuf, size_t statelen, struct random_data *buf);

int setstate_r (char *statebuf, struct random_data *buf);
*/

/* STD */
/* int rand(void); */
/* void srand(unsigned int seed); */

/* POSIX
int rand_r (unsigned int *seed);
*/

/*** Memory Allocation and Deallocation ***/

void *ecx_calloc(size_t nmemb, size_t size);
void *ecx_malloc(size_t size);

/* void ecx_free(void *ptr); */

void *ecx_realloc(void *ptr, size_t size);

/*** Process Control ***/

/* void abort(void); */

int ecx_atexit(void (*function)(void));

/* void exit(int status); */

extern const char ECX_GETENV_NOT_FOUND[]; /* Data: C String */
char *ecx_getenv(const char *name);

extern const char ECX_SYSTEM_FAILURE[]; /* Data: C String */
int ecx_system(const char *command);

/*** Sorting, Searching and Comparison ***/

extern const char ECX_BSEARCH_NOT_FOUND[]; /* Data: C String */
void *ecx_bsearch(
        const void *key,
        const void *base,
        size_t nmemb,
        size_t size,
        int (*compar)(const void *, const void *));

/* void qsort(
        void *base,
        size_t nmemb,
        size_t size,
        int(*compar)(const void *, const void *)); */

/*** Mathematics ***/

/* int abs(int j); */
/* long int labs(long int j); */
/* long long int llabs(long long int j); */

/*** Multibyte/Wide Characters ***/

extern const char ECX_MBLEN_INVALID[]; /* Data: C String */
int ecx_mblen(const char *s, size_t n);

extern const char ECX_MBTOWC_INVALID[]; /* Data: C String */
int ecx_mbtowc(wchar_t *pwc, const char *s, size_t n);

extern const char ECX_WCTOMB_FAILURE[]; /* Data: C String */
int ecx_wctomb(char *s, wchar_t wc);

extern const char ECX_MBSTOWCS_INVALID[]; /* Data: C String */
size_t ecx_mbstowcs(wchar_t *dest, const char *src, size_t n);

extern const char ECX_WCSTOMBS_INVALID[]; /* Data: C String */
size_t ecx_wcstombs(char *dest, const wchar_t *src, size_t n);

#endif /* ECX_STDLIB_H */
