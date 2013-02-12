#include <ec/ec.h>
#include <errno.h>
#include <string.h>

#include <ecx_stdio.h>

/* FIXME: Check errno? POSIX only? */

const char ECX_EOF[] = "EOF";

int
ecx_fclose(FILE *fp)
{
    int status = fclose(fp);
    if (status != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return status;
}

FILE *
ecx_fopen(const char *path, const char *mode)
{
    FILE *stream = fopen(path, mode);
    if (stream == NULL) {
        ec_throw_errno(errno, free) strdup(path);
    }

    return stream;
}

FILE *
ecx_fdopen(int fd, const char *mode)
{
    FILE *stream = fdopen(fd, mode);
    if (stream == NULL) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return stream;
}

FILE *
ecx_freopen(const char *path, const char *mode, FILE *stream)
{
    FILE *new_stream = freopen(path, mode, stream);
    if (stream == NULL) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return new_stream;
}

int
ecx_remove(const char *pathname)
{
    int status = remove(pathname);
    if (status != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return status;
}

int
ecx_rename(const char *old, const char *new)
{
    int status = rename(old, new);
    if (status != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return status;
}

int
ecx_fseek(FILE *stream, long offset, int whence)
{
    int status = fseek(stream, offset, whence);
    if (status != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return status;
}

long
ecx_ftell(FILE *stream)
{
    long status = ftell(stream);
    if (status == -1) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return status;
}

int
ecx_fgetpos(FILE *stream, fpos_t *pos)
{
    int status = fgetpos(stream, pos);
    if (status != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return status;
}

int
ecx_fsetpos(FILE *stream, fpos_t *pos)
{
    int status = fsetpos(stream, pos);
    if (status != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return status;
}

FILE *
ecx_tmpfile(void)
{
    FILE *stream = tmpfile();
    if (stream == NULL) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return stream;
}

int
ecx_fileno(FILE *stream)
{
    int fd = fileno(stream);
    if (fd == -1) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return fd;
}

int
ecx_fflush(FILE *stream)
{
    int status = fflush(stream);
    if (status != 0) {
        ec_throw_errno(errno, NULL) NULL;
    }

    return status;
}

const char ECX_FGETC_ERROR[] = "fgetc(...): File Read Char Error";

int
ecx_fgetc(FILE *stream)
{
    errno = 0;
    int status = fgetc(stream);
    if (status == EOF && ferror(stream) != 0) {
        if (errno != 0) {
            ec_throw_errno(errno, NULL) NULL;
        }
        else {
            ec_throw_str(ECX_FGETC_ERROR) NULL;
        }
    }

    return status;
}

const char ECX_FGETS_ERROR[] = "fgets(...): File Read String Error";

char *
ecx_fgets(char *s, int size, FILE *stream)
{
    errno = 0;
    char *str = fgets(s, size, stream);
    if (str == NULL && ferror(stream) != 0) {
        if (errno != 0) {
            ec_throw_errno(errno, NULL) NULL;
        }
        else {
            ec_throw_str(ECX_FGETS_ERROR) NULL;
        }
    }

    return str;
}

const char ECX_GETC_ERROR[] = "getc(...): Read Char Error";

int
ecx_getc(FILE *stream)
{
    errno = 0;
    int status = getc(stream);
    if (status == EOF && ferror(stream) != 0) {
        if (errno != 0) {
            ec_throw_errno(errno, NULL) NULL;
        }
        else {
            ec_throw_str(ECX_GETC_ERROR) NULL;
        }
    }

    return status;
}

const char ECX_GETCHAR_ERROR[] = "getchar(...): Read Char Error";

int
ecx_getchar(void)
{
    errno = 0;
    int status = getchar();
    if (status == EOF && ferror(stdin) != 0) {
        if (errno != 0) {
            ec_throw_errno(errno, NULL) NULL;
        }
        else {
            ec_throw_str(ECX_GETCHAR_ERROR) NULL;
        }
    }

    return status;
}

const char ECX_GETS_ERROR[] = "gets(...): Read String Error";

char *
ecx_gets(char *s)
{
    errno = 0;
    char *str = gets(s);
    if (str == NULL && ferror(stdin) != 0) {
        if (errno != 0) {
            ec_throw_errno(errno, NULL) NULL;
        }
        else {
            ec_throw_str(ECX_FGETS_ERROR) NULL;
        }
    }

    return str;
}

const char ECX_UNGETC_ERROR[] = "ungetc(...): Pushback Error";

int
ecx_ungetc(int c, FILE *stream)
{
    int status = ungetc(c, stream);
    if (status == EOF) {
        ec_throw_str(ECX_UNGETC_ERROR) NULL;
    }

    return status;
}

const char ECX_FREAD_ERROR[] = "fread(...): File Read Error";

size_t
ecx_fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t count = fread(ptr, size, nmemb, stream);
    if (ferror(stream) != 0) {
        ec_throw_str(ECX_FREAD_ERROR) NULL;
    }

    return count;
}

const char ECX_FWRITE_ERROR[] = "fwrite(...): File Write Error";

size_t
ecx_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t count = fwrite(ptr, size, nmemb, stream);
    if (ferror(stream) != 0) {
        ec_throw_str(ECX_FWRITE_ERROR) NULL;
    }

    return count;
}

const char ECX_PRINTF_FAILURE[] = "printf(...): Failure";

/* Note: Can't use ec_with(...) to handle va_end(...). va_end(...) may be a
 * macro and is required to be called within the same function as the
 * corresponding va_start(...). This precludes the creation of an auxiliary
 * function for cleanup.
 */

int
ecx_printf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int status = vprintf(format, ap);
    va_end(ap);

    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

int
ecx_fprintf(FILE *stream, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int status = vfprintf(stream, format, ap);
    va_end(ap);

    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

int
ecx_sprintf(char *str, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int status = vsprintf(str, format, ap);
    va_end(ap);

    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

int
ecx_snprintf(char *str, size_t size, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int status = vsnprintf(str, size, format, ap);
    va_end(ap);

    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

int
ecx_vprintf(const char *format, va_list ap)
{
    int status = vprintf(format, ap);
    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

int
ecx_vfprintf(FILE *stream, const char *format, va_list ap)
{
    int status = vfprintf(stream, format, ap);
    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

int
ecx_vsprintf(char *str, const char *format, va_list ap)
{
    int status = vsprintf(str, format, ap);
    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

int
ecx_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    int status = vsnprintf(str, size, format, ap);
    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

/* Note: EOF when writing is an exception. When reading you expect to reach the
 * end of a file, when writing (much like with allocating memory) you don't
 * expect to run out of space. 
 */

int
ecx_fputc(int c, FILE *stream)
{
    int status = fputc(c, stream);
    if (status == EOF) {
        ec_throw_str(ECX_EOF) NULL; 
    }

    return status;
}

int
ecx_fputs(const char *s, FILE *stream)
{
    int status = fputs(s, stream);
    if (status == EOF) {
        ec_throw_str(ECX_EOF) NULL; 
    }

    return status;
}

int
ecx_putc(int c, FILE *stream)
{
    int status = putc(c, stream);
    if (status == EOF) {
        ec_throw_str(ECX_EOF) NULL; 
    }

    return status;
}

int
ecx_putchar(int c)
{
    int status = putchar(c);
    if (status == EOF) {
        ec_throw_str(ECX_EOF) NULL; 
    }

    return status;
}

int
ecx_puts(const char *s)
{
    int status = puts(s);
    if (status == EOF) {
        ec_throw_str(ECX_EOF) NULL; 
    }

    return status;
}

const char ECX_SCANF_FAILURE[] = "scanf(...): Failure";
const char ECX_SCANF_FAILURE_EOF[] =
    "End of input reached before first successful conversion"
    " or failed match occurred.";

int
ecx_scanf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int status = vscanf(format, ap);
    va_end(ap);

    if (status == EOF) {
        ec_throw(ECX_SCANF_FAILURE,
                 NULL,
                 (void (*)(FILE *, void *))ec_fprint_str)
            (void *)ECX_SCANF_FAILURE_EOF;
    }

    return status;
}

int
ecx_fscanf(FILE *stream, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int status = vfscanf(stream, format, ap);
    va_end(ap);

    if (status == EOF) {
        if (ferror(stream) != 0) {
            ec_throw_errno(errno, NULL) NULL;
        }

        ec_throw(ECX_SCANF_FAILURE,
                 NULL,
                 (void (*)(FILE *, void *))ec_fprint_str)
            (void *)ECX_SCANF_FAILURE_EOF;
    }

    return status;
}

int
ecx_sscanf(const char *str, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int status = vsscanf(str, format, ap);
    va_end(ap);

    if (status == EOF) {
        ec_throw(ECX_SCANF_FAILURE,
                 NULL,
                 (void (*)(FILE *, void *))ec_fprint_str)
            (void *)ECX_SCANF_FAILURE_EOF;
    }

    return status;
}

int
ecx_vscanf(const char *format, va_list ap)
{
    int status = vscanf(format, ap);
    if (status == EOF) {
        ec_throw(ECX_SCANF_FAILURE,
                 NULL,
                 (void (*)(FILE *, void *))ec_fprint_str)
            (void *)ECX_SCANF_FAILURE_EOF;
    }

    return status;
}

int
ecx_vsscanf(const char *str, const char *format, va_list ap)
{
    int status = vsscanf(str, format, ap);
    if (status == EOF) {
        ec_throw(ECX_SCANF_FAILURE,
                 NULL,
                 (void (*)(FILE *, void *))ec_fprint_str)
            (void *)ECX_SCANF_FAILURE_EOF;
    }

    return status;
}

int
ecx_vfscanf(FILE *stream, const char *format, va_list ap)
{
    int status = vfscanf(stream, format, ap);
    if (status == EOF) {
        ec_throw(ECX_SCANF_FAILURE,
                 NULL,
                 (void (*)(FILE *, void *))ec_fprint_str)
            (void *)ECX_SCANF_FAILURE_EOF;
    }

    return status;
}

const char ECX_SETVBUF_FAILURE[] = "setvbuf(...): Failure";

int
ecx_setvbuf(FILE *stream, char *buf, int mode, size_t size)
{
    errno = 0;
    int status = setvbuf(stream, buf, mode, size);
    if (status != 0) {
        if (errno != 0) {
            ec_throw_errno(errno, NULL) NULL;
        }
        
        ec_throw_str_static(ECX_SETVBUF_FAILURE, "Mode is invalid or the request cannot be honored.");
    }

    return status;
}

const char ECX_TMPNAM_FAILURE[] = "tmpnam(...): Failure";

char *
ecx_tmpnam(char *s)
{
    char *t = tmpnam(s);
    if (t == NULL) {
        ec_throw_str_static(ECX_TMPNAM_FAILURE, "Unique name cannot be generated.");
    }

    return t;
}

#ifdef _GNU_SOURCE

int
ecx_asprintf(char **strp, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    int status = vasprintf(strp, format, ap);
    va_end(ap);

    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

int
ecx_vasprintf(char **strp, const char *format, va_list ap)
{
    int status = vasprintf(strp, format, ap);
    if (status < 0) {
        ec_throw_str(ECX_PRINTF_FAILURE) NULL;
    }

    return status;
}

#endif
