#include <stdio.h>
#include <HELPERS.h>

int putchar(int c) {
    return mc_putc((char)c);
}

int puts(const char *s) {
    while (*s) mc_putc(*s++);
    mc_putc('\n');
    return 0;
}

int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);
    return ret;
}

int vprintf(const char *format, va_list args) {
    return mc_vprintf(format, args);
}

int snprintf(char *buf, size_t n, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = mc_vsnprintf(buf, n, format, args);
    va_end(args);
    return ret;
}

#define MAX_OPEN_HANDLES 1024
FILE open_handles[MAX_OPEN_HANDLES];
_Bool open_handles_free_list[MAX_OPEN_HANDLES] = {1};

#define PARSE_MODE(mode_str) \
    (((mode_str[0]=='r')&&(mode_str[1]!='+'))?O_RDONLY: \
     ((mode_str[0]=='r')&&(mode_str[1]=='+'))?O_RDWR: \
     ((mode_str[0]=='w')&&(mode_str[1]!='+'))?(O_WRONLY|O_CREAT|O_TRUNC): \
     ((mode_str[0]=='w')&&(mode_str[1]=='+'))?(O_RDWR|O_CREAT|O_TRUNC): \
     ((mode_str[0]=='a')&&(mode_str[1]!='+'))?(O_WRONLY|O_CREAT|O_APPEND): \
     ((mode_str[0]=='a')&&(mode_str[1]=='+'))?(O_RDWR|O_CREAT|O_APPEND):0)

FILE *fopen(const char *path, const char *mode) {
    int free_idx = -1;
    for (int i = 0; i < MAX_OPEN_HANDLES; i++) {
        if (open_handles_free_list[i]) { free_idx = i; break; }
    }
    if (free_idx == -1) return NULL;

    int fd = open(path, PARSE_MODE(mode), 0644);
    if (fd < 0) return NULL;

    open_handles_free_list[free_idx] = 0;
    open_handles[free_idx].fd = fd;
    open_handles[free_idx].error = 0;
    open_handles[free_idx].index = free_idx;

    return &open_handles[free_idx];
}

int fclose(FILE *stream) {
    if (!stream) return -1;
    int idx = stream->index;
    if (close(stream->fd) < 0) return -1;
    open_handles_free_list[idx] = 1;
    stream->fd = -1;
    stream->error = 0;
    return 0;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    if (!stream || size == 0 || nmemb == 0) return 0;
    size_t total = size * nmemb;
    size_t read_bytes = 0;
    while (read_bytes < total) {
        ssize_t n = read(stream->fd, (char*)ptr + read_bytes, total - read_bytes);
        if (n <= 0) { if (n < 0) stream->error = 1; break; }
        read_bytes += n;
    }
    return read_bytes / size;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
    if (!stream || size == 0 || nmemb == 0) return 0;
    size_t total = size * nmemb;
    size_t written = 0;
    while (written < total) {
        ssize_t n = write(stream->fd, (const char*)ptr + written, total - written);
        if (n <= 0) { if (n < 0) stream->error = 1; break; }
        written += n;
    }
    return written / size;
}

int fseek(FILE *stream, long offset, int whence) {
    if (!stream) return -1;
    off_t ret = lseek(stream->fd, offset, whence);
    if (ret < 0) { stream->error = 1; return -1; }
    return 0;
}

long ftell(FILE *stream) {
    if (!stream) return -1;
    off_t ret = lseek(stream->fd, 0, SEEK_CUR);
    if (ret < 0) { stream->error = 1; return -1; }
    return (long)ret;
}

int fflush(FILE *stream) {
    if (!stream) return -1;
    return 0;
}

int ferror(FILE *stream) {
    if (!stream) return -1;
    return stream->error;
}
