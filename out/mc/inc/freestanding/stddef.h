#ifndef MC_STDDEF_H
#define MC_STDDEF_H 1

#define MC_STDDEF_H 1

typedef unsigned long long size_t;
typedef signed long long ssize_t;
typedef long ptrdiff_t;

#define NULL ((void*)0)
#define offsetof(type, member) __builtin_offsetof(type, member)

#ifdef MC_STANDARD
#define floortoalignment(value, alignment) \
    ((value) & ~((alignment) - 1))
#define ceiltoalignment(value, alignment) \
    (((value) + (alignment) - 1) & ~((alignment) - 1))

#define roundtonearest(value, place) \
    (((value) + ((place) / 2)) / (place) * (place))
#endif

#endif
