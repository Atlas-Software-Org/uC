#include <unistd.h>
#include <HELPERS.h>

ssize_t read(int fd, void *buf, size_t n) {
    if (fd < 0 || !buf || n == 0) {
        errno = EBADF;
        return -1;
    }

    ssize_t ret = mc_sys_read(fd, buf, n);
    if (ret < 0) {
        errno = mc_last_error();
    }
    return ret;
}

ssize_t write(int fd, const void *buf, size_t n) {
    if (fd < 0 || !buf || n == 0) {
        errno = EBADF;
        return -1;
    }

    ssize_t ret = mc_sys_write(fd, buf, n);
    if (ret < 0) {
        errno = mc_last_error();
    }
    return ret;
}

int close(int fd) {
    if (fd < 0) {
        errno = EBADF;
        return -1;
    }

    int ret = mc_sys_close(fd);
    if (ret < 0) {
        errno = mc_last_error();
    }
    return ret;
}

static void *mc_heap_end = 0;

void *sbrk(intptr_t increment) {
    if (!mc_heap_end) {
        mc_heap_end = mc_sys_get_heap_start();
    }

    void *prev_end = mc_heap_end;
    void *new_end = mc_helper_add_ptr(mc_heap_end, increment);

    if ((intptr_t)new_end < (intptr_t)prev_end) {
        errno = ENOMEM;
        return (void *)-1;
    }

    if (mc_sys_adjust_heap(new_end) < 0) {
        errno = ENOMEM;
        return (void *)-1;
    }

    mc_heap_end = new_end;
    return prev_end;
}

off_t lseek(int fd, off_t offset, int whence) {
    if (fd < 0) {
        errno = EBADF;
        return -1;
    }
    off_t ret = mc_sys_lseek(fd, offset, whence);
    if (ret < 0) {
        errno = mc_last_error();
    }
    return ret;
}
