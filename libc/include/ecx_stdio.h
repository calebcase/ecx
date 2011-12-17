#ifndef ECX_STDIO_H
#define ECX_STDIO_H 1

#include <stdio.h>
#include <stdarg.h>

extern const char ECX_EOF[]; /* Data: C String */

int ecx_fclose(FILE *fp);

FILE *ecx_fopen(const char *path, const char *mode);
FILE *ecx_fdopen(int fd, const char *mode);
FILE *ecx_freopen(const char *path, const char *mode, FILE *stream);

int ecx_remove(const char *pathname);

int ecx_rename(const char *old, const char *new);

int ecx_fseek(FILE *stream, long offset, int whence);
long ecx_ftell(FILE *stream);

/* void rewind(FILE *stream); */

int ecx_fgetpos(FILE *stream, fpos_t *pos);
int ecx_fsetpos(FILE *stream, fpos_t *pos);

FILE *ecx_tmpfile(void);

/* void clearerr(FILE *stream); */
/* int feof(FILE *stream); */
/* int ferror(FILE *stream); */

int ecx_fileno(FILE *stream);

int ecx_fflush(FILE *stream);

/*
int ecx_fgetc(FILE *stream);
char *ecx_fgets(char *s, int size, FILE *stream);
int ecx_getc(FILE *stream);
int ecx_getchar(void);
char *ecx_gets(char *s);
int ecx_ungetc(int c, FILE *stream);
*/

extern const char ECX_FREAD_ERROR[]; /* Data: C String */
size_t ecx_fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

extern const char ECX_FWRITE_ERROR[]; /* Data: C String */
size_t ecx_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

int ecx_printf(const char *format, ...);
int ecx_fprintf(FILE *stream, const char *format, ...);
int ecx_sprintf(char *str, const char *format, ...);
int ecx_snprintf(char *str, size_t size, const char *format, ...);

int ecx_vprintf(const char *format, va_list ap);
int ecx_vfprintf(FILE *stream, const char *format, va_list ap);
int ecx_vsprintf(char *str, const char *format, va_list ap);
int ecx_vsnprintf(char *str, size_t size, const char *format, va_list ap);

/* void perror(const char *s); */

int ecx_fputc(int c, FILE *stream);
int ecx_fputs(const char *s, FILE *stream);
int ecx_putc(int c, FILE *stream);
int ecx_putchar(int c);
int ecx_puts(const char *s);

int ecx_scanf(const char *format, ...);
int ecx_fscanf(FILE *stream, const char *format, ...);
int ecx_sscanf(const char *str, const char *format, ...);

int ecx_vscanf(const char *format, va_list ap);
int ecx_vsscanf(const char *str, const char *format, va_list ap);
int ecx_vfscanf(FILE *stream, const char *format, va_list ap);

/* void setbuf(FILE *stream, char *buf); */
/* void setbuffer(FILE *stream, char *buf, size_t size); */
/* void setlinebuf(FILE *stream); */

int ecx_setvbuf(FILE *stream, char *buf, int mode, size_t size);

char *ecx_tmpnam(char *s);

#endif /* ECX_STDIO_H */
