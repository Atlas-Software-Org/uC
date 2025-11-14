#ifndef MC_FCNTL_H
#define MC_FCNTL_H 1

#define FCNTL_H 1

#define O_RDONLY    0x0000
#define O_WRONLY    0x0001
#define O_RDWR      0x0002

#define O_CREAT     0x0100
#define O_EXCL      0x0200
#define O_NOCTTY    0x0400
#define O_TRUNC     0x0800
#define O_APPEND    0x1000
#define O_NONBLOCK  0x2000
#define O_DSYNC     0x4000
#define O_RSYNC     0x8000
#define O_SYNC      0x10000

#define F_GETFD     1
#define F_SETFD     2
#define F_GETFL     3
#define F_SETFL     4

int open(const char *__pathname, int __flags, ...);

__attribute__((deprecated))
int fcntl(int fd, int cmd, ...);

#endif