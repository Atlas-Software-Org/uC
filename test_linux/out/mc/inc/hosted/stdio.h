#ifndef MC_STDIO_H
#define MC_STDIO_H 1

#include <stdarg.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int putchar(int __c);
int puts(const char *__s);

int printf(const char *__format, ...);
int vprintf(const char *__format, va_list __args);
int snprintf(char *buf, size_t n, const char *format, ...);

typedef struct FILE {
    int fd;
    int error;
    int index;
} FILE;

FILE *fopen(const char *__path, const char *__mode);
int fclose(FILE *__stream);
size_t fread(void *__ptr, size_t __size, size_t __nmemb, FILE *__stream);
size_t fwrite(const void *__ptr, size_t __size, size_t __nmemb, FILE *__stream);
int fseek(FILE *__stream, long __off, int __whence);
long ftell(FILE *__stream);
int fflush(FILE *__stream);
int ferror(FILE *__stream);

#endif /* MC_STDIO_H */
