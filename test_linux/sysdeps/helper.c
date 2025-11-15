#include <HELPERS.h>
#include "printf.h"

static void **initial_stack = 0;

__attribute__((section(".init_array")))
static void *init_stack_capturer(void *unused)
{
    void *sp;
    __asm__("mov %%rsp, %0" : "=r"(sp));
    initial_stack = (void **)sp;
    return 0;
}


unsigned long long mc_getargc()
{
    return (unsigned long long)initial_stack[0];
}

unsigned long long mc_getargv()
{
    return (unsigned long long)&initial_stack[1];
}

unsigned long long mc_getenvp()
{
    unsigned long long argc = (unsigned long long)initial_stack[0];

    return (unsigned long long)&initial_stack[1 + argc + 1];
}


static long my_syscall(long n, long a, long b, long c,
                       long d, long e, long f)
{
    long r;
    __asm__ volatile(
        "mov %1, %%rax\n"
        "mov %2, %%rdi\n"
        "mov %3, %%rsi\n"
        "mov %4, %%rdx\n"
        "mov %5, %%r10\n"
        "mov %6, %%r8\n"
        "mov %7, %%r9\n"
        "syscall\n"
        "mov %%rax, %0\n"
        : "=r"(r)
        : "r"(n),"r"(a),"r"(b),"r"(c),"r"(d),"r"(e),"r"(f)
        : "rax","rdi","rsi","rdx","r10","r8","r9","rcx","r11","memory"
    );
    return r;
}

#define SC0(n)            my_syscall(n,0,0,0,0,0,0)
#define SC1(n,a)          my_syscall(n,(long)a,0,0,0,0,0)
#define SC3(n,a,b,c)      my_syscall(n,(long)a,(long)b,(long)c,0,0,0)


void mc_doexit(unsigned long long exit_code)
{
    SC1(60, exit_code);
    for(;;);
}

int mc_vprintf(const char *format, __builtin_va_list args)
{
    return vprintf(format, args);
}

int mc_vsnprintf(char *buf, unsigned long long n,
                 const char *format, __builtin_va_list args)
{
    return vsnprintf(buf, n, format, args);
}

signed long long mc_sys_read(int fd, void *buf, unsigned long long n)
{
    return SC3(0, fd, buf, n);
}

signed long long mc_sys_write(int fd, const void *buf, unsigned long long n)
{
    return SC3(1, fd, buf, n);
}

int mc_sys_close(int fd)
{
    return (int)SC1(3, fd);
}

void *mc_sys_get_heap_start(void)
{
    return (void *)SC1(12, 0);
}

int mc_sys_adjust_heap(void *new_end)
{
    long r = SC1(12, new_end);
    return (r == (long)new_end) ? 0 : -1;
}

int mc_last_error(void)
{
    return -1;
}

void *mc_helper_add_ptr(void *ptr, long long increment)
{
    return (char *)ptr + increment;
}

void *mc_malloc(unsigned long long size)
{
    static char *end = 0;
    if (!end)
        end = mc_sys_get_heap_start();
    char *old = end;
    char *next = old + size;
    if (mc_sys_adjust_heap(next))
        return 0;
    end = next;
    return old;
}

void mc_free(void *ptr)
{
    (void)ptr;
}

unsigned long long mc_malloc_size(void *ptr)
{
    return 0;
}

void mc_abort()
{
    long pid = SC0(39);
    SC3(62, pid, 6, 0);
    for(;;);
}

int mc_putc(char c)
{
    return (int)SC3(1, 1, &c, 1);
}

long long mc_sys_lseek(int fd, long long offset, int whence)
{
    return SC3(8, fd, offset, whence);
}
