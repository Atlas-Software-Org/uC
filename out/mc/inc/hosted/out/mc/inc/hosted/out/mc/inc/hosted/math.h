#ifndef MC_MATH_H
#define MC_MATH_H 1

#define MATH_H 1

#include <stddef.h>
#include <stdint.h>

#ifndef MC_FLOATS
uint64_t sin(uint64_t x);
uint64_t cos(uint64_t x);
uint64_t tan(uint64_t x);

uint64_t sqrt(uint64_t x);
uint64_t fabs(uint64_t x);

uint64_t ceil(uint64_t x);
uint64_t floor(uint64_t x);
uint64_t pow(uint64_t x, uint64_t y);
#else
double sin(double x);
double cos(double x);
double tan(double x);

double sqrt(double x);
double fabs(double x);

double ceil(double x);
double floor(double x);
double pow(double x, double y);
#endif

#endif
