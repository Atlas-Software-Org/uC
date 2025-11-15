#ifndef MC_CTYPE_H
#define MC_CTYPE_H 1

#define CTYPE_H 1

static inline int isdigit(int __c) {
    if (__c >= '0' && __c <= '9') {
        return 1;
    }
    return 0;
}

static inline int isalpha(int __c) {
    if ((__c >= 'a' && __c <= 'z') || (__c >= 'A' && __c <= 'Z')) {
        return 1;
    }
    return 0;
}

static inline int isalnum(int __c) {
    if (isalpha(__c) || isdigit(__c)) {
        return 1;
    }
    return 0;
}

static inline int isspace(int __c) {
    if (__c == ' ' || __c == '\t' || __c == '\n' || __c == '\v' || __c == '\f' || __c == '\r') {
        return 1;
    }
    return 0;
}

static inline int isprint(int __c) {
    if (__c >= 32 && __c <= 126) {
        return 1;
    }
    return 0;
}

static inline int tolower(int __c) {
    if (__c >= 'A' && __c <= 'Z') {
        return __c + ('a' - 'A');
    }
    return __c;
}

static inline int toupper(int __c) {
    if (__c >= 'a' && __c <= 'z') {
        return __c - ('a' - 'A');
    }
    return __c;
}

#endif /* MC_CTYPE_H */
