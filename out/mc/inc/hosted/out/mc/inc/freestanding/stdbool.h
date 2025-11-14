#ifndef MC_STDBOOL_H
#define MC_STDBOOL_H 1

#define STDBOOL_H 1

#ifndef MC_U8_BOOLS
#define bool _Bool
#else
#define bool unsigned char
#endif
#define true 1
#define false 0

#endif /* MC_STDBOOL_H */
