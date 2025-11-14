#ifndef MC_STDLIB_H
#define MC_STDLIB_H 1

#define STDLIB_H 1

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

void free(void *__ptr);
void *malloc(size_t __size);
void *calloc(size_t __nmemb, size_t __size);
void *realloc(void *__ptr, size_t __size);

void abort(void);
void exit(int __status);
int atexit(void (*__func)(void));

int atoi(const char *__s);
long atol(const char *__s);
long strtol(const char *__s, char **__end, int base);

void qsort(void *__base, size_t __nmemb, size_t __size, int (*__compar)(const void *, const void*));
void *bsearch(const void *__key, const void *__base, size_t __nmemb, size_t __size, int (*__compar)(const void*, const void*));

#endif /* MC_STDLIB_H */
