#ifndef MC_UNISTD_H
#define MC_UNISTD_H 1

#define UNISTD_H 1

#include <stddef.h>
#include <stdint.h>
#include <errno.h>

typedef long long off_t;

ssize_t read(int __fd, void *__buf, size_t __n);
ssize_t write(int __fd, const void *__buf, size_t __n);
int close(int __fd);
void *sbrk(intptr_t __increment);
off_t lseek(int fd, off_t offset, int whence);

#endif
