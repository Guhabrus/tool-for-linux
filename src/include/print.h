#ifndef PRINT_H
#define PRINT_H

#define PRINT_DEBUG

#ifdef PRINT_DEBUG
    #include <stdio.h>
    #define print_debug(...) printf(__VA_ARGS__)
#else
    #define print_debug(...) while(0)
#endif


#endif