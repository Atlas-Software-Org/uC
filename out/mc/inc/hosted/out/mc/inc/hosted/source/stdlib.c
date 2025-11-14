#include <stdlib.h>
#include <HELPERS.h>

void *malloc(size_t size) {
    return mc_malloc(size);
}

void free(void *ptr) {
    mc_free(ptr);
}

void *calloc(size_t nmemb, size_t size) {
    size_t total = nmemb * size;
    void *ptr = malloc(total);
    if (ptr) {
        char *p = (char*)ptr;
        for (size_t i = 0; i < total; i++) p[i] = 0;
    }
    return ptr;
}

void *realloc(void *ptr, size_t size) {
    if (!ptr) return malloc(size);
    if (size == 0) { free(ptr); return NULL; }
    void *newptr = malloc(size);
    if (newptr) {
        size_t old_size = mc_malloc_size(ptr);
        size_t copy_size = old_size < size ? old_size : size;
        for (size_t i = 0; i < copy_size; i++)
            ((char*)newptr)[i] = ((char*)ptr)[i];
        free(ptr);
    }
    return newptr;
}

void abort(void) {
    mc_abort();
    while (1);
}

void exit(int status) {
    mc_doexit(status);
    while (1);
}

#define MAX_ATEXIT_FUNCS 32
static void (*atexit_funcs[MAX_ATEXIT_FUNCS])(void);
static int atexit_count = 0;

int atexit(void (*func)(void)) {
    if (atexit_count >= MAX_ATEXIT_FUNCS) return -1;
    atexit_funcs[atexit_count++] = func;
    return 0;
}

int atoi(const char *s) {
    return (int)strtol(s, NULL, 10);
}

long atol(const char *s) {
    return strtol(s, NULL, 10);
}

long strtol(const char *nptr, char **endptr, int base) {
    long result = 0;
    int sign = 1;

    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n') nptr++;

    if (*nptr == '-') { sign = -1; nptr++; }
    else if (*nptr == '+') { nptr++; }

    if (base == 0) {
        if (*nptr == '0') {
            base = (*(nptr + 1) == 'x' || *(nptr + 1) == 'X') ? 16 : 8;
            if (base == 16) nptr += 2;
        } else base = 10;
    }

    while (*nptr) {
        int digit;
        if (*nptr >= '0' && *nptr <= '9') digit = *nptr - '0';
        else if (*nptr >= 'a' && *nptr <= 'f') digit = *nptr - 'a' + 10;
        else if (*nptr >= 'A' && *nptr <= 'F') digit = *nptr - 'A' + 10;
        else break;

        if (digit >= base) break;
        result = result * base + digit;
        nptr++;
    }

    if (endptr) *endptr = (char*)nptr;
    return result * sign;
}

static void swap_bytes(char *a, char *b, size_t size) {
    for (size_t i = 0; i < size; i++) {
        char tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

static void quicksort(void *base, size_t nmemb, size_t size,
                      int (*compar)(const void*, const void*)) {
    if (nmemb < 2) return;
    char *b = (char*)base;
    size_t pivot = 0;
    for (size_t i = 1; i < nmemb; i++) {
        if (compar(b + i*size, b) < 0) {
            pivot++;
            swap_bytes(b + i*size, b + pivot*size, size);
        }
    }
    swap_bytes(b, b + pivot*size, size);
    quicksort(b, pivot, size, compar);
    quicksort(b + (pivot+1)*size, nmemb - pivot - 1, size, compar);
}

void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void*, const void*)) {
    quicksort(base, nmemb, size, compar);
}

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size,
              int (*compar)(const void*, const void*)) {
    size_t low = 0, high = nmemb;
    const char *b = (const char*)base;
    while (low < high) {
        size_t mid = (low + high) / 2;
        int cmp = compar(key, b + mid*size);
        if (cmp < 0) high = mid;
        else if (cmp > 0) low = mid + 1;
        else return (void*)(b + mid*size);
    }
    return NULL;
}
