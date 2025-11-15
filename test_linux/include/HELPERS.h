#ifndef HELPERS_H
#define HELPERS_H 1

unsigned long long mc_getargc();
unsigned long long mc_getargv();
unsigned long long mc_getenvp();
void mc_doexit(unsigned long long exit_code);
int mc_vprintf(const char *format, __builtin_va_list args);
int mc_vsnprintf(char *buf, unsigned long long n, const char *format, __builtin_va_list args);
signed long long mc_sys_read(int fd, void *buf, unsigned long long n);
signed long long mc_sys_write(int fd, const void *buf, unsigned long long n);
int mc_sys_close(int fd);
void *mc_sys_get_heap_start(void);
int mc_sys_adjust_heap(void *new_end);
int mc_last_error(void);
void *mc_helper_add_ptr(void *ptr, signed long long increment);
void *mc_malloc(unsigned long long size);void mc_free(void *ptr);
unsigned long long mc_malloc_size(void *ptr);
void mc_abort();
int mc_putc(char c);
long long mc_sys_lseek(int fd, long long offset, int whence);

#endif /* HELPERS_H */