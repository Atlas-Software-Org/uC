#include <stdint.h>
#include <HELPERS.h>

#ifndef MC_FLOATS

uint64_t sin(uint64_t x) {
    const uint64_t SCALE = 1000000;
    const uint64_t PI = 3141592;
    x = x % (2*PI);
    if (x <= PI) return (x * SCALE)/PI;
    else return ((2*PI - x) * SCALE)/PI;
}

uint64_t cos(uint64_t x) {
    const uint64_t PI_2 = 1570796;
    return sin(x + PI_2);
}

uint64_t tan(uint64_t x) {
    uint64_t c = cos(x);
    if (c == 0) return 0;
    return (sin(x) * 1000000) / c;
}

uint64_t sqrt(uint64_t x) {
    uint64_t r = 0;
    while (r*r <= x) r++;
    return r-1;
}

uint64_t fabs(uint64_t x) {
    return x;
}

uint64_t ceil(uint64_t x) {
    return x;
}

uint64_t floor(uint64_t x) {
    return x;
}

uint64_t pow(uint64_t x, uint64_t y) {
    uint64_t r = 1;
    for (uint64_t i=0;i<y;i++) r*=x;
    return r;
}

#else

double sin(double x)   { return __builtin_sin(x); }
double cos(double x)   { return __builtin_cos(x); }
double tan(double x)   { return __builtin_tan(x); }

double sqrt(double x)  { return __builtin_sqrt(x); }
double fabs(double x)  { return __builtin_fabs(x); }

double ceil(double x)  { return __builtin_ceil(x); }
double floor(double x) { return __builtin_floor(x); }
double pow(double x, double y) { return __builtin_pow(x,y); }

#endif
